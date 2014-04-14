#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int KeyPadPin = 4;


char* engTeamHasTalked[] = {"0", "0", "0", "0", "0"};
char* theSpeaker[][4] = 
  {
    {"     Mike    ", "the Magnificent", "da Miscellaneous", "the Mischievous"}, 
    {"   Marissa    ", "the Magical", "the Mysterious", "the Mellifluous"},
    {"    Chris    ", "the Piss", "the Carnivorous", "the Choir Boy"},
    {"    Jason    ", "the Jovial", "the Jester", "the Judicious"},
    {"     Bart    ", "the Brave", "the Berserk", "the Bureaucrat"}
  };


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
       char theSpeakerName; //this will hold the name of the speakers array
   char* personSpeaking = theSpeaker[1][0];
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(personSpeaking);
   //Serial.println(theSpeaker[40]);
 //  Serial.println(mike[0]);
//Serial.println(theSpeaker[1]);
//Serial.println(theSpeaker[2]);
//Serial.println(theSpeaker[3]);
   lcd.setCursor(0,1);
   lcd.print(theSpeaker[1][1]);
  // Serial.println(theSpeaker[1]);
   delay(2000);
   }
   
} 


