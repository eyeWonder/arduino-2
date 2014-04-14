
// pin 8 front switch
// pin 9 front led
// pin 11 turn servo left 60 right 110
// pin 12 open servo 62 open 180 close

//NOTE: Servo.attach() disables PWM on pins 9 and 10 even after Servo.detach()

#include <Servo.h> 
 
unsigned long time;
unsigned long futureTime;
boolean fadeUp = true;
int fadeValue = 0;

Servo openServo;  // create servo object to control a servo
int openPos;    // variable to store the servo openPosition 
Servo turnServo;  // create servo object to control a servo
int turnPos;    // variable to store the servo openPosition

int switchPin = 8;
int ledPin = 6;
int openServoPin = 12;
int turnServoPin = 11;
boolean hatOpen = false;
boolean hatMoving = false;


void setup() { 
 
  openServo.attach(openServoPin);
  openServo.detach();
  
  time = millis();
  futureTime = time + 30;
  Serial.begin( 9600 );
  pinMode(switchPin, INPUT_PULLUP);
} 

void loop() { 
  time = millis();
  
  //When the hat is open the animation servo, sound and excellerometer are active.
  //This should be non blocking so se can check the open/close switch
  if ( hatOpen == true && (hatMoving == false) ) {   
    accelerometer();   
    animationServo();    
    sound();    
  }
  
  //check the open/close switch, trun LED off and set hatMoving boolean
  if ( digitalRead(switchPin) == LOW && (hatMoving == false) ) {
    Serial.println("openServoPin is LOW ");
    hatMoving = true;
    analogWrite(ledPin, 0);
    openCloseHat();
  }
  
  //this will reset and trigger every 30ms
  //Used for LED fade
  if (time >= futureTime) { 
    Serial.println("reset future time ");
    futureTime = time + 30;
    if ( hatOpen == false && (hatMoving == false) ) {
      fadeLED();    
    }
  } 
}


void accelerometer(){
  
  
}

void sound() {
  
}

void animationServo(){
  turnServo.attach(turnServoPin);
  if (hatOpen) {
    for(turnPos = 60; turnPos < 110; turnPos += 1) {  
      openServo.write(openPos);              
      delay(30);                       
    }
  } else {
    for(turnPos = 110; turnPos>=60; turnPos-=1) {                                  
      openServo.write(openPos);               
      delay(30);                        
    }
  } 
  turnServo.detach();  
}

void fadeLED() {// fade LED up and down without delay
 if ( fadeUp && (fadeValue <= 251) ){
   fadeValue += 4; 
 } else {
   fadeUp = false;
   fadeValue -= 6;
 }
 analogWrite(ledPin, fadeValue);
 
 if (fadeUp == false && (fadeValue <= 5)){
   fadeUp = true; 
 }
 Serial.println(fadeValue); 
}

void openCloseHat() {
  //open or close hat, set booleans and detach to save power
  openServo.attach(openServoPin);
  if (hatOpen) {
      for(openPos = 62; openPos < 180; openPos += 1) {  
      openServo.write(openPos);              
      delay(30);                       
    }
  } else {
      for(openPos = 180; openPos>=62; openPos-=1) {                                  
      openServo.write(openPos);               
      delay(30);                        
    }
  } 
 openServo.detach();
 hatOpen = !hatOpen;
 hatMoving = false; 
}
