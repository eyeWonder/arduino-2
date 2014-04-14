
int startPin = 8;
int endPin = 13;
int lastReading[18];
int readCount;
char* pinName[] = {"elevator", "aileron", "throttle", "flaps", "aux 3", "rudder"};
int theChangePin;
char* concatOutput = "";
int biggestChange;

  void setup() {
    Serial.begin(9600); 
    
    for (int count=startPin; count<=endPin; count++) {
      pinMode(count, INPUT);//set pins
      lastReading[count] = 0; //fill array     
    }
  }
  
  void loop() {    
    biggestChange = 0;
    for (readCount=startPin; readCount<=endPin; readCount++) {
      int duration = pulseIn(readCount, HIGH);

      int change = duration - lastReading[readCount];
      change = abs(change);
      lastReading[readCount] = duration;
      
      if (change > biggestChange) {
        biggestChange = change;
        theChangePin = readCount; 
      }
      
      String pinReading = "Pin ";
      if (duration == 0) {
        pinReading = pinReading + readCount + " 0000  |  ";   
      } else {
        pinReading = pinReading + readCount + " " + duration + "  |  "; 
      }
      Serial.print(pinReading);
    }
     
    Serial.print("Biggest change ");
    Serial.print(biggestChange);
    Serial.print(" on pin ");    
    Serial.print(theChangePin);
    Serial.print("  ");
    Serial.println(pinName[(theChangePin-startPin)]);

    delay(1000);
  }
  
  
  

