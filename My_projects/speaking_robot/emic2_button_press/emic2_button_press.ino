#include <SoftwareSerial.h>
// set pin numbers:
#define rxPin 2    // Serial input (connects to Emic 2 SOUT)
#define txPin 3    // Serial output (connects to Emic 2 SIN)
#define buttonPin 5     // the number of the pushbutton pin
#define ledPin 13      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH); 
 
   // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);
 
  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay

  emicSerial.flush();      // Flush the receive buffer 
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, LOW);  
    
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
    talk(); 
  }
}

void talk1() {
    // Speak some text
    emicSerial.print("N2\n"); // change voice command needs new line and double quotes to work
  emicSerial.print('S');
  emicSerial.print("Hello. 1; 34.. you know what time it is mike. it's time to be __awesome.. ##love ##you.");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);  
  
}

void talk3() {
    // Speak some text
    emicSerial.print("N2\n"); // change voice command needs new line and double quotes to work
  emicSerial.print('S');
  //emicSerial.print("[:phone arpa speak on][:rate 300][:n0][dah<300,10>blx<300,10>yu<300,10>_<300>nay<310,10>n_<300>giy<310,10>][:n0]");  // Send the desired string to convert to speech
  //emicSerial.print("My Emic has a :-)0 voice :-)1 voice :-)2 voice :-)3 voice:-)4 voice :-)5 voice:-)6 voice :-)7 voice:-)8 voice."); 
  //emicSerial.print(":-)0 Hello everyone. My name is Emic 2. I am the next generation text-to-speech module created by Grand Idea Studio. I can ##whisper ##very ##quietly. I can change to 1 of 9 voices. For example, from Paul :-)1 to Harry :-)4 to Dennis :-)8 to Wendy. :-)0 I can also 0x28 increase my pitch.  And increase my pitch again. >>>> Then speak faster >>>> and even faster >>>> and even faster again. <<<<<<<<<<<< And then go back to normal.");
 emicSerial.print("[aw<100,22>rr fllae<400,23>g wah<400,15> stih<400,17>ll dheh<600,18>r _<300> ow<400> sey<400,23> dah<400>z dhae<200,23>ae<200,22>t stah<400,20>r spae<400>ngel<400>d bae<400,25>nrr<200,28>rr<200,27> yxeh<200,25>eh<200,23>t wey<800,23>ey<150,25>ey<150,23>ey<1200,22>v _<900> fow<300,18>rdhah<300> llae<900,23>ae<400,25>nd ah<300,27>v dhah<300,28> friy<1000,30>iy<1000,35> _<900> ae<300,23>nd dhah<300,25> hxow<1000,27>m _<600> ah<300,28>v dhah<1000,25> brrey<1500,23>v _<900>]");
  //  emicSerial.print(":All your base are belong to us.:");

  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);  
}


void talk() {
    // Speak some text
    emicSerial.print("N2\n"); // change voice command needs new line and double quotes to work
    emicSerial.print("V-10\n");
  emicSerial.print('S');
  //pitch up    \\x2F\\x5C\\x2F\\x5C
  //pitch down  \\x5C\\x2F\\x5C\\x2F
  emicSerial.print("you know what time it is __mike. it's time to be awesome \n");  // Send the desired string to convert to speech
   //while (emicSerial.read() != ':');
   emicSerial.print("V18\n"); 
   emicSerial.print('S');
   emicSerial.print("Volume changed can you tell");
  emicSerial.print('\n');

  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command

  
}
