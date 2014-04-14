
// set pin numbers:
const int pinA5 = A5;     // the number of the pushbutton pin
const int pinA4 = A4;
const int pinA3 = A3;
const int pinA2 = A2;
const int pinA1 = A1;
const int pinA0 = A0;
const int pinD8 = 8;
const int pinD7 = 7;


// variables will change:
int stateA5 = 1;         // variable for reading the pushbutton status
int stateA4 = 1;
int stateA3 = 1;
int stateA2 = 1;
int stateA1 = 1;
int stateA0 = 1;
int stateD8  = 1;
int stateD7  = 1;

void setup() {

  // Pins are input by default
  digitalWrite(pinA5, HIGH);       // turn on pullup resistors 
  digitalWrite(pinA4, HIGH); 
  digitalWrite(pinA3, HIGH); 
  digitalWrite(pinA2, HIGH); 
  digitalWrite(pinA1, HIGH); 
  digitalWrite(pinA0, HIGH); 
  digitalWrite(pinD8, HIGH); 
  digitalWrite(pinD7, HIGH);
  Serial.begin( 9600 );
}

void loop(){
  // read the state of the pushbutton value:
  stateA5 = digitalRead(pinA5);
  stateA4 = digitalRead(pinA4);
  stateA3 = digitalRead(pinA3);
  stateA2 = digitalRead(pinA2);
  stateA1 = digitalRead(pinA1);
  stateA0 = digitalRead(pinA0);
  stateD8 = digitalRead(pinD8);
  stateD7 = digitalRead(pinD7);

  
  Serial.print("A5 is ");Serial.print(stateA5);Serial.print(" ");
  Serial.print("A4 is ");Serial.print(stateA4);Serial.print(" ");
  Serial.print("A3 is ");Serial.print(stateA3);Serial.print(" ");
  Serial.print("A2 is ");Serial.print(stateA2);Serial.print(" ");
 
  Serial.print("A1 is ");Serial.print(stateA1);Serial.print(" ");
  Serial.print("A0 is ");Serial.print(stateA0);Serial.print(" ");
  Serial.print("D8 is ");Serial.print(stateD8);Serial.print(" ");
  Serial.print("D7 is ");Serial.print(stateD7);Serial.println(" ");
  delay(550);
}
