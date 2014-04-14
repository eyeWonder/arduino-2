
#include <NewSoftSerial.h>

#define SerInToArdu 2
#define SerOutFrmArdu 3

#define wDelay 600//  Sets how long each "message" appears

NewSoftSerial mySerialPort(SerInToArdu,SerOutFrmArdu);
//  The above creates the serial channel we will use.
long timerDuration = 15; //how long the timer is set for
long timeSet; //holds millis when timers started
int counter;
int theDisplay;
long timeNow;
int seconds;
int minutes;

void setup(){

 pinMode(SerOutFrmArdu,OUTPUT);
 pinMode(SerInToArdu,INPUT);//Not actually needed... put in
 //to be explicit as to data direction over serial lines
 timeNow = millis();
 mySerialPort.begin(9600);
 Serial.begin(9600);

 mySerialPort.print("v");//To reset display module
 mySerialPort.print("xxxx");

 //http://www.arunet.co.uk/tkboyd/ec/ec1led4x7ser.htm

 // DIMMING send 0x7A command then 0 to 254 Higher numbers are dimmer
 mySerialPort.print(0x7A,BYTE);
 mySerialPort.print(200,BYTE);

 timeSet = timerDuration + (millis()/1000);
 counter = timerDuration;
}//end setup()

void loop(){

 if (millis()- timeNow >= 1000) { setDisplay(); }

}

int setDisplay() {  
 counter--;

 if (counter >= 10 ) {
    mySerialPort.print("xx");
    mySerialPort.print(counter);
 } else if (counter >= 0 ) {
    //Serial.println(counter);
    mySerialPort.print("xxx");
    mySerialPort.print(counter);    
 } else {
    //mySerialPort.print("xxxx");
    mySerialPort.print("DONE");
    //while(1){} //traps into endless loop  
 }

 timeNow = millis();
}


 //  mySerialPort.print("1234");
 //  delay(wDelay);
 //  mySerialPort.print("2340");
 //  delay(wDelay);
 //  mySerialPort.print("3400");
 //  delay(wDelay);
 //  mySerialPort.print("4000");
 //  delay(wDelay);
 //  mySerialPort.print("0000");
 //  delay(wDelay);
 //  mySerialPort.print("----");
 //  delay(wDelay);
 //  mySerialPort.print("8888");
 //  delay(wDelay);
//  mySerialPort.print("REDY");
//  delay(wDelay);
//  delay(wDelay);
//  mySerialPort.print("DONE");
//  delay(wDelay);
//  delay(wDelay);
//  delay(wDelay);
//  mySerialPort.print("xxxx");//Send an "x" to turn a digit off
//  delay(wDelay);
//  delay(wDelay);
