//This Program will detect an object moving toward a Ping sensor NOT
//away from it or or an object that is stationary.
//When the progam starts it waits eight seconds before it starts watching.
//It also waits 8 seconds between each trigger event so it doesn't happen repeatedly.

  
  #include <Servo.h>
  int buzzerPin = 9; 
  
  const int pingPin = A5;
  long duration, inches, cm, lastTrigger=millis(), timeNow = millis();
    
  //turn on and off the serial print 
  boolean debug = 1;
  
  //basePing holds the changing ping distance so we can check if things are getting closer
  // this should be set a little closer than the furthest the ping can see in the enviornment you are in
  // Example: if a wall is 50in. away set it for 
  // 45in. so when something comes between the sensor and the wall you will see a change  
  // manually entering this is easier than writing a calibration routine
  int resetBasePingDist = 80; 
  int basePingDist = resetBasePingDist;
  int nowCloser = 0;
  
void setup() {
  if (debug == 1) {
    // initialize serial communication:
    Serial.begin(9600);
    pinMode(buzzerPin, OUTPUT);
  }
}

void loop()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
 
  //check to see if the reading is closer and 
  //checks if the variable nowCloser is 0 so this only gets run once per target sighting
  //check that we are a certain amount of time from the last trigger event so it doen't trigger repeatedly
  //sets timeNow so we can see if these events happend withing a certain time
  //updates the basetPingDist variable to the new closer value to compare next time
  //increments the nowCloser variable so we can check later if the object keeps getting closer
  //you can change inches+2 to inches+1 to make it more sensitive to changing values
  if ( inches+2 < basePingDist && nowCloser == 0 && millis()-lastTrigger > 8000) {
    timeNow = millis();
    basePingDist = inches;
    nowCloser++;
  }
  
  //this conditional is almost exactly like the one above but has the
  //millis()-timeNow < 2000 statemant so we can test if it got closer again within 2 seconds
  // we update timeNow, basePingDist and nowCloser again
  if ( inches+2 < basePingDist && millis()-timeNow < 2000  && millis()-lastTrigger > 8000 ) {
    timeNow = millis();
    basePingDist = inches;
    nowCloser++;
    if (debug == 1) {
      Serial.print("inches   ");Serial.println(inches+2);  
      Serial.print("pingDist ");Serial.println(basePingDist); 
      Serial.print("closer increment ");  
      Serial.println(nowCloser);
    }
  } 
  
  //if the timeNow is greater than 2 seconds we did not get as many events as
  // we needed to do the trigger event so reset the variable and start watching again.
  if ( millis()-timeNow > 2000 && nowCloser > 0) { //stopped getting closer within time limit
    nowCloser = 0; //reset the closer variable 
    basePingDist = resetBasePingDist; //reset basPingDist back out.
  }
  
  //if we get as many nowCloser events as we need then do the trigger and
  //reset the variables
  if (nowCloser >= 4) {//object has gotten closer a few times so trigger
    if (debug == 1) {
      Serial.println("---------the trigger has fired----------");
      playDetect();
    }
    lastTrigger=millis();//reset variable after the trigger event
    basePingDist = resetBasePingDist;
    nowCloser = 0;  
  }
  
  //debug serial prints 
  if (debug == 1) { //this variable is set manually at the top of the program
    // for debuging - lets you know when wait between triggers is reached
    if ( millis()-lastTrigger > 8000) {
      Serial.println("Wait time reached, go");
    }
    
    //for debug - when sensor does not pick up anything closer
    // it reverts to showing inches
    if ( nowCloser == 0 ){
      Serial.print(inches);
      Serial.print(" in.");
      Serial.println();
    }
  }
  
  delay(100);
}

long microsecondsToInches(long microseconds){
  return microseconds / 74 / 2;
}

void playDetect() {
    Serial.println("---------playdetect----------");
   
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


