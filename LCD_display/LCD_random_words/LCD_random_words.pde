#include <SoftwareSerial.h>

#define txPin 2

SoftwareSerial LCD = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin

int randPos, randConsonant, randVowel, randFreq, lowerLetter;
char consonant[] = "BCDFGHJKLMNPRSTVWZ";
char vowel[] = "AEIOUY";

void setup(){
  pinMode(txPin, OUTPUT);
  LCD.begin(9600);
  clearScreen();
  randomSeed(analogRead(0));
}

void loop(){
  randPos = random(0, 32);
  randFreq = random(0, 21); 
  randConsonant = random(0, 17);
  randVowel = random(0, 6);

  LCD.print(0xFE, BYTE);   //command flag
  LCD.print(0x80, BYTE);   //command flag
  LCD.print(randPos, BYTE);    //position
  
  if (randFreq < 12) {
    if (randFreq < 5 && randPos > 3 && randPos < 13 || randFreq < 5 && randPos > 19 && randPos < 29 ) {
     // lowerLetter = vowel[randVowel].toLowerCase();
      LCD.print(' ');
    }else {
      LCD.print(vowel[randVowel]);
    }
  } else {
   LCD.print(consonant[randConsonant]); 
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

