// updated - Joe Saavedra, 2010
#include <Servo.h> 
 
Servo headServo; 
Servo frontServo;  
Servo rearServo;  
int centerPos = 91;
int frontRightUp = 72;
int frontLeftUp = 108;
int backRightForward = 75;
int backLeftForward = 105;
int distanceToMove;
int headCenter = 97;
int headLeft = 20;
int headRight = 160;

int speedMillisMultiplier = 20;

void moveForward()
{
  moveServo(frontServo, frontRightUp, 1); 
  moveServo(rearServo, backLeftForward, 1); 
  moveServo(frontServo, centerPos, 1); 
  moveServo(rearServo, centerPos, 1); 
  moveServo(frontServo, frontLeftUp, 1); 
  moveServo(rearServo, backRightForward, 1); 
  moveServo(frontServo, centerPos, 1); 
  moveServo(rearServo, centerPos, 1); 
}
void moveHead()
{
  moveServo(headServo, headLeft, 1); 
  moveServo(headServo, headRight, 1); 
  moveServo(headServo, centerPos, 1); 
}
 
void setup()
{
  headServo.attach(4);
  frontServo.attach(2);
  rearServo.attach(8);
  
  
  moveServo(headServo, headCenter, 1);
}

void loop()
{
  //moveHead();
  //moveForward();
  delay(600);  //time between each step taken, speed of walk
}

void moveServo(Servo servoName, int moveTo, int speedMillis) 
{
  int distanceToMove;
  int servoPosition = servoName.read();
  
  if ( speedMillis == 0 ){
    servoName.write(moveTo);
  } else {
    if (servoPosition >= moveTo) {
      for (int i = servoPosition; i>=moveTo; i--) {
        servoName.write(i);
        delay(speedMillis*speedMillisMultiplier);
      }
    } else {
      for (int i = servoPosition; i<=moveTo; i++) {
        servoName.write(i);
        delay(speedMillis*speedMillisMultiplier);
      }
    }
  }
  return;
}





