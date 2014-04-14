
#include <SoftwareSerial.h>

SoftwareSerial LCD(3,2); // pin 2 = TX, pin 3 = RX (unused)
//char* LCDtext;
int pan = 11; //ail on reciever
int tilt = 10; // elev on reciever
unsigned long duration;


void setup()
{
  LCD.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  backlightOn();
  pinMode(pan, INPUT);
}

void loop()
{
  clearLCD();
  duration = pulseIn(pan, HIGH); 
  clearLCD();
  LCD.print("pan: ");
  LCD.print(duration);
  moveToSecondLine();
  duration = pulseIn(tilt, HIGH); 
  LCD.print("tilt: ");
  LCD.print(duration);
  
  delay(1000);
  
 
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


