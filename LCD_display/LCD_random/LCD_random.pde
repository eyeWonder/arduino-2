#include <SoftwareSerial.h>

#define txPin 12

SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin

int randPos, randConsonant, randVowel, randFreq;
char consonant[] = "bBcCdDfFgGhHjJkKlLmMnNpPrRsStTVwWZ";
char vowel[] = "aAeEiIoOuUY";

void setup(){
  pinMode(txPin, OUTPUT);
  LCD.begin(9600);
  clearScreen();
  randomSeed(4);
}

void loop(){
  randPos = random(0, 32);
  randFreq = random(0, 11); 
  randConsonant = random(0, 35);
  randVowel = random(0, 12);

  LCD.print(0xFE, BYTE);   //command flag
  LCD.print(0x80, BYTE);   //command flag
  LCD.print(randPos, BYTE);    //position
  
  if (randFreq < 6) {
   LCD.print(vowel[randVowel]);
  } else {
   LCD.print(consonant[randConsonant]); 
  }

  delay(200); 
}

/******************** Helper functions *******************************/
void clearScreen(){   //a general function to call the command flag for issuing all other commands   
  LCD.print(0xFE, BYTE);
  LCD.print(0x01, BYTE);
  delay(10);
  LCD.print(0xFE, BYTE);
  LCD.print(0x0C, BYTE);
}

