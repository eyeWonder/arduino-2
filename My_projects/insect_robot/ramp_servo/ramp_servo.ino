// updated - Joe Saavedra, 2010
#include <Servo.h> 
 
Servo frontServo;  
  
int center = 91;
int right = 30;
int left = 150;
int distanceToMove;
int speedMillisAdded = 10;
int timesTilStop = 6;

void moveForward()
{
  moveServo(frontServo, right, 1); 
  //moveServo(frontServo, center, 1); 
  moveServo(frontServo, left, 1); 
}
 
void setup()
{
  frontServo.attach(7);
  Serial.begin(9600);
}

void loop()
{
  moveForward();
  delay(200);  //time between each step taken, speed of walk
  timesTilStop--;
  if (timesTilStop == 0) {
    while (true) {};
  }
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
        delay(speedMillis+speedMillisAdded);
      }
    } else {
      for (int i = servoPosition; i<=moveTo; i++) {
        servoName.write(i);
        delay(speedMillis+speedMillisAdded);
      }
    }
  }
  return;
}

int ramp (int startPos, int currentPos, int endPos) {


 float something = millis()/1000.0;
 int value = 128.0 + 128 * sin( something * 2.0 * PI  );

 Serial.print(value);
 Serial.print("hello ");
 Serial.println(something);
 delay(500);

}



