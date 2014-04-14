/*
  Pitch follower
 
 Plays a pitch that changes based on a changing analog input

 
 */
 long lastTimed = millis();
 int sensorReading;
void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A2);
  // print the sensor reading so you know its range
  if ( millis()-lastTimed >= 50 ) {
    monitorVizual();
  }
  // map the pitch to the range of the analog input.
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  //int thisPitch = map(sensorReading, 0, 1022, 100, 1000);
  // play the pitch:
  // tone(8, thisPitch, 10);

}

void monitorVizual() {
  //this will get the sensor reading and display it with a text representaion of the value
  // using the switchcase is faster than the for loop because it does not have to loop through 1000 stars when the
  // reading is large. I just stick 0 through 9 stars on the end to represent the multiples of ten ie *** == 30.
    sensorReading = analogRead(A2);
    int modStars;
    int stars = sensorReading / 100;
    
    if (sensorReading < 100) { //then we want the a 0...9 value of the multiples of 10 ie. 37 = 3 or 52 = 5
      modStars = sensorReading / 10;
    } else { // if the reading is over 100 we still want multiples of ten so we devide by 10 and take the remainder
      modStars = sensorReading % 10;
    }
    String theStars;
    
    switch(stars) {
    case 1:
      //theStars += "**********";
      theStars += "ONE HUNDRED ";// using words instead of stars because it more fun and easier to read
      break;
    case 2:
      //theStars += "********************";
      theStars += "One TWO HUNDRED ";
      break;
    case 3:
      //theStars += "******************************";
      theStars += "One Two THREE HUNDRED ";  
      break;
    case 4:
      //theStars += "****************************************";
      theStars += "One Two Three FOUR HUNDRED ";
      break;
    case 5:
      //theStars += "**************************************************";
      theStars += "One Two Three Four FIVE HUNDRED ";
      break;
    case 6:
      //theStars += "************************************************************";
      theStars += "One Two Three Four Five SIX HUNDRED ";
      break;
    case 7:
     // theStars += "**********************************************************************";
     theStars += "One Two Three Four Five Six SEVEN HUNDRED ";
      break;
    case 8:
      //theStars += "********************************************************************************";
      theStars += "One Two Three Four Five Six Seven EIGHT HUNDRED       ";
      break;
    case 9:
      //theStars += "******************************************************************************************";
      theStars += "One Two Three Four Five Six Seven Eight NINE HUNDRED ";
      break;
   case 10:
      //theStars += "****************************************************************************************************";
      theStars += "One Two Three Four Five Six Seven Eight Nine ONE THOUSAND ";
      break;   
     
    }
  
    for (int i=0; i<modStars; i++) {
      theStars += '*';
    }
    Serial.print(sensorReading);
    Serial.print(" " + theStars);
    Serial.println(' ');
    lastTimed = millis();
       
}
