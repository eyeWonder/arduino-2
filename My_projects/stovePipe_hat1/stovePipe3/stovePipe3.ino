
// pin 8 front switch
// pin 9 front led
// pin 11 turn servo left 60 right 110
// pin 12 open servo 62 open 180 close

//NOTE: Servo.attach() disables PWM on pins 9 and 10 even after Servo.detach()

#include <Servo.h> 
#include <math.h>   // (no semicolon!)
#include <EEPROM.h>

//pin assignments 
int switchPin = 8;
int ledPin = 6;
int openServoPin = 12;
int turnServoPin = 11;
const int X_Pin = 1;  // arduino pin for x 
const int Y_Pin = 2;  // arduino pin for y 
const int Z_Pin = 3;  // arduino pin for z 

unsigned long time;
unsigned long futureTime;
boolean fadeUp = true;
int fadeValue = 0;

//acceleromenter vars See Tilt_Sensing_Accelerometer scetch for more info
int xMid, yMid, zMid, xRng, yRng, zRng;
int xr = 0, yr = 0, zr = 0;    // x raw etc
float x = 0;
float y = 0;
float z = 0;
float tiltx, tilty, tiltz;

Servo openServo;  // create servo object to control a servo
int openPos;    // variable to store the servo openPosition 
Servo turnServo;  // create servo object to control a servo
int turnPos;    // variable to store the servo openPosition

boolean hatOpen = false;
boolean hatMoving = false;


void setup() { 
  Serial.begin( 9600 );
  
  time = millis();
  futureTime = time + 30;
  
  pinMode(switchPin, INPUT_PULLUP);
  
      // read calibration values from EEprom - won't work until calibrated
    xMid = EEPROM.read(1000) << 8; 
    xMid = xMid | EEPROM.read(1001);
    xRng = EEPROM.read(1002) << 8;
    xRng = xRng | EEPROM.read(1003);
    yMid = EEPROM.read(1004) << 8; 
    yMid = yMid | EEPROM.read(1005);
    yRng = EEPROM.read(1006) << 8;
    yRng = yRng | EEPROM.read(1007);
    zMid = EEPROM.read(1008) << 8; 
    zMid = zMid | EEPROM.read(1009);
    zRng = EEPROM.read(1010) << 8;
    zRng = zRng | EEPROM.read(1011);

    // print calibration values. x, y, z pairs
    // they should look like ~300 ~160  ~300 ~160   ~300 ~160   
    
    Serial.println("Calibratrion constants: xMid, xRng, yMid, yRng, zMid, zRng");
    Serial.print(xMid);
    Serial.print("\t"); 
    Serial.print(xRng); 
    Serial.print("\t\t");
    Serial.print(yMid);
    Serial.print("\t"); 
    Serial.print(yRng); 
    Serial.print("\t\t");
    Serial.print(zMid); 
    Serial.print("\t"); 
    Serial.println(zRng);
    delay(2000);

} 

void loop() { 
  time = millis();
  
  //check the open/close switch, trun LED off and set hatMoving boolean
  if ( digitalRead(switchPin) == LOW && (hatMoving == false) ) {
    Serial.println("openServoPin is LOW ");
    hatMoving = true;
    analogWrite(ledPin, 0);
    openCloseHat();
  }
  
  //this will reset and trigger every 30ms
  //Used to trigger short duraton events
  //Try to use only non blocking functions when possible
  if (time >= futureTime) { 
    Serial.println("reset future time ");
    futureTime = time + 30;
    
    if ( hatOpen && (hatMoving == false) ) {
      //do open stuff
      //accelerometer();
      animationServo();    
      sound();
      
    }
    
    if ( hatOpen == false && (hatMoving == false) ) {
      fadeLED();    
    }
  } 
}


void accelerometer(){
  
  readdAccelerometer();
    Serial.print(tiltx); // use "tiltx", "tilty" etc in your program
    Serial.print("\t");  // "\t" is tab character
    Serial.print(tilty); 
    Serial.print("\t"); 
    Serial.println(tiltz);
}

void  readdAccelerometer(){
    xr = analogRead(X_Pin);      // read analog pin for x raw
    //     Serial.print(xr );       
    //     Serial.print("  ");
    yr = analogRead(Y_Pin);      // read analog pin for y raw
    //     Serial.print(yr ); 
    //     Serial.print(" ");     
    zr = analogRead(Z_Pin);      // read analog pin for z raw   
    //     Serial.println(zr );              

    x = (xr - xMid) / (float)xRng;
    //    Serial.print("   "); 
    y = (yr - yMid) / (float)yRng;
    //    Serial.print("         "); 
    z = (zr - zMid) / (float)zRng;

    tiltx = atan2( sqrt((y*y) + (z*z)), x);
         Serial.print(tiltx );       
         Serial.print("  ");
    tilty = atan2( sqrt((x*x) + (z*z)), y);
         Serial.print(tiltyjg; );       
         Serial.print("  ");
    tiltz = atan2( sqrt((y*y) + (x*x)), z);
         Serial.print(tiltx );       
         Serial.print("  ");
}

void sound() {
 // mouseSqueek();
}

void mouseSqueek(){
  for (int squeeks = 0; squeeks < 4; squeeks++) { 
    int thisNote;
   for (thisNote = 0; thisNote < 6; thisNote++) {    
      tone(6, 100, 20);
      delay(20);
      tone(6, 160, 15);
      delay(20);
      tone(6, 26, 40);
      delay(35);  
   }
    delay(30); 
  } 
}

void peep() { 
  int totalSqueeks = random(2, 5);  
  for (int squeeks = 0; squeeks < totalSqueeks; squeeks++) { 
    for (int thisNote = 2900; thisNote < 3500; thisNote++) {
      float duration = 370 - (thisNote/10);//makes the duration shorter the highter the note
      tone(6, thisNote, duration);     
      //noTone(6);
    }
    int extraDelay = random(0, 600);
    delay(200+extraDelay); 
  }
}

void animationServo(){
  turnServo.attach(turnServoPin);
 
    for(turnPos = 60; turnPos < 110; turnPos += 1) {  
      turnServo.write(turnPos);              
      delay(30);                       
    }
 
    for(turnPos = 110; turnPos>=60; turnPos-=1) {                                  
      turnServo.write(turnPos);               
      delay(30);                        
    }
 
  
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
    turnServo.detach(); 
    
    for(openPos = 62; openPos < 180; openPos += 1) {  
      openServo.write(openPos);              
      delay(30);                       
    }
  } else {
    for(openPos = 180; openPos>=62; openPos-=1) {                                  
      openServo.write(openPos);               
      delay(30);                        
    }
    
    turnServo.attach(turnServoPin);
  } 
  openServo.detach();
  hatOpen = !hatOpen;
  hatMoving = false; 
}
