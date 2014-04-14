
  #include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
  SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
  SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)
  
  //char* LCDtext;
  
  int throtPin = 13; //trottle on reciever
  int steerPin = 12; // rudder on reciever
  int panPin = 11; //ail on reciever
  int tiltPin = 10; // elev on reciever
  int leftPin = A0;
  int rightPin = A1;
  int startPin = 8;
  int endPin = 13;
  
  int maestroLeft = 2;
  int MaestroRight = 3;
  
  boolean showPanTilt = false; //show pan tilt info on LCD if false it shows throttle and steering
  unsigned long duration; //duration of the pulsein from the radio
  long previousShortMillis = 0; //short interval timer
  long shortInterval = 50; // short interval timer
  long previousMediumMillis = 0; // medium interval timer
  long mediumInterval = 2000; // medium interval timer
  
  //pan tilt smoothing variables
  const int bufferLength = 10;
  int panTiltIndex = 0; 
  int panBufferTotal = 0;
  int tiltBufferTotal = 0;
  int panBuffer[bufferLength];
  int tiltBuffer[bufferLength];
  
  //driving variables
           int throtAverage, steerAverage;///do I need this?
  int throtSteerIndex = 0;
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
    
    //set up maestro pins and default values
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(leftPin, HIGH); //write forward direction to left and right with split cables
    digitalWrite(rightPin, HIGH);
    setTarget(2, 1100); //left??
    setTarget(3, 1100); //right??
    
    //set all radios pins as inputs
    for (int count=startPin; count<=endPin; count++) {
      pinMode(count, INPUT);//set pin    
    }
	
    //fill pan and tilt buffers
    for (int thisIndex = 0; thisIndex < bufferLength; thisIndex++) {
      panBuffer[thisIndex] = 1475;//fill with center position 
      panBufferTotal = panBufferTotal + 1475;
      tiltBuffer[thisIndex] = 1475; 
      tiltBufferTotal = tiltBufferTotal + 1475;
      throtBuffer[thisIndex] = 1475; 
      throtBufferTotal = throtBufferTotal + 1475;
      steerBuffer[thisIndex] = 1475; 
      steerBufferTotal = steerBufferTotal + 1475; 
    } 
  }//setup
  
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


///////DRIVE STUFF //////////////////////////////////////////

  void smoothDrive() {
    
    //Throttle
    duration = pulseIn(throtPin, HIGH);
    if (duration < 1150) { //if no reading then center servo 
      duration = 1475;
    }
    
    throtBufferTotal = throtBufferTotal - throtBuffer[throtSteerIndex]; //subtract oldest buffer value from total
    throtBuffer[throtSteerIndex] = duration; // add newest value in it's place
    throtBufferTotal = throtBufferTotal + throtBuffer[throtSteerIndex]; //add it back to the total
    throtAverage = panBufferTotal / bufferLength;  //get new average
    
    //Steering	
    duration = pulseIn(steerPin, HIGH);
    if (duration == 0) {
      duration = 1475;
    }
    steerBufferTotal = steerBufferTotal - steerBuffer[throtSteerIndex];  
    steerBuffer[throtSteerIndex] = duration;  
    steerBufferTotal = steerBufferTotal + steerBuffer[throtSteerIndex]; 
    steerAverage = steerBufferTotal / bufferLength;
    //setTarget(1, average);	
	
    throtSteerIndex = throtSteerIndex + 1;
    if (panTiltIndex >= bufferLength) { //wrap around to the beginning
      throtSteerIndex = 0;
    }
    
    ////
    //return; //either the throttle is all the way down or the radio is off but either way stop don't 
    ////

    int turningThrotAverage;
    
    if (throtAverage > 1550) { //lets go forward
       digitalWrite(leftPin, HIGH); //write forward direction to left and right with split cables
       digitalWrite(rightPin, HIGH);
       throtAverage = map(throtAverage, 1551, 1850, 1100, 1850); // map from top half of stick positon to full range
     
       if (steerAverage > 1550 || steerAverage < 1400) { //we are steering 
       
          if (steerAverage > 1550) { //going right
            int fastTrack = throtAverage;
            int amountOfSteer = 1850 - steerAverage; // get the amount of steering 
            int slowTrack = map(amountOfSteer, 300, 0, 1100, fastTrack);
            
            slowTrack = slowTrack/2; //cut it in half this may need to be adjusted
            setTarget(2, fastTrack); //left??
            setTarget(3, slowTrack); //right??
          } else {
            //turn left
          }  
        } else { // we are going straight, set both sides the same
          setTarget(2, throtAverage); //left??
          setTarget(3, throtAverage); //right??
        } 
      
      }
//    } else if (throtAverage < 1400) { //lets go backward
//        digitalWrite(leftPin, LOW); //write forward direction to left and right with split cables
//        digitalWrite(rightPin, LOW); 
//        map(throtAverage, 1100, 1399, 1100, 1850); // map to full range
//        //more like the above
//      
//      
//    } else { // we are stopped
//        if (steerAverage > 1550) {
//          //turn left ??? 
//        } else {
//          //turn right
//        }     
//    }
    
  }//smoothDrive  
///////DRIVE STUFF //////////////////////////////////////////


///////PAN AND TILT STUFF //////////////////////////////////
  
  void smoothPanTilt() {
    int average;
    
    //pan
    duration = pulseIn(panPin, HIGH);
    if (duration < 100) { //if no reading then center servo 
      duration = 1475;
    }
    panBufferTotal = panBufferTotal - panBuffer[panTiltIndex]; //subtract oldest buffer value from total
    panBuffer[panTiltIndex] = duration; // add newest value in it's place
    panBufferTotal = panBufferTotal + panBuffer[panTiltIndex]; //add it back to the total
    average = panBufferTotal / bufferLength;  //get new average
    setTarget(0, average);
    
    //tilt	
    duration = pulseIn(tiltPin, HIGH);
    if (duration == 0) {
      duration = 1475;
    }
    tiltBufferTotal = tiltBufferTotal - tiltBuffer[panTiltIndex];  
    tiltBuffer[panTiltIndex] = duration;  
    tiltBufferTotal = tiltBufferTotal + tiltBuffer[panTiltIndex]; 
    average = tiltBufferTotal / bufferLength;
    setTarget(1, average);	
	
    panTiltIndex = panTiltIndex + 1;
    if (panTiltIndex >= bufferLength) { //wrap around to the beginning
      panTiltIndex = 0;
    }
  }
///////PAN AND TILT STUFF ////////////////////////////////// 
  
  
////// MAESTRO STUFF //////////////////////////////////////

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
////// MAESTRO STUFF //////////////////////////////////////

  
////// LCD STUFF /////////////////////////////////////////

  void LCDinfo(){
    clearLCD();  
    if (showPanTilt) { //show pan tilt info    
      duration = pulseIn(panPin, HIGH);
      LCD.print("Pan: ");
      LCD.print(duration);
      moveToSecondLine();
      duration = pulseIn(tiltPin, HIGH); 
      LCD.print("Tilt: ");
      LCD.print(duration);     
    } else { //show throttle steering info    
      duration = pulseIn(throtPin, HIGH);
      LCD.print("Throttle average: ");
      LCD.print(throtAverage);
      moveToSecondLine();
      duration = pulseIn(steerPin, HIGH); 
      LCD.print("Steeringaaverage: ");
      LCD.print(steerAverage); 
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
////// LCD STUFF /////////////////////////////////////////

