m #include <SoftwareSerial.h>

#define txPin 2

SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin

int randPos, randLetter, randFreq;
char* letterChance;
char space[] = ".";


void setup(){
  pinMode(txPin, OUTPUT);
  LCD.begin(9600);
  clearScreen();
  randomSeed(analogRead(0));
}

void loop(){
  randPos = random(0, 32);
  randFreq = random(3, 21); 
  randLetter = random(0, 130);
  
  //0 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 array postion
  //a b  c  d  e  f  g  H  I  k  l  m  n  o  p  r  s  t  u  v  w  y data
  //8 10 13 17 30 32 34 40 47 48 52 55 62 70 72 78 84 93 96 97 99 101 perentage out of 101
  if (randLetter < 8) {
    letterChance = "A";
  } else if (randLetter < 10) {
    letterChance = "B";
  } else if (randLetter < 13) {
    letterChance = "C";
  } else if (randLetter < 17) {
    letterChance = "D";
  } else if (randLetter < 30) {
    letterChance = "E";
  } else if (randLetter < 32) {
    letterChance = "F";
  } else if (randLetter < 34) {
    letterChance = "G";
  } else if (randLetter < 40) {
    letterChance = "H";
  } else if (randLetter < 47) {
    letterChance = "I";
  } else if (randLetter < 48) {
    letterChance = "K";
  } else if (randLetter < 52) {
    letterChance = "L";
  } else if (randLetter < 55) {
    letterChance = "M";
  } else if (randLetter < 62) {
    letterChance = "N";
  } else if (randLetter < 70) {
    letterChance = "O";
  } else if (randLetter < 72) {
    letterChance = "P";
  } else if (randLetter < 78) {
    letterChance = "R";
  } else if (randLetter < 84) {
    letterChance = "S";
  } else if (randLetter < 93) {
    letterChance = "T";
  } else if (randLetter < 96) {
    letterChance = "U";
  } else if (randLetter < 97) {
    letterChance = "V";
  } else if (randLetter < 99) {
    letterChance = "W";
  } else if (randLetter < 101) {
    letterChance = "Y";
  } 
  //letterChance = letterChance.toUpperCase();
  LCD.print(0xFE, BYTE);   //command flag
  LCD.print(0x80, BYTE);   //command flag
  LCD.print(randPos, BYTE);    //position
  
  if (randLetter > 101 && randPos > 3 && randPos < 13 || randLetter > 101 && randPos > 19 && randPos < 29) {   
    LCD.print(' ');
    //LCD.print(letterChance);    
  } else {
    //LCD.print(space[0]); 
    LCD.print(letterChance); 
  }
  if (millis() < 3000) {
    delay(100);
  } else { 
    delay(300);
  }
   
}

/******************** Helper functions *******************************/
void clearScreen(){   //a general function to call the command flag for issuing all other commands   
  LCD.print(0xFE, BYTE);
  LCD.print(0x01, BYTE);
  delay(10);
  LCD.print(0xFE, BYTE);
  LCD.print(0x0C, BYTE);
}

