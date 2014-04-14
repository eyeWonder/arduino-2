// SparkFun Serial LCD example 1
// Clear the display and say "Hello World!"

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

// Attach the serial display's RX line to digital pin 2
SoftwareSerial LCDserial(3,2); // pin 2 = TX, pin 3 = RX (unused)
char* LCDtext;

void setup()
{
  LCDserial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
}

void loop()
{
  clearLCD();
  LCDtext = "sssarsgaaard";
  LCDserial.write(LCDtext);
  
  while(1); // wait forever
}

void clearLCD() {
  LCDserial.write(0xFE); // move cursor to beginning of first line
  LCDserial.write(1);
  LCDserial.write("                "); // clear display
  LCDserial.write("                ");
}

