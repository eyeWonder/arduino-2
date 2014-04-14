/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 Modified 4 Sep 2010
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = 0;    // select the input pin for the potentiometer
int ledPin = 11;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  delay(5000);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
  outputValue = map(sensorValue, 0, 1023, 0, 50);  
  
  if (outputValue > 0) {  
    Keyboard.print(":"); 
    if (outputValue < 10) {
      Keyboard.print("0");
    }
    Keyboard.print(outputValue);
    Keyboard.print("99sp;");
  } 

//  Serial.print(":00"); 
//  if (outputValue < 10) {
//    Serial.print("0");
//  }
//  Serial.print(outputValue);
//  Serial.println("sp;"); 
  
  delay(100);

//  sensorValue = analogRead(0);
//  .print("analog 0 is: ");
//  Serial.println(outputValue);
//  delay(250);
//  
//  // turn the ledPin on
//  digitalWrite(ledPin, HIGH);  
//  // stop the program for <sensorValue> milliseconds:
//  delay(sensorValue);          
//  // turn the ledPin off:        
//  digitalWrite(ledPin, LOW);   
//  // stop the program for for <sensorValue> milliseconds:
//  delay(sensorValue);                  
}
