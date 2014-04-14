 //#include "pitches.h"


void setup() {
  randomSeed(analogRead(4));
   mouseSqueek2();
   delay(1000);
   mouseSqueek();
  //delay(1000);
  //birdChirpUp();
  delay(1000);
  int numTimesCalled = random(2, 4);
  for (int called = 0; called < numTimesCalled; called++) { 
    peep();
  }
}


void mouseSqueek2(){
  for (int squeeks = 0; squeeks < 4; squeeks++) { 
    int thisNote;
   for (thisNote = 0; thisNote < 6; thisNote++) {    
      tone(6, 100, 20);
      delay(30);
      tone(6, 160, 15);
      delay(20);
      tone(6, 26, 40);
      delay(35);  
   }
    delay(25); 
  } 
}
void mouseSqueek(){
  for (int squeeks = 0; squeeks < 4; squeeks++) { 
    int thisNote;
   for (thisNote = 0; thisNote < 6; thisNote++) {    
      tone(6, 100, 20);
      delay(20);
      tone(6, 160, 15);
      delay(20);
      tone(6, 26, 40);
      delay(35);  
   }
    delay(30); 
  } 
}

void birdChirpUp() {
  for (int thisNote = 1000; thisNote < 2500; thisNote++) {
    int highNote = thisNote*1.5;
    float duration = 270 - (thisNote/10);
    tone(6, thisNote, duration);   
    //delay(1);   
    //noTone(6);
  }
}

void peep() {
  
  int totalSqueeks = random(2, 5);
  
  for (int squeeks = 0; squeeks < totalSqueeks; squeeks++) { 
    for (int thisNote = 2900; thisNote < 3500; thisNote++) {
      float duration = 370 - (thisNote/10);//makes the duration shorter the highter the note
      tone(6, thisNote, duration);     
      //noTone(6);
    }
    int extraDelay = random(0, 600);
    delay(200+extraDelay); 
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
