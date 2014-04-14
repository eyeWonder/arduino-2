#include <LiquidCrystal.h>

LiquidCrystal lcd(10,11,12,13,14,15,16);

int KeyPadPin = 4;
int numPlays = 0;
int fiveKeyPadReading = 0;

int hasPlayed[] = {0, 0, 0, 0};
char* intro[][2] = 
  {
    {"Talk about", "0"}, 
    {"Discuss", "0"},
    {"Whats up with", "0"},
    {"Tell us about", "0"}
  };
  
char* topics[][5] = 
  {
    {"Commercial", "Where the man", "Radiohead -", "Libya and", "Radishes"},
    {"fishing", "touched you", "Lotus Flower vid", "Gaddafi", ""},
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
     showTopic();
     //boolean resetHasTalked = 1;
//     check to see if all are set to 1
//     if so 
//       give go back to work message
//       set reset to true
//       call itself again 
//       reset hasTalked
//     else
//    call showSpeaker()      
     
   } else if (numPlays >= (numTopics-1)) {      //reset topic array
     for (int t=0; t<numTopics; t++) {
       topics[2][t] = "0";
     }
     numPlays = 0;   
   } 
   
}

void showTopic(){
   //char theSpeakerName; //this will hold the name of the speakers array
   int RandPlayer;
   int RandTopic;
   char* thePlayerName;
   char* theTitle;  
   lcd.clear();
   
   RandPlayer = makeRandom(0, numPlayers); //first ranomized speaker
   RandTopic = makeRandom(0, numTopics); //first ranomized speaker
  
     while (topics[2][RandTopic] == "1") {  //if the engTeamHasTalked array holds 1 the person has talked
       RandTopic = makeRandom(0, numTopics);//get new random person if that one has talked  
       Serial.println(RandTopic);
       delay(500);
     }
   topics[2][RandTopic] = "1";

   thePlayerName = intro[RandPlayer][0];
  // theSpeakerName = engTeam[0][0]; 
  
  
  char* theTopic = topics[0][RandTopic];
  char* theTopic2 = topics[1][RandTopic];
  // theTitle = engTeam[0][random(1, 4)];
   //Serial.println( engTeam[Rand][random(1, 4)] );
   
   
  lcd.setCursor(0,0);
  lcd.print(thePlayerName);
  Serial.println(thePlayerName);
  
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(theTopic);
  Serial.println(theTopic);
  lcd.setCursor(0,1);
  lcd.print(theTopic2);
  Serial.println(theTopic2);
  
  
}

int makeRandom(int lowerLimit, int upperLimit) {
//  Serial.print("the value of analog 5 is ");
//  Serial.println(analogRead(5));
//  delay(500);
  return random(lowerLimit, (upperLimit)); 
}
