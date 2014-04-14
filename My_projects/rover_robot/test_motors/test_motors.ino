
#include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
 SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)

int leftPin = A0;
int rightPin = A1;

int loopCounter = 0;


void setup() {
  
   Maestro.begin(9600);
    delay(500); // wait for display to boot up
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  
  
}


void loop() {
  
  
 digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  setTarget(2, 1400);
 setTarget(3, 1400);
  
  delay(2000);
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  
  delay(2000);
  
  loopCounter++;
  
  if (loopCounter > 2) {
     while(1){}// do nothing forever 
  } 
}


  //Send a Set Target command to the Maestro.
  //Target is in units of quarter microseconds, so the normal range is 4000 to 8000.
  void setTarget(unsigned char servo, unsigned int target) {
    target = map(target, 1100, 1850, 4000, 8000);
    //target = 2000;
    Maestro.write(0xAA); //start byte
    Maestro.write(0x0C) ; //device id 12
    Maestro.write(0x04); //command number 0x04 = Set Target
    Maestro.write(servo); //servo number
    Maestro.write(target & 0x7F); //target low bits
    Maestro.write((target >> 7) & 0x7F); //target high bits
    
  }
