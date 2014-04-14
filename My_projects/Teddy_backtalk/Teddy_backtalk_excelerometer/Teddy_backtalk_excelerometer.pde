#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"
//
//*********************************************************************************************************************
//Pins 13, 12, 11 are always used by the SD card (they are the only pins that have a high speed SPI interface).
//Then there are 5 other pins used to talk to the DAC and SD card, but they can be set to connect to any arduino pin. 
//However, by default, the library is configured to use pins 10 (for SD card) and pins 2, 3, 4 and 5 for the DAC. 
//To chanage these pins requires modifying the library - the pins are referenced by their 'hardware' pin names 
//(ie PORTD, etc) not by arduino pins.
//
//That means pins 6, 7, 8, 9 and the 6 analog in pins (also known as digital i/o pins 14-20) are available
//
//Project specific
//analog pins 0 - 5 are for buttons
//pins 7 and 8 are used for the chest buttons and could be combined into one pin if needed
//pin 6 and 9 are the accelerometer
//*********************************************************************************************************************

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

#define DEBOUNCE 5  // button debouncer

const int xPin = 6;		// X output of the accelerometer
const int yPin = 9;		// Y output of the accelerometer

// here is where we define the buttons that we'll use. button "0" is the first, button "7" is the 6th, etc
byte buttons[] = { 18, 19, 16, 17, 14, 15, 8, 7};

// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'pressed' (the current state
volatile byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

void setup() {
  byte i;
  
  //set up exccelerometer pins
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  
  // set up serial port
  Serial.begin(9600);
  putstring_nl("WaveHC with ");
  Serial.print(NUMBUTTONS, DEC);
  putstring_nl("buttons");
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(freeRam());      // if this is under 150 bytes it may spell trouble!
  
  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
 
  // pin13 LED
  pinMode(13, OUTPUT);
 
  // Make input & enable pull-up resistors on switch pins
  for (i=0; i< NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
  
  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Ready!");
  
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1<<TOIE2;


}

SIGNAL(TIMER2_OVF_vect) {
  check_switches();
}

void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  byte index;

  for (index = 0; index < NUMBUTTONS; index++) {
    currentstate[index] = digitalRead(buttons[index]);   // read the button
    
    /*     
    Serial.print(index, DEC);
    Serial.print(": cstate=");
    Serial.print(currentstate[index], DEC);
    Serial.print(", pstate=");
    Serial.print(previousstate[index], DEC);
    Serial.print(", press=");
    */
    
    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
          // just pressed
          justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
          // just released
          justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    //Serial.println(pressed[index], DEC);
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}


void loop() {
 // byte i;
  accelerometer();

  if (justpressed[0]) {
    justpressed[0] = 0;
    Serial.println("zero");
    playfile("R_ear.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[1]) {
    justpressed[1] = 0;
    playfile("L_ear.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[2]) {
    justpressed[2] = 0;
    playfile("R_hand.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[3]) {
    justpressed[3] = 0;
    playfile("L_hand.WAV");
    while (wave.isplaying)  {}
    wave.stop();    
  }
  if (justpressed[4]) {
    justpressed[4] = 0;
    playfile("R_foot.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[5]) {
    justpressed[5] = 0;
    playfile("L_foot.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[6]) {
    justpressed[6] = 0;
    playfile("triangle.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
  if (justpressed[7]) {
    justpressed[7] = 0;
    playfile("heart.WAV");
    while (wave.isplaying) {}
    wave.stop();    
  }
}


void accelerometer() {
  int pulseX, pulseY;                // variables to read the pulse widths
  int accelerationX, accelerationY;  // variables to contain the resulting accelerations
  
  pulseX = pulseIn(xPin,HIGH);      // read pulse from x- and y-axes:
  pulseY = pulseIn(yPin,HIGH);
  
  accelerationX = ((pulseX / 10) - 500) * 8; // check memsic example for details
  accelerationY = ((pulseY / 10) - 500) * 8;

  Serial.print(accelerationX);      // print the acceleration
  Serial.print("\t");              // print a tab character:
  Serial.print(accelerationY);
  Serial.println();

  delay(100);
}
  

// Plays a full file from beginning to end with no pause.
void playcomplete(char *name) {
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}

