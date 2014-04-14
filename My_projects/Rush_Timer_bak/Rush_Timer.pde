
////////////////////CONFIGURATION////////////////////////////////////////
// set pin numbers:                                                   //
const int buttonPin = A4;     // the number of the pushbutton pin    //
const int ledPin =  10;      // the number of the LED pin           //
int buzzerPin = 8;           // the buzzer pin                     //
////////////////////////////////////////////////////////////////////

/////////////CHANGE TIMING//////////////////////////////////////////////////////
//arm and disarm timer and alarm timer, these must be integers               //
int buttonPressTimer = 5; // Seconds button must be pressed for arm/disarm  //
long triggerTimer = 1; // Minutes before the trigger event                 //
////////////////////////////////////////////////////////////////////////////

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

//button debounce variables
long lastDebounceTime = 0;   // the last time the output pin was toggled
long debounceDelay = 50;     // the debounce time; increase if the output flickers

long armDisarmPress = 0;     // holds the time the button was pressed
boolean armState = false;    // wether armed or disarmed
long startTriggerTime = 0;   // holds the time the countdown was started
boolean triggered = false;   // this is set and reset so actions only happen once


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin); 

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  // whatever the reading is at, it's been there for longer than the debounce delay, so take it as the actual current state:
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;
  }
  
  if (buttonState == HIGH && armDisarmPress == 0 ) { //check if it is zero so we only set it once
    armDisarmPress = millis(); //set the counter when the switch was pressed and start timing the press   
  } else if (buttonState == LOW && armDisarmPress != 0) {
    armDisarmPress = 0;  //set it back to 0 if the button is not pressed   
  }
  
  // this tests if the time now minus the time button was pressed is 
  // greater than the minutes we have to wait for the timeer
  if ( ( millis()-armDisarmPress ) > ( buttonPressTimer*1000 ) && buttonState == HIGH ) {
    armState = !armState; //reverses the armState
    armDisarmPress = 0;
  }
  
  if (armState == true && startTriggerTime == 0) { // check if it's zero so we don't keep resetting starTriggerTime
    startTriggerTime = millis();
    digitalWrite(buzzerPin, HIGH); //turn on alarm
    triggered = true;
  }
  if (armState == false && startTriggerTime != 0) {
    digitalWrite(buzzerPin, LOW); //turn off alarm
    startTriggerTime = 0;
    triggered = false;
  }
  
  if ( (millis()-startTriggerTime) > (triggerTimer*1000*60) && triggered == true){
    //trigger event, to be determined but changing the armed state below will turn the buzzer off for now
    Serial.println("~~~~~~~~~~~~~~~~~~~~~TRIGGERED~~~~~~~~~~~~~~~~~~~~~~");
    armState = !armState;
   // startTriggerTime = 0;
    triggered = false;
  }  
  
    // set the LED using the state of the button:
    digitalWrite(ledPin, buttonState);
 
    // save the reading.  Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
    
 if (armState){
   Serial.println("my armState == true");
 } else {
   Serial.println("my armState == false");
 } 
 delay(500);
 
}// end void loop()


