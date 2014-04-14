 #include <SoftwareSerial.h>

   //////////////////////////////
   //                          //
   // TREV LOTS OF PIN CHANGES //     moving stuff for the cut wires and accelerometer
   //                          //
   //////////////////////////////

                        // This is not used because nothing is sent from the 7 segment LED to the arduino but
#define SerInToArdu 1   // a pin number is still needed on compile so there is not error and because when you 
                        // make an instance of SoftwareSerial a pin number is need to prevent an error.
                        
#define SerOutFrmArdu 2 // To the 7 segment led RX pin
#define setBtn 6        // switch is conected to ground constantly and breaks when pressed - no resistor used
#define setLED 5        // for button press feedback
#define setPot A3       // potentiometer for setting time

//Cut Wire Pins         // These could be cut down to 2 pins if we use resistors and analog ports
#define stopWire 8      //
#define explodeWire 9   //
#define speedupWire 10  //
#define slowdownWire 11 //

//Accelerometer pins
//#define x A0          // coming soon
//#define y A1          //
//#define z A2          //

unsigned long minuteSet;
int secondSet = 0;
unsigned long elapseTime = 1001;
unsigned long timeIntervalStart = millis();
int timeInterval = 100;
boolean timeSet = false;
unsigned long minutes;
unsigned long seconds;

// wire cut variables
boolean stopWireCut = true;
int stopWireCount = 0;
boolean explodeWireCut = true;
int explodeWireCount = 0;
boolean speedupWireCut = true;
int speedupWireCount = 0;
boolean slowdownWireCut = true;
int slowdownWireCount = 0;
int gameType;           // 0 = use switch to start and stop timer
                        // 1 = cut wire to change the timer state
                        // 2 = accelerometer mode - details to come
// amount of time the timer will speed up or slow down in minutes
int timerChangeDuration = 1;
unsigned long wireCutCheck;

boolean buttonPressed = false;
unsigned long buttonPressCheck;
int btnSetCounter = 0;

boolean timerRunning = true;

SoftwareSerial mySerialPort(SerInToArdu,SerOutFrmArdu);

void setup(){
  pinMode(SerOutFrmArdu,OUTPUT);
  mySerialPort.begin(9600);
  Serial.begin(9600);
  //mySerialPort.print("XXXX"); //turn off all digits
  //
  delay(1000);
  pinMode(setLED, OUTPUT);
  
  
    pinMode(stopWire, INPUT);        //set all wire pins as inputs and set pull up resitors
     digitalWrite(stopWire, HIGH);
    pinMode(explodeWire, INPUT);
     digitalWrite(explodeWire, HIGH);
    pinMode(speedupWire, INPUT);
     digitalWrite(speedupWire, HIGH);
    pinMode(slowdownWire, INPUT);
     digitalWrite(slowdownWire, HIGH);
     
  if ( digitalRead(stopWire) == LOW ) { // test for stopWire and if so this is a wire cut game
    stopWireCut = false;
    mySerialPort.write(0x76); //reset display no second byte
    mySerialPort.print("CUTX"); 
    gameType = 1;
    delay(500);
    
    //test other non required wires to see if they are set. HIGH means they are not connected
    if ( digitalRead(explodeWire) == LOW ) { // test if explodeWire is absent
      explodeWireCut = false;
      Serial.println("explodeWireCut set to false");
    }
    if ( digitalRead(speedupWire) == LOW ) { // test if speedupWire is absent
      speedupWireCut = false;
      Serial.println("speedupWireCut set to false");
    }
    if ( digitalRead(slowdownWire) == LOW ) { // test if slowdonWire is absent  
      slowdownWireCut = false;
      Serial.println("slowdownWireCut set to false");
    }
  } else { // this is a button press game
    mySerialPort.write(0x76); //reset display no second byte
    //mySerialPort.print("5678"); //turn off all digits
    mySerialPort.print("BTNX");
    gameType = 0;
  } 
  
  pinMode(setBtn, INPUT);
  digitalWrite(setBtn, HIGH); //set internal pull up resitor 
  delay(3000);
  mySerialPort.write(0x77);//command byte
  mySerialPort.write(0x10);//data byte - this turns the colon on  
  
   Serial.print("game type ");
          Serial.println(gameType);
  
          Serial.print("stopWireCut in setup ");
          Serial.println(stopWireCut);
          Serial.print("explodeWireCut in setup ");
          Serial.println(explodeWireCut);
          Serial.print("speedupWireCut in setup ");
          Serial.println(speedupWireCut);
          Serial.print("slowdownWireCut in setup ");
          Serial.println(slowdownWireCut);
         
}

