#include <SoftwareSerial.h>

#define SerInToArdu 2
#define SerOutFrmArdu 3
int count =100;
SoftwareSerial mySerialPort(SerInToArdu,SerOutFrmArdu);

void setup(){
 pinMode(SerOutFrmArdu,OUTPUT);
 mySerialPort.begin(9600);
 mySerialPort.print("v");
 
}

void loop(){
    count--;
    mySerialPort.write(0x76);
    mySerialPort.print("");
    mySerialPort.print(count);
    delay(1000);
   if (count < 1 )Reset();
}
 
 
 void Reset(){
   mySerialPort.write(0x76);
   mySerialPort.print("DEAD");
   count = 120;
   delay(2000);
 }

