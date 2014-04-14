//~~~~ This will set the servo postion using the serial monitor.

//~~~~NOTE: For this to work correctly you must have "no line ending" selected in the dropdown on the bottom
//~~~~of the Serial monitor. If you don't an extra \n is added and parsed into a "0" alternately you could
//~~~~use parseFloat() because that will leave non number characters behind
//~~~~ but you will also have to do junk=serial.read() to clear the buffer before you can read again.

// turn servo left 60 right 110
// open servo 62 open 180 close



#include <Servo.h> 
int pos; // servo position
Servo myservo;  // create servo object to control a servo 

void setup(){
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600); // Sets up communication with the serial monitor
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only  
  instructions();
}//end setup

void loop(){
  if (Serial.available()>0) { // Checks for a character in the serial monitor 
    pos = Serial.parseInt();

    myservo.write(pos);  // tell servo to go to position in variable 'pos' 
    delay(1500); //give the servo a second to get there
    
    Serial.print("your servo position is ");
    Serial.println(pos);
    Serial.println("");
    
    instructions();
  }
  
}//end loop

void instructions(){
    Serial.println("Enter a value from 0 to 180 to set the servo position");
    Serial.println("");
}//end instructions
