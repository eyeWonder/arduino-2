#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int buzzerPin = 8; 
int bigButtonPin = A4;
int bigLedPin =9;
int talkedCounter = 0;
int fiveKeyPadReading = 0;

int hasTalked[] = {0, 0, 0, 0, 0};
char* engTeam[][4] = 
  {
    {"Mike", "the Magnificent", "da Miscellaneous", "the Mischievous"}, 
    {"Marissa", "the Magical", "the Mysterious", "the Mellifluous"},
    {"Chris", "the Piss", "the Carnivorous", "the Choir Boy"},
    {"Jason", "the Jovial", "the Jester", "the Judicious"},
    {"Bart", "the Brave", "the Berserk", "the Bureaucrat"},
    {"Raj", "the Ravenous", "the Reluctant", "the Raucous"}
  };

int theRandomness;
int engTeamLength = 6;

void setup()
{
  Serial.begin( 9600 );
  randomSeed(analogRead(5));
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(bigButtonPin, INPUT);
  pinMode(bigLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}


void loop()
{ 
  if ( digitalRead(bigButtonPin) == HIGH && (talkedCounter == engTeamLength) ) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("go back to work");
    lcd.setCursor(0,1);
    lcd.print("");
    delay(2000);
    talkedCounter++;
    
  } 
  if ( digitalRead(bigButtonPin) == HIGH && (talkedCounter == engTeamLength+1) ) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERIOUSLY");
    lcd.setCursor(0,1);
    lcd.print("go back to work");
    talkedCounter++;
    delay(2000);
  }
  if ( digitalRead(bigButtonPin) == HIGH && (talkedCounter == engTeamLength+2) ) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Reseting");
    for (int i=0; i<engTeamLength; i++) {
      hasTalked[i]=0; 
    }
    talkedCounter = 0;
    delay(2500);
    lcd.clear();
  }  
  
   if ( digitalRead(bigButtonPin) == HIGH && (talkedCounter < engTeamLength) ) {
     
     digitalWrite(bigLedPin, HIGH);
     talkedCounter++;
       Serial.print("talkedCounter ");
       Serial.println(talkedCounter);
       Serial.println();
     showSpeaker();   
     delay(500);
   } else {
     // turn LED off:
     digitalWrite(bigLedPin, LOW); 
   }
  

}

void showSpeaker(){
   //char theSpeakerName; //this will hold the name of the speakers array
   int Rand;
   char* theSpeakerName;
   char* theTitle;  
   lcd.clear();
   
   Rand = makeRandom(0, engTeamLength); //first ranomized speaker
  
     while (hasTalked[Rand] == 1) {  //if the engTeamHasTalked array holds 1 the person has talked
       Rand = makeRandom(0, engTeamLength);//get new random person if that one has talked
       Serial.println(Rand);
     }
   hasTalked[Rand] = 1;

   theSpeakerName = engTeam[Rand][0];
   
  theTitle = engTeam[Rand][random(1, 4)];   
   
  int theNoise = random(1, 3);
  switch(theNoise) {
    case 1:
      chirpChirp();
      break;
    case 2:
      hello();
      break;
  }
   
  lcd.setCursor(0,0);
  lcd.print(theSpeakerName);
  Serial.println(theSpeakerName);
  lcd.setCursor(0,1);
  lcd.print(theTitle);
  Serial.println(theTitle);
  
  for (int i=0; i<engTeamLength; i++) {
   Serial.print(hasTalked[i], DEC);   
  }
  Serial.println();
  delay(1000);    
}


int makeRandom(int lowerLimit, int upperLimit) {
  Serial.print("the value of analog 5 is ");
  Serial.println(analogRead(5));
  Serial.print("the value of talkedCounter ");
  Serial.println(talkedCounter);
//  delay(500);
  return random(lowerLimit, (upperLimit)); 
}


void hello() {
  
   for (int y=0; y<6; y++) {
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(2000-(y*20));//tiny delay
      digitalWrite(buzzerPin, LOW);
      delay(20); //delay between pips      
    }
    for (int v=0; v<25; v++) {
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
    
     for (int z=0; z<7; z++) {
       digitalWrite(buzzerPin, HIGH);
       delayMicroseconds(50-(z*5));//tiny delay
       digitalWrite(buzzerPin, LOW);
       delay(300+z*3); //delay between pips 
     } 
     
}

void chirpChirp() {
   
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
}

void eeeYahPipPipPip() { //this is function makeSomeNoise
    
       for (int y=0; y<6; y++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(60);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(20-y); //delay between pips      
        }
        for (int v=0; v<20; v++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(60);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(8+v); //delay between pips      
        }
        
        for (int i=0; i<9; i++) {
          digitalWrite(buzzerPin, HIGH);
          delayMicroseconds(300);//tiny delay
          digitalWrite(buzzerPin, LOW);
          delay(70); //delay between pips 
        }
    
     for (int z=0; z<6; z++) {
       digitalWrite(buzzerPin, HIGH);
       delayMicroseconds(50-(z*4));//tiny delay
       digitalWrite(buzzerPin, LOW);
       delay(300+z*3); //delay between pips 
     } 
 

}// end of
