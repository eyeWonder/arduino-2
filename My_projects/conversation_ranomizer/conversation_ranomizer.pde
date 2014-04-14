#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int KeyPadPin = 4;
int numPlays = 0;
int fiveKeyPadReading = 0;

int hasPlayed[] = {0, 0, 0, 0};
char* players[][1] = 
  {
    {"Mike", "0"}, 
    {"Sarah", "0"},
    {"Veronica", "0"},
    {"Bill", "0"}
  };
  
char* topics[][5] = 
  {
    {"Commercial fishing", "Where the man", "Radiohead - Lotus", "Libya and", "Radishes"},
    {"fishing", "touched you", "Flower video", "Gaddafi", ""}'
    {"0", "0", "0", "0", "0"}    
  };
int theRandomness;
int numPlayers = 4;
int numTopics = 5;

void setup()
{
  Serial.begin( 9600 );
  randomSeed(analogRead(5));
  lcd.begin(16, 2);
  lcd.clear();
}


void loop()
{
  fiveKeyPadReading = analogRead( KeyPadPin );
  
   if ( (fiveKeyPadReading > 1000) && (numPlays < numPlayers) ) {
     
     numPlays++;
       Serial.print("numPlays ");
       Serial.println(numPlays);
       Serial.println();
     showSpeaker();
     //boolean resetHasTalked = 1;
//     check to see if all are set to 1
//     if so 
//       give go back to work message
//       set reset to true
//       call itself again 
//       reset hasTalked
//     else
//    call showSpeaker() 
     
     
   } 
   
}

void showSpeaker(){
   //char theSpeakerName; //this will hold the name of the speakers array
   int RandPlayer;
   int RandTopic;
   char* thePlayerName;
   char* theTitle;  
   lcd.clear();
   
   RandPlayer = makeRandom(0, numPlayers); //first ranomized speaker
   RandTopic = makeRandom(0, numTopics); //first ranomized speaker
  
     while (hasPlayed[RandPlayer] == 1) {  //if the engTeamHasTalked array holds 1 the person has talked
       RandPlayer = makeRandom(0, numPlayers);//get new random person if that one has talked
       Serial.println(RandPlayer);
       delay(500);
     }
   hasPlayed[RandPlayer] = 1;

   
   thePlayerName = players[RandPlayer][0];
  // theSpeakerName = engTeam[0][0]; 
  
  
  char* theTopic = topics[0][random(0, 5)];
  // theTitle = engTeam[0][random(1, 4)];
   //Serial.println( engTeam[Rand][random(1, 4)] );
   
   
  lcd.setCursor(0,0);
  lcd.print(thePlayerName);
  Serial.println(thePlayerName);
  lcd.setCursor(0,1);
  lcd.print(theTopic);
  Serial.println(theTopic);
  
  for (int i=0; i<5; i++) {
   Serial.print(hasPlayed[i], DEC);   
  }
  Serial.println();
  delay(200);
}

int makeRandom(int lowerLimit, int upperLimit) {
  Serial.print("the value of analog 5 is ");
  Serial.println(analogRead(5));
  delay(500);
  return random(lowerLimit, (upperLimit)); 
}
