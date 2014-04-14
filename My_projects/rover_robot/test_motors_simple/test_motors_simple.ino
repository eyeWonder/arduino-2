
#include <SoftwareSerial.h>
  
  // This does not seem to be a problem useing the same rx pin for both
 SoftwareSerial Maestro(3,5); // pin 5 = TX, pin 3 = RX (unused)

int leftPin = A2;
int rightPin = A1;

int loopCounter = 0;


void setup() {
  
   Maestro.begin(9600);
    delay(500); // wait for display to boot up
  pinMode(A2, OUTPUT);
 digitalWrite(A2, HIGH);
  setTarget(2, 1000);
  delay(5000);
}


void loop() {
  //stop
  setTarget(2, 0);

}


  //Send a Set Target command to the Maestro.
  //Target is in units of quarter microseconds, so the normal range is 4000 to 8000.
  void setTarget(unsigned char servo, unsigned int target) {
    //target = map(target, 1100, 1850, 4000, 8000);
    //target = 2000;
    Maestro.write(0xAA); //start byte
    Maestro.write(0x0C) ; //device id 12
    Maestro.write(0x04); //command number 0x04 = Set Target
    Maestro.write(servo); //servo number
    Maestro.write(target & 0x7F); //target low bits
    Maestro.write((target >> 7) & 0x7F); //target high bits
    
  }
