#include "pitches.h"

int inPin = 10;

// notes in the melody:
int melody[] = {
  NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_C7, NOTE_B6, 0,
  NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_D6, NOTE_C6, 0,
  NOTE_G6, NOTE_G6, NOTE_G7, NOTE_E6, NOTE_C6, NOTE_C6, NOTE_B6, NOTE_A6, 0,
  NOTE_F6, NOTE_F6, NOTE_E6, NOTE_C6, NOTE_D6, NOTE_C6};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {  
2, 4, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2, 2, 2, 2,
2, 4, 2, 2, 2, 2};

void setup() {

  digitalWrite(inPin, HIGH);   

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 29; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    // change 350 to 1000 to make timing accurate
    int noteDuration = 350/noteDurations[thisNote];
    tone(inPin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);
  }

}

void loop() {
  // just one time through, thanks
}
