#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object 2

void setup() 
{   
} 
 
void loop() 
{ 
  robot_straight(2000);
  delay(2000);
  robot_turn('right', 90);
  delay(2000);
  
  robot_straight(2000);
  delay(2000);
  robot_turn('right', 90);
  delay(2000);
  
  robot_straight(2000);
  delay(2000);
  robot_turn('right', 90);
  delay(2000);
  
  robot_straight(2000);
  delay(2000);
  robot_turn('right', 90);
  delay(2000);
  
 
}

int robot_straight (int duration) 
{ 
  myservo.attach(9);
  myservo2.attach(12);
  
  myservo.write(50);
  myservo2.write(150);
  
  delay(duration);
  
  myservo.detach();
  myservo2.detach();
}

int robot_turn (String turnDirection, int turnDegrees) 
{ 
  int val;
  int val2;
  int delayTime = turnDegrees * 6;
  
  if (turnDirection == 'left'){
    val = 1200;
    val2 = 20;  
  } else {
    val = 20;
    val2 = 1200;  
  }
  
  myservo.attach(9);
  myservo2.attach(12);
  myservo.write(val);
  myservo2.write(val2);
  delay(delayTime);
  myservo.detach();
  myservo2.detach();    
}

