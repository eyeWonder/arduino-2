
  void setup() {
    Serial.begin(9600); 
    
    for (int count=8; count<14; count++) {
      pinMode(count, INPUT);
    }
  }
  
  void loop() {    
    for (int count=8; count<14; count++) {
      int duration = pulseIn(count, HIGH);
      String pinReading = "Pin ";
      pinReading = pinReading + count + " " + duration + "  |  "; 
      Serial.print(pinReading);
    }
    Serial.println("");
    delay(1000);
  }
  
  
  

