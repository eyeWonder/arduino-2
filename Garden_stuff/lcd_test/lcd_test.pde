// include the library code:
#include <SerialLCD.h>
#include <NewSoftSerial.h> //this is a must
 
// initialize the library
SerialLCD slcd(11,12);//this is a must, assign soft serial pins
 
void setup() {
  // set up : 
  slcd.begin();
  // Print a message to the LCD.
  slcd.print("hello, world!");
}
 
void loop() {
  // Turn off the blinking cursor:
  slcd.noBlink();
  delay(1000);
   // Turn on the blinking cursor:
  slcd.blink();
  delay(1000);
}
