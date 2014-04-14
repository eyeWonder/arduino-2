
  void setup() {
    Serial.begin(9600); 
    
    pinMode(A0, OUTPUT);
    pinMode(A3, OUTPUT);
     
     
    ////Write forward direction to left and right with split cables
    ////On each side of the rover the motors are mounted in oposite directions so they rotate in oposite directions by default 
    digitalWrite(A0, HIGH); // ch1 and ch3 forward
    digitalWrite(A3, LOW);  // ch2 and ch4 forward

    //digitalWrite(A0, LOW); // ch1 and ch3 reverse
    //digitalWrite(A3, HIGH);  // ch2 and ch4 reverse   
   
    analogWrite(6, 255); // ch1 and ch2 speed Left side
    analogWrite(5, 60); // ch2 and ch4 speed Right side

  }
  
  void loop() { 

    delay(5000);
    analogWrite(6, 0);
    analogWrite(5, 0);

    
    
  }
  

  
  

  
  
