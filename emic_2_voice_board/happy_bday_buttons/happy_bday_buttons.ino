#include <SoftwareSerial.h>
// set pin numbers:
#define rxPin 2    // Serial input (connects to Emic 2 SOUT)
#define txPin 3    // Serial output (connects to Emic 2 SIN)
#define buttonPin 5     // the number of the pushbutton pin
#define springButtonPin 6     // the number of the pushbutton pin
#define ledPin 13      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int springButtonState = 0;         // variable for reading the pushbutton status
int springButtonArmed = 0;
int springButtonHasFired = 0;

// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
 // Serial.begin(9600);
  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH);
  pinMode(springButtonPin, INPUT); 
  digitalWrite(springButtonPin, HIGH);  
 
   // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);
 
  emicSerial.write('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  
  delay(5000);
  emicSerial.flush();      // Flush the receive buffer 
}

void loop(){
  delay(250);
  springButtonState = digitalRead(springButtonPin);
//  Serial.print(springButtonState);
//  Serial.print("\n");
//  Serial.print(springButtonHasFired);
//  Serial.print("\n");

  //if (digitalRead(springButtonPin) == HIGH && springButtonArmed == true && springButtonHasFired == false) {
  if (springButtonState == 0) {
            happy();
  }
  
 // buttonState = digitalRead(buttonPin);
  //springButtonState = digitalRead(springButtonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
    //talk();
  // happy(); 
  }
}


void happy(){
  if (springButtonHasFired == 2){
    return;   
  }
  emicSerial.write("N2\n"); // change voice command needs new line and double quotes to work
  emicSerial.write("V2\n");
  emicSerial.write("P0\n");
  emicSerial.write('S');
  emicSerial.write("Happy birthday sarah. Let me sing for you. are you ready");
  delay(1500);
  emicSerial.write("[:phoneme arpabet speak on][:rate 150][:n0][hxae<300,10>piy<300,10> brrrx<600,12>th<100>dey<600,10>tuw<600,15> yu<1200,14>_<300> hxae<300,10>piy<300,10> brrrx<600,12>th<100>dey<600,10> tuw<600,17>yu<1200,15>_<300> hxae<300,10>piy<300,10> brrrx<600,22>th<100>dey<600,19> dih<600,15>r sae<600,14>rx<100,12>rxae<350,12>aehx_<120>_<300> hxae<300,20>piy<300,20> brrrx<600,19>th<100>dey<600,15> tuw<600,17> yu<1200,15>][:n0]"); 
  while (emicSerial.read() != ':');
   springButtonHasFired++;
}