void loop(){
//  Serial.print("explodeWireCut begining of loop ");
//          Serial.println(explodeWireCut); 
//          Serial.print("explodeWireCut begining of loop ");
//          Serial.println(explodeWireCut); 
//          Serial.print("explodeWireCut begining of loop ");
//          Serial.println(explodeWireCut); 
          
          
  if (elapseTime < 1000 )endCountdown(); //finish countdown and stop
  
  // This is the clock time interval
  if (millis() > timeIntervalStart + timeInterval) { //with this we can get rid of the delay() and just
      timeIntervalStart = millis();                 // set timeInterval to speeed it up or slow it down.

    if (!timeSet) { // if the time is not set we read the pot and wait for a button press
      minuteSet = analogRead(setPot);
      minuteSet = map(minuteSet, 0, 1023, 1, 99);
      SetClock(minuteSet, secondSet);
      elapseTime = minuteSet*1000*60;
  
      if (buttonPress()) { //test button if button pressed
        if (btnSetCounter == 3) { //wait 3/10 a second because the button is checked every 100 milliseconds
          timeSet = true; // now the timer is set 
          digitalWrite(setLED, LOW); //turn on LED
          // chirp alarm    
        }
      }
        
    } else { //timer already set
         
      if (gameType == 0) {//button switch game    
        if (buttonPress()) { //test button if button pressed
          if (btnSetCounter == 30) { //wait 3 seconds
            timerRunning = !timerRunning; //change the state
            // probably chirp the alarm here     
          }
        }
      }//end gameType == 0 this is the switch game
      
      if (gameType == 1) { //wire cut came  
         
        if (stopWireCut == false) { // if stopWireCut is false we check it and the other wires
          wireCut();
         
          if (stopWireCount == 5) { // test for stopWireCut
            stopWireCut = true; 
          }
  
          if (!explodeWireCut) { // test for explodeWireCut
            if (explodeWireCount == 5) {
              endCountdown(); 
              explodeWireCut = true; 
            }
          }
          
          if (!speedupWireCut) { // test for speedupWireCut
            if (speedupWireCount == 5) {
              Serial.println("--------------------the Speed up Wire was Cut--------------");
              endCountdown(); 
              speedupWireCut = true; 
            }
          }
          
          if (!slowdownWireCut) { // test for slowdownWireCut
            if (slowdownWireCount == 5) {
              Serial.println("--------------------the slow down Wire was Cut--------------");
              endCountdown(); 
              slowdownWireCut = true; 
            }
          }
           
        } else { //stopWireCut so stop the timer
          timerRunning = false; //stop the timer
           Serial.print("timerRunning ");
          Serial.println(timerRunning);
        }// end stopWire else
      }// end wire cut game
      
      //if (gameType == 2) { //accelerometer game coming soon
      
      //}
      
      
      if (timerRunning) {
         makeMinSec(); //decriment the time and set the clock
      }
      
    }// end else timeSet/update clock if/else
  }// end clock time interval
}//end main loop



boolean wireCut() { //this will check the button every 100 milliseconds
   if (millis() > wireCutCheck + 100) { //button interval do every 100 milliseconds
     buttonPressCheck = millis();   
     
     if (digitalRead(stopWire) == HIGH) { //test button
        stopWireCount++;  
       //Serial.print(stopWireCount);     
     } else {
        stopWireCount = 0; // reset button pressed var
     }
     
     if (digitalRead(explodeWire) == HIGH) { //test button
        explodeWireCount++; 
       Serial.print("incrment explodeWireCount "); 
        Serial.println(explodeWireCount);     
     } else {
       Serial.print("decriment explodeWireCount "); 
        Serial.println(explodeWireCount); 
        explodeWireCount = 0; // reset button pressed var
     }
     
     
     
     
     
  }//end button interval check
}//end buttonPress


boolean buttonPress() { //this will check the button every 100 milliseconds
   if (millis() > buttonPressCheck + 100) { //button interval do every 100 milliseconds
     buttonPressCheck = millis();   
     if (digitalRead(setBtn) == HIGH) { //test button
        btnSetCounter++;
        digitalWrite(setLED, HIGH); //turn on LED give button press feedback
        return true;
     } else {
        btnSetCounter = 0; // reset button pressed var
        digitalWrite(setLED, LOW); //turn on LED 
        return false;
     }
  }//end button interval check
}//end buttonPress

unsigned long makeMinSec() { 
    elapseTime = elapseTime - 999;
    //hour = elapseTime / (1000*60*60); not used but just for reference
    //minutes = (elapseTime % (1000*60*60)) / (1000*60);
    ////////////////////////356400000 is the number of milliseconds in 99 minutes instead of 1 hour
    minutes = (elapseTime % 356400000) / 60000;
    //seconds = ((elapseTime % (1000*60*60)) % (1000*60)) / 1000;
    seconds = ((elapseTime % 356400000) % 60000) / 1000;  
   SetClock(minutes, seconds);//sending a float to an int this seems to work
}//end makeMinSec


void SetClock(int minutes, int seconds){
  mySerialPort.write("v"); //reset display no second byte
    if (minutes < 10) {
      mySerialPort.print("X");  
    }
    mySerialPort.print(minutes);
   
    if (seconds < 10) {
      mySerialPort.print("0");  
    }
    mySerialPort.print(seconds);
}// end SetClock



void endCountdown(){
  mySerialPort.print("DEAD");
 // mySerialPort.write(0x77);//command byte
 // mySerialPort.write(0x00);//This causes an error and is a know issue patch in next version
  Serial.print("-----------------------explode-----------------------");
  boolean alarmOn = false;
  while(true){// endless loop to stop the main loop but will use this to turn off alarm after a bit
    
    // Set off alarm here
  }//endless loop
}// end endCountdown


