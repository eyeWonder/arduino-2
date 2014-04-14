
#include <SoftwareSerial.h>

#define SerInToArdu 2
#define SerOutFrmArdu 3
#define setPot A3

unsigned long elapseTime = 2879001;
unsigned long hour;
unsigned long minute;
unsigned long second;


void setup(){

  
  Serial.begin(9600);
  //elapseTime = elapseTime*1000*60*60;
 // elapseTime = elapseTime*3600000;
  
 
      
  
}

void loop(){
  elapseTime = elapseTime - 1000;
  hour = elapseTime / (1000*60*60);
   minute = (elapseTime % (1000*60*60)) / 60000;
   second = ((elapseTime % (1000*60*60)) % 60000) / 1000;
   
   Serial.print("elapseTime ");
  Serial.println(elapseTime);
   
    Serial.print(hour);
    Serial.print(" : ");
    Serial.print(minute);
    Serial.print(" : ");
    Serial.print(second);
    Serial.println("");
   
   
   delay(200);
 
}//end loop



