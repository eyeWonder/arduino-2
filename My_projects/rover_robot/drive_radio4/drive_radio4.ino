
int startPin = 8; // to initialize the radio pins
int endPin = 13;
int lastReading[18];
int readCount;
char* pinName[] = {"elevator", "aileron", "throttle", "flaps", "aux 3", "rudder"};
int theChangePin;
char* concatOutput = "";
int biggestChange;

int leftPWM = 6;
int leftDirection = A0;
int rightPWM = 5;
int rightDirection = A3;

int radioPWM; //duration of the pulsein from the radio
int turnAmount;

boolean showSerialRadioInfo = true; //show all radio values in the serial monitor
long previousShortMillis = 0; //short interval timer
long shortInterval = 50; // short interval timer
long previousMediumMillis = 0; // medium interval timer
long mediumInterval = 2000; // medium interval timer

  void setup() {
    Serial.begin(9600); 
    
    pinMode(leftDirection, OUTPUT);
    pinMode(rightDirection, OUTPUT);
    for (int count=startPin; count<=endPin; count++) {
      pinMode(count, INPUT);//set pins
      //lastReading[count] = 0; //fill array     
    }
  }
  
  void loop() { 
    unsigned long currentMillis = millis(); 

    // very frequent events 
    if (currentMillis - previousShortMillis > shortInterval) { 
      previousShortMillis = currentMillis; 
      
      move();
    }
    
    // medium frequency events	
    if (currentMillis - previousMediumMillis > mediumInterval) { 
      previousMediumMillis = currentMillis; 
      
      if (showSerialRadioInfo) { printRadioInputs(); }    
      
      
    }

  }
  
  void move() {
    
    radioPWM = pulseIn(10, HIGH);
    
   // if (radioPWM > 1115) { //see if we should move
    
        if (radioPWM > 1500) { //We are moving forward
          //Serial.print(radioPWM);
          //Serial.println(" we are moving forward");
          
          int motorSpeed = map(radioPWM, 1500, 1910, 30, 255);
          //Serial.println(motorSpeed);
      
          digitalWrite(A0, HIGH); //write forward direction to left and right with split cables
          digitalWrite(A3, LOW);
                  
          setMotorSpeeds(motorSpeed);
          
        } else if (radioPWM < 1300) { //We are in reverse
          
         // Serial.print(radioPWM);
         // Serial.println(" we are moving backward");
          
          //we map the input to 150 - 30 to slow it down a bit in reverse
          int motorSpeed = map(radioPWM, 1050, 1299, 150, 30);
        // Serial.println(motorSpeed);
      
          digitalWrite(A0, LOW); //write forward direction to left and right with split cables
          digitalWrite(A3, HIGH);
      
          setMotorSpeeds(motorSpeed);
        
        } else {
          stopMotors(); 
        }
        
//      } else {
//        stopMotors();      
//      }
    

  }
  
  void setMotorSpeeds(int motorSpeed) {
    
       int leftMotorSpeed, rightMotorSpeed;
       
//    Serial.print("raw motor speed ");
//        Serial.println(motorSpeed);
    
      turnAmount = pulseIn(13, HIGH);
      
//         Serial.print("turnAmount ");
//        Serial.println(turnAmount);
    
      if (turnAmount < 1300) { //we ar turning right
      
        // so we reduce the speed of the right track
        int adjustSpeedBy = map(turnAmount, 1050, 1299, motorSpeed, 0);
 
        
        leftMotorSpeed = motorSpeed;
        rightMotorSpeed = motorSpeed - adjustSpeedBy;

        
      } else if (turnAmount > 1550) { //we ar turning left
        
        int adjustSpeedBy = map(turnAmount, 1549, 187 0, 0, motorSpeed);
        
//                 Serial.print("adjustSpeedBy ");
//        Serial.println(adjustSpeedBy);
        
        leftMotorSpeed = motorSpeed - adjustSpeedBy;
        leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
        
        rightMotorSpeed = motorSpeed;
        
        //delay(2000);
//        Serial.print("left motor speed ");
//        Serial.print(leftMotorSpeed);
//        Serial.print("right motor speed ");
//        Serial.println(rightMotorSpeed);
        
      } else { // we are going straight
        leftMotorSpeed = motorSpeed;
        rightMotorSpeed = motorSpeed;
      }
          
      analogWrite(leftPWM, leftMotorSpeed);
      analogWrite(rightPWM, rightMotorSpeed);     
  }
  
  void stopMotors() {
      analogWrite(leftPWM, 0);
      analogWrite(rightPWM, 0);
      Serial.println(" set right left to 0");    
  }
  
  void moveForward() {
    
        Serial.print(radioPWM);
        Serial.println(" we are moving");
        
        int forwardSpeed = map(radioPWM, 1115, 1890, 30, 255);
        Serial.println(forwardSpeed);
    
        digitalWrite(A0, HIGH); //write forward direction to left and right with split cables
        digitalWrite(A3, LOW);
    
        analogWrite(leftPWM, forwardSpeed);
        analogWrite(rightPWM, forwardSpeed);     
    
  }
  
  
  void printRadioInputs() {
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
  }//printRadioInputs
  
  
