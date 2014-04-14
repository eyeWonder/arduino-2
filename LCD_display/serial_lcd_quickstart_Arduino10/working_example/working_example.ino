// SparkFun Serial LCD example 1
// more info here
// https://github.com/jimblom/Serial-LCD-Kit/wiki/Serial-Enabled-LCD-Kit-Datasheet

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, usev
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

// Attach the serial display's RX line to digital pin 2
SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
//char* LCDtext;

void setup()
{
  LCD.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  backlightOn();
}

void loop()
{
  clearLCD();
  LCD.write("sarsgaaard");
  
  delay(1000);
  
  moveToSecondLine();
  LCD.write("b aaard");
  
  delay(1000);
  
  clearLCD();
  LCD.write("bargle sargle");
  
  delay(1000);
  
  moveToSecondLine();
  LCD.write("gargle");
  
  while(1); // wait forever
}

void clearLCD() {
  LCD.write(0xFE); //command flag
  LCD.write(0X01); // clear command
}

void moveToSecondLine() {
  LCDgoTo(16); //move to function position 16 is the first position on the second line
}

void backlightOn() {
  LCD.write(0x80); //command flag
  LCD.write(0x9D);//157 about half brightness
}

void backlightOff(){  //turns off the backlight
  int zero = 0; //using a variable because I get an error when useing an literal integer
  LCD.write(0x80);   //command flag for backlight stuff
  LCD.write(zero);    //light level for off.
}

void LCDgoTo(int position) 
{ //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
  if (position<32){ 
    LCD.write(0xFE); //command flag
    LCD.write(0X80); // set cursor position command
    LCD.write(position);  // cursor position
  } 
  else { LCDgoTo(0); }
}


