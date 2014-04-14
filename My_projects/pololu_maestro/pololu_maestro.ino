    #include <SoftwareSerial.h>
    #define txPin 5
    #define rxPin 3

  SoftwareSerial mySerial(rxPin, txPin);
    
    void setup() {                
      mySerial.begin(9600);
      sdelay(1000);    
    }
    
    void loop() {
     delay(1500);
     settarget(0, 10);
     settarget(1, 10);
     settarget(2, 10);
     settarget(3, 10);
     //settarget(5, 10); ports 5 & 6 are glitching
     delay(1500);
     settarget(0, 140);
     settarget(1, 140);
     settarget(2, 140);
     settarget(3, 140);
     //settarget(5, 140); ports 5 & 6 are glitching

      
      
    }
    
    //Send a Set Target command to the Maestro.
//Target is in units of quarter microseconds, so the normal range is 4000 to 8000.
    void settarget(unsigned char servo, unsigned int target)
    {
      target = map(target, 0, 180, 4000, 8000);
      mySerial.write(0xAA); //start byte
      mySerial.write(0x0C) ; //device id 12
      mySerial.write(0x04); //command number
      mySerial.write(servo); //servo number
      mySerial.write(target & 0x7F);
      mySerial.write((target >> 7) & 0x7F);
    }
