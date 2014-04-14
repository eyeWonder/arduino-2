/*Photovore
 * ------------------ 
 *turns the robot towards light
 *
 *
 */
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
Servo myservo2;  // create servo object 2

int LDR = 1;       // right photocell
int LDL = 2;       // left  photocell
int val4  = 0;      // variable to store the value coming from the right sensor
int val5 = 1;      // variable to store the value coming from the left sensor



void setup() {
    pinMode(LDR, INPUT);       // declare the LDR as an INPUT
    pinMode(LDL, INPUT);       // declare the LDL as an INPUT 
}



void loop() {
    val4  = analogRead(LDR);       // read the value from the right sensor
    val5 = analogRead(LDL);       // read the value from the left sensor
   
    if (val4 > val5) {
        robot_turn('right', 10);
    } else {
        robot_straight(2000); 
    }
}



int robot_straight(int duration) { 
    myservo.attach(9);
    myservo2.attach(12);
    
    myservo.write(50);
    myservo2.write(150);
    
    delay(duration);
    
    myservo.detach();
    myservo2.detach();
}




int robot_turn(String turnDirection, int turnDegrees) { 
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


