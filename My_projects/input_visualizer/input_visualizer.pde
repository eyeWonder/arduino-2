/*
  Pitch follower
 
 Plays a pitch that changes based on a changing analog input

 
 */
 long lastTimed = millis();

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A2);
  // print the sensor reading so you know its range
  monitorVizual(sensorReading);
  // map the pitch to the range of the analog input.
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  //int thisPitch = map(sensorReading, 0, 1022, 100, 1000);
  
  
  
  // play the pitch:
// tone(8, thisPitch, 10);

}

void monitorVizual(int reading) {
  if ( millis()-lastTimed >= 20 ) { 
    int stars = reading / 15;
    String theStars = '*';
//    
    for (int i=0; i<stars; i++) {
      theStars += '*';
    }
    Serial.print(reading);
    Serial.print(" " + theStars);
    Serial.println(' ');
    lastTimed = millis();
  }
     
}
