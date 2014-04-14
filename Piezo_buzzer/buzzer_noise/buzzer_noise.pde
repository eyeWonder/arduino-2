#include <Servo.h>


int buzzerPin = 8; 

void setup()
{
  pinMode(buzzerPin, OUTPUT);
}


void loop()
{ 
digitalWrite(buzzerPin, HIGH);
  makeSomeNoise();  
  delay(5000);
}



int makeSomeNoise() { //this is function makeSomeNoise
   
//  for (int s=0; s<4; s++) {  
//    
//    for (int i=0; i<25; i++) {
//      digitalWrite(buzzerPin, HIGH);
//      delayMicroseconds(300);//tiny delay
//      digitalWrite(buzzerPin, LOW);
//      delay(50); //delay between pips 
//    }
//    
//    for (int t=0; t<5; t++) {
//      digitalWrite(buzzerPin, HIGH);
//      delayMicroseconds(300);//tiny delay
//      digitalWrite(buzzerPin, LOW);
//      delay(200); //delay between pips 
//    }
//  }
  
  
  for (int q=0; q<4; q++) {  
    
    for (int y=0; y<25; y++) {
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(300);//tiny delay
      digitalWrite(buzzerPin, LOW);
      delay(25); //delay between pips 
      
    }
    
    for (int z=0; z<4; z++) {
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(300);//tiny delay
      digitalWrite(buzzerPin, LOW);
      delay(300); //delay between pips 
    }
  }
  
//    digitalWrite(buzzerPin, HIGH);   // longer beep
//    delay(25);
//    digitalWrite(buzzerPin, LOW);
  
}// end of makeSomeNoise()
