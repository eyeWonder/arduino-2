// updated - Joe Saavedra, 2010
#include <Servo.h> 
 
Servo frontServo;  
Servo rearServo;  
int centerPos = 91;
int frontRightUp = 72;
int frontLeftUp = 108;
int backRightForward = 75;
int backLeftForward = 105;
void moveForward()
{
  frontServo.write(frontRightUp);
  delay(300);
  rearServo.write(backLeftForward);
  delay(225);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(130);
  frontServo.write(frontLeftUp);
  delay(300);
  rearServo.write(backRightForward);
  delay(225);
  
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(130);
}
 
void setup()
{
  frontServo.attach(10);
  rearServo.attach(12);
}

void loop()
{
  moveForward();
  delay(150);  //time between each step taken, speed of walk
}
