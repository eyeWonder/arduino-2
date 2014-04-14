
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position 
int inByte = 0;         // incoming serial byte
 
void setup() 
{ 
  // start serial port at 9600 bps:
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  establishContact();  // send a byte to establish contact until receiver responds  
} 
 
 
void loop() 
{ 
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if (inByte == 'q'){
      moveServo();
     
    }
    
  }
} 

void moveServo() {
    for(pos = 20; pos < 120; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 120; pos>=20; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
