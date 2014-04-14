#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object 2

 
//int val = 1200;    // set value 
//int val2 = 10;    // set value 2  
 
void setup() 
{ 
 // myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
//  myservo2.attach(12);  // attaches the servo on pin 10 to the servo object 
  
} 
 
void loop() 
{ 
 robot_straight(3000);
 robot_turn('right', 90);
 
  
}

int robot_straight (int duration) 
{ 
  int delayTime = turnDegrees * 10;
  
  myservo.attach(9);
  myservo2.attach(12);
  
  myservo.write(1200);
  myservo2.write(1200);
  
  delay(duration);
  
  myservo2.detach();
  myservo2.detach();
 
}

int robot_turn (String turnDirection, int turnDegrees) 
{ 
  int val;
  int val2;
  int delayTime = turnDegrees * 10;
  
  if (turnDirection == 'right'){
    myservo.attach(9);
    val = 1200;
    myservo.write(val);
    delay(delayTime);
    myservo2.detach();  
  }
 
  if (turnDirection == 'left'){   
    myservo.attach(12);
    val2 = 1200;
    myservo.write(val2);
    delay(delayTime);
    myservo2.detach();
  }    
}

int robot_straight (duration) 
{ 
  int delayTime = turnDegrees * 10;
  
  myservo.attach(9);
  myservo2.attach(12);
  
  myservo.write(1200);
  myservo2.write(1200);
  
  delay(duration);
  
  myserv2.detach();
  myservo2.detach();
 
}




