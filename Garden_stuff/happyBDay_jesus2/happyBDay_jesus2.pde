// include the library code:
#include <SerialLCD.h>
#include <NewSoftSerial.h> //this is a must
#include "pitches.h"
#include <Servo.h> 

// initialize the library
SerialLCD slcd(11,12);//this is a must, assign soft serial pins

//Vars
const int pingPin = 6; //for ping pin
long duration, inches; //more ping vars
boolean eyeCover = false;
long timeEyeCovered;
int inPin = 10;  // happy birthday pin
int pos = 0;    // variable to store the servo position

// notes in the melody:
int melody[] = {
  NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_C7, NOTE_B6, 0,
  NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_D6, NOTE_C6, 0,
  NOTE_G6, NOTE_G6, NOTE_G7, NOTE_E6, NOTE_C6, NOTE_C6, NOTE_B6, NOTE_A6, 0,
  NOTE_F6, NOTE_F6, NOTE_E6, NOTE_C6, NOTE_D6, NOTE_C6};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {  
2, 4, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2};
  
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be create 
 
void setup() {
  Serial.begin(9600);
  slcd.begin(); // set up lcd 
  
  pinMode(4, OUTPUT);  //for the LED
  
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
  myservo.write(15);  // sets initial servo postion
  myservo.detach();  // detaches the servo so it wont move
  coverJesus();
}
 
void loop() {
  
  testPing();
  Serial.print(inches); //print to serial monitor for debug
  Serial.println(" inches");
  
  if (inches<5 && inches != 0 && eyeCover == false){
    eyeCover = true;
    timeEyeCovered = millis();
    NowHoldIt();
  } else if(inches>5 && eyeCover == true ){
   eyeCover = false;
   coverJesus(); 
  }
  
  if (millis()-timeEyeCovered >3000 && eyeCover == true){
    playHappyBirthday();
  } 
  
}

void playHappyBirthday(){
  digitalWrite(4, HIGH); //LED
  digitalWrite(inPin, HIGH); //buzzer  

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 29; thisNote++) {
    digitalWrite(4, HIGH); //LED
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    // change 350 to 1000 to make timing accurate
    int noteDuration = 350/noteDurations[thisNote];
    tone(inPin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);
    
    slcd.clear();
    slcd.setCursor(0, 0);
    slcd.print("it your birthday");
    slcd.setCursor(0, 1);
    slcd.print(" happy birthdy");
    
  }
    
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object  
  for(pos = 0; pos < 120; pos += 1)  // goes from 0 degrees to 120 degrees 
  {                                  // in steps of 2 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 5ms for the servo to reach the position 
  } 
  for(int i = 0; i<=1; i+=1){ 
    for(pos = 120; pos>=80; pos-=1) {                                 
      myservo.write(pos);               
      delay(20);                      
    } 
    for(pos = 80; pos<=120; pos+=1) {                                 
      myservo.write(pos);               
      delay(20);                      
    }
  }  
  for(pos = 120; pos>=15; pos-=1)     // goes from 120 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  myservo.detach();
  
  digitalWrite(4, LOW); //LED
  
  coverJesus();
  
}

void coverJesus() {
  // Print a message to the LCD
  slcd.clear();
  slcd.setCursor(0, 0);
  slcd.print("cover Jesuses");
  slcd.setCursor(0, 1);
  slcd.print("eyes to begin");   
}

void NowHoldIt() {
  slcd.clear();
  slcd.setCursor(0, 0);
  slcd.print("Thant's Good");
  slcd.setCursor(0, 1);
  slcd.print("Now Hold it");   
}

int testPing() {
   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  microsecondsToInches(duration);  
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  inches =  microseconds / 74 / 2;
}
