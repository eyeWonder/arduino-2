#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int KeyPadPin = 4;
char* myWords[] = {"One", "Two", "Three"};
char* engTeam[] = {"Mike the Magnigicent", "Marissa the Magical",  "Chris the Piss", "Jason the Jovial", "Bart the Brave"};
int engTeamLength = 5;

void setup()
{
  Serial.begin( 9600 );
  lcd.begin(16, 2);
 
  lcd.clear();
}

int fiveKeyPadReading = 0;

void loop()
{
  fiveKeyPadReading = analogRead( KeyPadPin );
  
   if (fiveKeyPadReading > 1000) {
     Serial.println(engTeam[0]);
     delay(3000);
   } 

  lcd.setCursor(0,0);
  lcd.clear();
  Serial.println(fiveKeyPadReading, DEC);
  
  
  lcd.print( fiveKeyPadReading );
  
  delay(500);
  
  lcd.clear();
}

