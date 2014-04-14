#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int KeyPadPin = 4;
char* engTeam[5] = {"mike", "marissa", "chris", "jason", "bart"};
char* engTeamHasTalked[] = {"0", "0", "0", "0", "0"};
char* mike[] = {"     Mike    ", "the Magnificent", "da Miscellaneous", "the Mischievous"};
char* marissa[] = {"   Marissa    ", "the Magical", "the Mysterious", "the Mellifluous"};
char* chris[] = {"    Chris    ", "the Piss", "the Carnivorous", "the Choir Boy"};
char* jason[] = {"    Jason    ", "the Jovial", "the Jester", "the Judicious"};
char* bart[] = {"     Bart    ", "the Brave", "the Berserk", "the Bureaucrat"};

int theRandomness;
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
     
     showSpeaker();
   } 

 // lcd.clear();
 // Serial.println(fiveKeyPadReading, DEC);

 // lcd.print( fiveKeyPadReading );
  
 // delay(500);
  
//  lcd.clear();
}

void showSpeaker(){
   char theSpeakerName; //this will hold the name of the speakers array
   char* speakerArray[] = theSpeakerName[];
   lcd.clear();
   int engTeamRand = makeRandom(0, engTeamLength);
   for (int i=0; i<=engTeamLength; i++) {
     
     while (engTeamHasTalked[engTeamRand] == "1") {  //if the engTeamHasTalked array holds 1 the person has talked
       engTeamRand = makeRandom(0, engTeamLength);
     }
     
     theSpeaker = engTeam[engTeamRand]; //this will now hold the name of the speakers array
   } 
   
   lcd.setCursor(0,0);
   lcd.print(theSpeaker[0]);
   Serial.println(theSpeaker[40]);
   Serial.println(mike[0]);
//Serial.println(theSpeaker[1]);
//Serial.println(theSpeaker[2]);
//Serial.println(theSpeaker[3]);
   lcd.setCursor(0,1);
   lcd.print(theSpeaker[1]);
   Serial.println(theSpeaker[1]);
   delay(2000);
}

int makeRandom(int lowerLimit, int upperLimit) {
  random(lowerLimit, (upperLimit+1));
}
