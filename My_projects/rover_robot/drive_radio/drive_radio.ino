
  #include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
  SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
  SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)
  
  //char* LCDtext;
  
  int throtPin = 13; //trottle on reciever
  int steerPin = 12; // rudder on reciever
  int panPin = 11; //ail on reciever
  int tiltPin = 10; // elev on reciever
  int leftPin = 7;
  int rightPin = 6;
  int startPin = 8;
  int endPin = 13;
  
  boolean showPanTilt = false; //show pan tilt info on LCD if false it shows throttle and steering
  unsigned long duration; //duration of the pulsein from the radio
  long previousShortMillis = 0; //short interval timer
  long shortInterval = 50; // short interval timer
  long previousMediumMillis = 0; // medium interval timer
  long mediumInterval = 2000; // medium interval timer
  
  //pan tilt smoothing variables
  const int bufferLength = 10;
  int bufferIndex = 0;
  int panBufferTotal = 0;
  int tiltBufferTotal = 0;
  int panBuffer[bufferLength];
  int tiltBuffer[bufferLength];
  
  //driving variables
  int throtAverage, steerAverage;
  int throtBufferTotal = 0;
  int steerBufferTotal = 0;
  int throtBuffer[bufferLength];
  int steerBuffer[bufferLength];
  
  
  void setup()
  {
    LCD.begin(9600); // set up serial port for 9600 baud
    Maestro.begin(9600);
    delay(500); // wait for display to boot up
    backlightOn();
    pinMode(panPin, INPUT);
    pinMode(tiltPin, INPUT);
    pinMode(throtPin, INPUT);
    pinMode(steerPin, INPUT);
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    
    //set all radios pins as inputs
    for (int count=startPin; count<=endPin; count++) {
      pinMode(count, INPUT);//set pins
      lastReading[count] = 0; //fill array     
    }
	
    //fill pan and tilt buffers
    for (int thisReading = 0; thisReading < bufferLength; thisReading++) {
      panBuffer[thisReading] = 1475;//fill with center position 
      panBufferTotal = panBufferTotal + 1475;
      tiltBuffer[thisReading] = 1475;  
      
      int throtBufferTotal = 14750;
  int steerBufferTotal = 14750;
    } 
  }
  
  void loop()
  {
    unsigned long currentMillis = millis(); 
    
    // very frequent events 
    if (currentMillis - previousShortMillis > shortInterval) { 
      previousShortMillis = currentMillis; 
      
      smoothPanTilt(); //smooth pan and tilt and set servo		
    }
    
    // medium frequency events	
    if (currentMillis - previousMediumMillis > mediumInterval) { 
      previousMediumMillis = currentMillis; 
      
      LCDinfo();     
    }
   
  }//loop
  
  void LCDinfo(){
    clearLCD();  
    if (showPanTilt) {     
      duration = pulseIn(panPin, HIGH);
      LCD.print("Pan: ");
      LCD.print(duration);
      moveToSecondLine();
      duration = pulseIn(tiltPin, HIGH); 
      LCD.print("Tilt: ");
      LCD.print(duration);     
    } else {     
      duration = pulseIn(throtPin, HIGH);
      LCD.print("Throttle: ");
      LCD.print(duration);
      moveToSecondLine();
      duration = pulseIn(steerPin, HIGH); 
      LCD.print("Steering: ");
      LCD.print(duration); 
    } 
  }
  
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
  
  void smoothDrive() {
    
    //Throttle
    duration = pulseIn(throtPin, HIGH);
    if (duration < 1150) { //if no reading then center servo 
      duration = 1475;
    }
    ////
    return; //either the throttle is all the way down or the radio is off but either way stop
    ////
    
    throtBufferTotal = throtBufferTotal - throtBuffer[bufferIndex]; //subtract oldest buffer value from total
    throtBuffer[bufferIndex] = duration; // add newest value in it's place
    throtBufferTotal = throtBufferTotal + throtBuffer[bufferIndex]; //add it back to the total
    throtAverage = panBufferTotal / bufferLength;  //get new average
    //setTarget(0, average);
    
    //Steering	
    duration = pulseIn(steerPin, HIGH);
    if (duration == 0) {
      duration = 1475;
    }
    steerBufferTotal = steerBufferTotal - steerBuffer[bufferIndex];  
    steerBuffer[bufferIndex] = duration;  
    steerBufferTotal = steerBufferTotal + steerBuffer[bufferIndex]; 
    steerAverage = steerBufferTotal / bufferLength;
    //setTarget(1, average);	
	
    bufferIndex = bufferIndex + 1;
    if (bufferIndex >= bufferLength) { //wrap around to the beginning
      bufferIndex = 0;
    }
    
    //now what
    //well if we are stopped and stick is in the middle do nothing unless
    // the steering is to one side then turn
    // then um if the throttle is above half way go forward
    // if going forward and turn slow down side you are turning to
    // now for the f'ed up conditionals
    
    int turningThrotAverage;
    
    if (throtAverage > 1550) { //lets go forward
     digitalWrite(leftPin, HIGH); //write forward direction to left and right with split cables
     digitalWrite(rightPin, HIGH);
     throtAverage = map(throtAverage, 1551, 1850, 1100, 1850); // map to full range
     
     if (steerAverage > 1550 || steerAverage < 1400) { //we are steering 
        if (steerAverage > 1550) { //going right
          int fastTrack = map(throtAverage, 1551, 1850, 1100, 1850); // map to full range
          int amountOfSteer = 1850 - steerAverage; // get the abount of steering 
          int slowTrack = map(amountOfSteerAdjust, 0, 300, 1100, steerAverage);
          slowTrack = slowTrack/2; //cut it in half
          int fastTrack = map(throtAverage, 1551, 1850, 1100, 1850); // map to full range

          setTarget(2, throtAverage); //left??
          setTarget(3, slowTrack); //right??
          // figure it out
        } else {
          //turn left
        }  
      } else { // we are going straight, set both sides the same
        setTarget(2, throtAverage); //left??
        setTarget(3, throtAverage); //right??
      } 
     //go forward test steerAverage
    } else if (throtAverage < 1400) {
      digitalWrite(leftPin, LOW); //write forward direction to left and right with split cables
      digitalWrite(rightPin, LOW); 
      map(throtAverage, 1100, 1399, 1100, 1850); // map to full range
      //more like the above
      
    } else { // we are stopped
      if (steerAverage > 1550) {
        //turn left ??? 
      } else {
        //turn right
      }     
    }
    
    
  }


