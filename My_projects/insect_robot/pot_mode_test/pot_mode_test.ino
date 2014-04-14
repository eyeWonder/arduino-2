#include "pitches.h"
int potPin = A0;
int buzzerPin = A4;


int potValue;
boolean modeSet = false;
int mode;
int subMode = 10;
unsigned long currentMillis;
unsigned long nextPrintPotVal = 0;
long modeTimeout;
long modeConfirm;

  int numberOfNotes;
  int noteDuration;
  int melody[12];
  int noteDurations[12];

 
void setup()
{
 Serial.begin(9600);
 currentMillis = millis();
 modeTimeout = currentMillis + 3000; //how long before we beep what mode we are in
 modeConfirm = currentMillis + 5000;
}//end setup

void loop()
{
 //delay(500);
  currentMillis = millis();
   //Serial.println( currentMillis );
  
  if (!modeSet) {
    //check pot set mode
    readPot();
    if (potValue > 819) {
      mode = 5;
    } else if (potValue > 615) {
      mode = 4;
    } else if (potValue > 411) {
      mode = 3;
    } else if (potValue > 207) {
      mode = 2;
    } else {
      mode = 1;
    }
    
    if ( generalDelay(modeTimeout) ) {
      modeSet = true;
      beep(mode); // beep what mode I'm in
    }
    if ( generalDelay(modeConfirm) ) {
      
    }
    
    
    
    if ( generalDelay(nextPrintPotVal)  ) {
      nextPrintPotVal = currentMillis + 1000;
      Serial.print("the pot value is ");
      Serial.println(potValue);
    }
    
    
  } else { //mode is now set continue with program
    //
  }// end if mode
    
 
  delay(1);  //time between each step taken, speed of walk
}// end loop


void readPot()
{
  potValue = analogRead(potPin); 
}

//This holds all tht
void beep(int songNumber) {
  
  Serial.print("song number ");
  Serial.println(songNumber);
  
  switch (songNumber) {
    case 1:
      {//mode 1 beep
        int numberOfNotes = 1;
        int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
        int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
        playSong(numberOfNotes, melody, noteDurations);
      }
    break;
    case 2:
      {//mode 1 beep
        int numberOfNotes = 2;
        int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
        int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
        playSong(numberOfNotes, melody, noteDurations);
      }
    break;
    case 3:
      {
        int numberOfNotes = 3;
        int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
        int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
        playSong(numberOfNotes, melody, noteDurations);
      }
    break;
    case 4:
      {//mode 1 beep
       int numberOfNotes = 4;
        int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
        int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
        playSong(numberOfNotes, melody, noteDurations);
      }
    break;
    case 5:
      {//mode 1 beep
        int numberOfNotes = 5;
        int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
        int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };
        playSong(numberOfNotes, melody, noteDurations);
      }
    break;
  }//end switch
  
  
  

}//end beep function


void playSong(int numberOfNotes, int melody[], int noteDurations[]) {
  
  Serial.println("in playSong~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println(numberOfNotes);
  Serial.println(melody[0]);
  Serial.println(noteDurations[0]);
    Serial.println(" before iterate");
  
  
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < numberOfNotes; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(9, melody[thisNote],noteDuration);
    
    Serial.println(melody[thisNote]);
    Serial.println("iterate");

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);
  }
}





//Send this function a next evenEventMillis time and it will 
//return true if it is time to trigger that event 
//if true remember to reset your nextEventMillis variable into the future 
boolean generalDelay(unsigned long nextEventMillis) {
 if( currentMillis >= nextEventMillis) {
   return true;  
 } else {
   return false; 
 }  
}// end generalDelay






