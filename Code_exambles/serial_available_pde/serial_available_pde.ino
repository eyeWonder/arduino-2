#include <Servo.h> 
 
int outpin = 9;  // analog pin used to connect the potentiometer
Servo myservo;  // create servo object to control a servo 

void setup() 
{   
  Serial.begin(9600);
  
  myservo.attach(outpin);  // attaches the servo on pin 9 to the servo object
  myservo.write(0); 
  delay(5000);
} 
 
void loop() 
{ 
  if (Serial.available()) {
    int inByte = Serial.read();
    myservo.write(inByte);
  }             
  delay(15);    
} 
