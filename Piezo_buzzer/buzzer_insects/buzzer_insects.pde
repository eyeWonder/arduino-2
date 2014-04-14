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
  
  for (int q=0; q<4; q++) {  
     for (int t=0; t<2; t++) { 
        
       for (int y=0; y<15; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(300);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(25); //delay between pips      
        }
        
        for (int i=0; i<18; i++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(300);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(60); //delay between pips 
        }
     }
     for (int z=0; z<8; z++) {
       digitalWrite(buzzerPin, HIGH);
       delayMicroseconds(300);//tiny delay
       digitalWrite(buzzerPin, LOW);
       delay(300); //delay between pips 
     } 
     delay(900);
  }
  

}// end of makeSomeNoise()
