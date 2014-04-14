#include <SoftwareSerial.h>

#define txPin 19


SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin

const int pingPin = 14;

void setup()
{
Serial.begin(9600);

pinMode(txPin, OUTPUT);
LCD.begin(9600);
clearScreen();
  
}

void loop() {
  

   // establish variables for duration of the ping, 
  // and the distance result in inches:
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  
  clearScreen();
  selectLineOne();
  delay(100);
 LCD.print("INCHES ");
 // selectLineTwo();
  //delay(100);
  LCD.print(inches);
  //delay(100); 
  
  Serial.println(inches);
  
  delay(500);
 }
 
long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}
 
 
 
/********************LCD Helper functions *******************************/

void selectLineOne(){  //puts the cursor at line 0 char 0.
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(0x80, BYTE);   //command flag
   LCD.print(0, BYTE);    //position
}

void selectLineTwo(){  //puts the cursor at line 0 char 0.
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(0x80, BYTE);   //command flag
   LCD.print(16, BYTE);    //position
}

void goTo(int position) 
{ //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
  if (position<16){ 
      LCD.print(0xFE, BYTE);   //command flag
      LCD.print((position+128), BYTE);    //position
  }
  else if (position<32){
       LCD.print(0xFE, BYTE);   //command flag
       LCD.print((position+48+128), BYTE);    //position 
  }
  else { goTo(0); }
}

void clearLCD(){
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(0x01, BYTE);   //clear command.
}

void backlightOn(){  //turns on the backlight
    LCD.print(0x7C, BYTE);   //command flag for backlight stuff
    LCD.print(157, BYTE);    //light level.
}

void backlightOff(){  //turns off the backlight
    LCD.print(0x7C, BYTE);   //command flag for backlight stuff
    LCD.print(128, BYTE);     //light level for off.
}

void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.print(0xFE, BYTE);
}

void clearScreen(){   //a general function to call the command flag for issuing all other commands   
  LCD.print(0xFE, BYTE);
  LCD.print(0x01, BYTE);
  delay(10);
  LCD.print(0xFE, BYTE);
  LCD.print(0x0C, BYTE);
}

void clearSecondLine(){   //have not tested this  
  LCD.print(0xFE, BYTE);
  LCD.print(0x0C, BYTE);
}
