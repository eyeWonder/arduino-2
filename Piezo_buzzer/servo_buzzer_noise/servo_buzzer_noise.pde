#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(10,11,12,13,14,15,16);

Servo myservo1;
int KeyPadPin = 4;
int buzzerPin = 8; 
int fiveKeyPadReading = 0;


void setup()
{
  Serial.begin( 9600 );
  randomSeed(analogRead(5)); 
  pinMode(A2, OUTPUT);  
  pinMode(buzzerPin, OUTPUT);
}


void loop()
{
  fiveKeyPadReading = analogRead( KeyPadPin );
  
   if ( (fiveKeyPadReading > 1000) ) { 
     makeNoise();   
   }   
}



int makeNoise() {
  Serial.print("the value of analog 5 is ");
 
  myservo1.attach(9);
  for (int i=0; i<4; i++) {
    int noiseRand = random(0, 15);
    int delayServo = map(noiseRand, 0, 15, 100, 300);
    
    myservo1.write(50);  
    delay(delayServo);
    myservo1.write(150);
    
    for (int i=0; i<9; i++) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(A2, HIGH);   // set the LED on
      delayMicroseconds(300);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(A2, LOW);
    }
    delay(200);  
  }
  
  digitalWrite(A2, HIGH);   // set the LED on 
  digitalWrite(buzzerPin, HIGH);  
  delay(25);
  digitalWrite(buzzerPin, LOW);
  delay(250);
  digitalWrite(A2, LOW);
    
  myservo1.detach(); 
}
