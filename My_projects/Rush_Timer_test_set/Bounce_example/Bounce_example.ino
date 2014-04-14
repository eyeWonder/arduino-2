// This code turns a led on/off through a debounced switch

#include <Bounce.h>

// This code turns a led on/off through a debounced button
// Build the circuit indicated here: http://arduino.cc/en/Tutorial/Button

#define BUTTON 9
#define LED 5

// Instantiate a Bounce object with a 5 millisecond debounce time
Bounce bouncer = Bounce( BUTTON,5 ); 

void setup() {
  pinMode(BUTTON,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
}

void loop() {
 // Update the debouncer
  bouncer.update ( );

 // Get the update value
 int value = bouncer.read();

 // Turn on or off the LED
 if ( value == HIGH) {
   digitalWrite(LED, HIGH );
 } else {
    digitalWrite(LED, LOW );
 }

}
