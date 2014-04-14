#include <Servo.h>


int buzzerPin = 8; 

void setup()
{
  pinMode(buzzerPin, OUTPUT);
}


void loop()
{ 

  eeeYahPipPipPip();  
  delay(5000);
  chirpChirp();
  delay(5000);
  hello();
  delay(5000);
 
}


void hello() {
  for (int q=0; q<4; q++) {  
     for (int t=0; t<2; t++) { 
        
       for (int y=0; y<6; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(2000-(y*20));//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(20); //delay between pips      
        }
        for (int v=0; v<35; v++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(150-(v*4));//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(8+v); //delay between pips      
        }
        
        for (int i=0; i<5; i++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(300);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(70); //delay between pips 
        }
     }
     for (int z=0; z<10; z++) {
       digitalWrite(buzzerPin, HIGH);
       delayMicroseconds(50-(z*5));//tiny delay
       digitalWrite(buzzerPin, LOW);
       delay(300+z*3); //delay between pips 
     } 
     delay(3000);
  }
}

void chirpChirp() {
  for (int q=0; q<3; q++) {  
     for (int t=0; t<2; t++) { 
        
       for (int y=0; y<14; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(9000+(y*50));
          digitalWrite(buzzerPin, LOW);
          delay(15); //delay between pips      
        }
        for (int y=0; y<5; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(2000-(y*400));
          digitalWrite(buzzerPin, LOW);
          delay(15+(y*20)); //delay between pips      
        }
        
        
     }
     
     delay(2000);
  }
}

void eeeYahPipPipPip() { //this is function makeSomeNoise
  
  for (int q=0; q<4; q++) {  
     for (int t=0; t<2; t++) { 
        
       for (int y=0; y<6; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(60);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(20-y); //delay between pips      
        }
        for (int v=0; v<40; v++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(60);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(8+v); //delay between pips      
        }
        
        for (int i=0; i<18; i++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(300);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(70); //delay between pips 
        }
     }
     for (int z=0; z<10; z++) {
       digitalWrite(buzzerPin, HIGH);
       delayMicroseconds(50-(z*4));//tiny delay
       digitalWrite(buzzerPin, LOW);
       delay(300+z*3); //delay between pips 
     } 
     delay(3000);
  }
  

}// end of makeSomeNoise()
