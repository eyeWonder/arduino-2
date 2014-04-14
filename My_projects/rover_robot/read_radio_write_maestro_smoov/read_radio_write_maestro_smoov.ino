
  #include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
  SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
  SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)
  
  //char* LCDtext;
  
  int panPin = 11; //ail on reciever
  int tiltPin = 10; // elev on reciever
  unsigned long duration; //duration of the pulsein from the radio
  long previousShortMillis = 0; //short interval timer
  long shortInterval = 50; // short interval timer
  long previousMediumMillis = 0; // medium interval timer
  long mediumInterval = 2000; // medium interval timer
  
  //pan tilt smoothing variables
  const int bufferLength = 10;
  int bufferIndex = 0;
  int panBufferTotal = 14750;
  int tiltBufferTotal = 14750;
  int panBuffer[bufferLength];
  int tiltBuffer[bufferLength];
  
  
  void setup()
  {
    LCD.begin(9600); // set up serial port for 9600 baud
    Maestro.begin(9600);
    delay(500); // wait for display to boot up
    backlightOn();
    pinMode(panPin, INPUT);
    pinMode(tiltPin, INPUT);
	
    //fill pan and tilt buffers
    for (int thisReading = 0; thisReading < bufferLength; thisReading++) {
      panBuffer[thisReading] = 1475;//fill with center position 
      tiltBuffer[thisReading] = 1475;  
    } 
  }
  
  void loop()
  {
    unsigned long currentMillis = millis(); 
	 
    if (currentMillis - previousShortMillis > shortInterval) { 
      previousShortMillis = currentMillis; 
      smoothPanTilt(); //smooth pan and tilt and set servo		
    }
	
    if (currentMillis - previousMediumMillis > mediumInterval) { 
      previousMediumMillis = currentMillis; 
      clearLCD();
      duration = pulseIn(panPin, HIGH);
      LCD.print("pan: ");
      LCD.print(duration);
      moveToSecondLine();
      duration = pulseIn(tiltPin, HIGH); 
      LCD.print("tilt: ");
      LCD.print(duration);	
    }
   
  }//loop
  
  void clearLCD() {
    LCD.write(0xFE); //command flag
    LCD.write(0X01); // clear command
  }
  
  void moveToSecondLine() {
    LCDgoTo(16); //move to function position 16 is the first position on the second line
  }
  
  void backlightOn() {
    LCD.write(0x80); //command flag
    LCD.write(0x9D);//157 about half brightness
  }
  
  void backlightOff(){  //turns off the backlight
    int zero = 0; //using a variable because I get an error when useing an literal integer
    LCD.write(0x80);   //command flag for backlight stuff
    LCD.write(zero);    //light level for off.
  }
  
  void LCDgoTo(int position) 
  { //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
    if (position<32){ 
      LCD.write(0xFE); //command flag
      LCD.write(0X80); // set cursor position command
      LCD.write(position);  // cursor position
    } 
    else { LCDgoTo(0); }
  }

  //Send a Set Target command to the Maestro.
  //Target is in units of quarter microseconds, so the normal range is 4000 to 8000.
  void setTarget(unsigned char servo, unsigned int target) {
    target = map(target, 1100, 1850, 4000, 8000);
    //target = 2000;
    Maestro.write(0xAA); //start byte
    Maestro.write(0x0C) ; //device id 12
    Maestro.write(0x04); //command number 0x04 = Set Target
    Maestro.write(servo); //servo number
    Maestro.write(target & 0x7F); //target low bits
    Maestro.write((target >> 7) & 0x7F); //target high bits
	
	//Maestro.write(0xAA); //start byte
    //Maestro.write(0x0C) ; //device id 12
    //Maestro.write(0x07); //command number 0x04 = Set Speed 0x09 = set acceleration
    //Maestro.write(servo); //servo number
	//Maestro.write(target & 0x7F); //speed low bits
   // Maestro.write((target >> 7) & 0x7F); //speed high bits
  }
  
  void smoothPanTilt() {
    int average;
    
    //pan
    duration = pulseIn(panPin, HIGH);
    if (duration < 100) { //if no reading then center servo 
      duration = 1475;
    }
    panBufferTotal = panBufferTotal - panBuffer[bufferIndex]; //subtract oldest buffer value from total
    panBuffer[bufferIndex] = duration; // add newest value in it's place
    panBufferTotal = panBufferTotal + panBuffer[bufferIndex]; //add it back to the total
    average = panBufferTotal / bufferLength;  //get new average
    setTarget(0, average);
    
    //tilt	
    duration = pulseIn(tiltPin, HIGH);
    if (duration == 0) {
      duration = 1475;
    }
    tiltBufferTotal = tiltBufferTotal - tiltBuffer[bufferIndex];  
    tiltBuffer[bufferIndex] = duration;  
    tiltBufferTotal = tiltBufferTotal + tiltBuffer[bufferIndex]; 
    average = tiltBufferTotal / bufferLength;
    setTarget(1, average);	
	
    bufferIndex = bufferIndex + 1;
    if (bufferIndex >= bufferLength) { //wrap around to the beginning
      bufferIndex = 0;
    }
  }


