
int KeyPadPin = 4;
int fiveKeyPadReading = 0;
int engTeamLength = 5;
int talkedCounter = 0;

int hasTalked[] = {0, 0, 0, 0, 0};

void setup(){
 Serial.begin( 9600 );
 Serial.println();
  for (int i=0; i<5; i++) {
   Serial.print(hasTalked[i], DEC);   
  }
}

void loop()
{
  
  fiveKeyPadReading = analogRead( KeyPadPin );
  
  Serial.println();
  delay(1500);
  
   //if ( (fiveKeyPadReading > 1000) && (talkedCounter < engTeamLength) ) {
     
     talkedCounter++;
       Serial.print("increment talkedCounter ");
       Serial.println(talkedCounter);
       showSpeaker();
       Serial.println();
     //showSpeaker();
  // } 
   
}

void showSpeaker() {
  hasTalked[2] = 1;
  
  Serial.println();
  Serial.print("inside showSpeaker ");
  
  for (int i=0; i<5; i++) {
   Serial.print(hasTalked[i], DEC);   
  }
  
  Serial.println();
 delay(1500); 
 
 if (hasTalked[4] == 2) {
   hasTalked[4] = 8;   
 }
 
  if (talkedCounter == 4) {
   hasTalked[4] = 2;   
 }
 
 if (talkedCounter == 6) {
   hasTalked[0] = 1;   
 }
  
}
