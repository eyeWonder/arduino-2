
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object 2
 
int val = 600;    // set value 
//int val2 = 10;    // set value 2  
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
//  myservo2.attach(12);  // attaches the servo on pin 10 to the servo object 
  
} 
 
void loop() 
{ 
  myservo.attach(9);
 myservo.write(val);                  // sets the servo position according to the scaled value 
// myservo2.write(val2);
 
 delay(5000);
 myservo.detach();
// myservo.write(95); 
delay(5000); // sets the servo position according to the scaled value 

// myservo2.write(0);
 
 while (1) {}
} 
