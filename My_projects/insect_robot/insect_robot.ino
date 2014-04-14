
#include <Servo.h> 

Servo frontServo; 
Servo rearServo;  
int delayTime = 1000;

void setup() 
{ 
  frontServo.attach(10);
  frontServo.write(93); //center
  delay(delayTime);
  frontServo.write(180); //leftFrontDown 90 degrees
  delay(delayTime);
  frontServo.write(10); //rightFrontDown 90 degrees
  delay(delayTime);
  frontServo.write(93); //center 
  
  
  rearServo.attach(12);
  rearServo.write(90); //center
  delay(delayTime);
  rearServo.write(174); //rearRight 90 degrees
  delay(delayTime);
  rearServo.write(6); //rearLeft 90 degrees
  delay(delayTime);
  rearServo.write(90); //center  
  
  
} 
 
void loop() 
{ 
  delay(delayTime);
} 
