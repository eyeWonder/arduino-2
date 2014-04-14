
  #include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
  SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
  SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)
  //char* LCDtext;
  int panPin = 11; //ail on reciever
  int tiltPin = 10; // elev on reciever
  unsigned long duration; //duration of the pulsein from the radio
  long previousMillis = 0; //for interval timer
  long interval = 100; // for interval timer
  
  
  void setup()
  {
    LCD.begin(9600); // set up serial port for 9600 baud
    Maestro.begin(9600);
    delay(500); // wait for display to boot up
    backlightOn();
    pinMode(panPin, INPUT);
    pinMode(tiltPin, INPUT);
  }
  
  void loop()
  {
    unsigned long currentMillis = millis();  
    if (currentMillis - previousMillis > interval) { 
      previousMillis = currentMillis; 
      
      clearLCD();
      duration = pulseIn(panPin, HIGH); 
      clearLCD();
      LCD.print("pan: ");
      LCD.print(duration);
      settarget(0, duration); //move pan servo
      moveToSecondLine();
      duration = pulseIn(tiltPin, HIGH); 
      LCD.print("tilt: ");
      LCD.print(duration);
      settarget(1, duration); //move tilt servo
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
  void settarget(unsigned char servo, unsigned int target)
  {
    //target = map(target, 0, 180, 4000, 8000);//this is the original
    target = map(target, 1100, 1850, 4000, 8000);
    //target = 2000;
    Maestro.write(0xAA); //start byte
    Maestro.write(0x0C) ; //device id 12
    Maestro.write(0x04); //command number
    Maestro.write(servo); //servo number
    Maestro.write(target & 0x7F);
    Maestro.write((target >> 7) & 0x7F);
  }


