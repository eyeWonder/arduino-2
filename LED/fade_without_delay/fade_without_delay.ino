unsigned long time;
int interval = 30;
unsigned long futureTime = time + interval;

boolean fadeUp = true;
int fadeValue = 0;
int ledPin = 6;    // LED connected to digital pin 6

void setup()  { 
  // nothing happens in setup 
} 

void loop()  { 
  time = millis();
  if (time >= futureTime) {
    futureTime = time + interval;
    fadeLED();       
  } 
}

void fadeLED() {
 if ( fadeUp && (fadeValue <= 251) ){
   fadeValue += 4; 
 } else {
   fadeUp = false;
   fadeValue -= 6;
 }
 analogWrite(ledPin, fadeValue);
 
 if (fadeUp == false && (fadeValue <= 5)){
   fadeUp = true; 
 }
 Serial.println(fadeValue);
  
}
