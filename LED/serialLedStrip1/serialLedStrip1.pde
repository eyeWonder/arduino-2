//four pin
//blue  - vin
//red   - digital 2
//green - digital 3
//black - Ground
int SDI = 2; //Red wire (not the red 5V wire!)
int CKI = 3; //Green wire
int ledPin = 13; //On board LED

int pan1 = 1; //moving led
int pan2 = -pan1; //moving led
int panPosition = 0;

int lower=0;
int upper=31;

#define STRIP_LENGTH 32 //32 LEDs on this strip
long strip_colors[STRIP_LENGTH];

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(CKI, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //Clear out the array
  for(int x = 0 ; x < STRIP_LENGTH ; x++)
    strip_colors[x] = 0;
    
  randomSeed(analogRead(0));
  
  //Serial.begin(9600);
  //Serial.println("Hello!");
}

void loop() {
fadeUpRed();
colorChange();
cylon();
}
  
void fadeUpRed() {  
//string theValue;
 long new_color = 0;
 for (int t=0x00; t<0x50; t++) { //fade up the red
   new_color <<= 8;
   new_color |= t;
   for(int x = 0 ; x < 2 ; x++){ //fill the last two bytes
     new_color <<= 8;
     new_color |= random(0x05); //Give me a number from 0 to 0xFF
     //new_color &= 0xFFFFF0; //Force the random number to just the upper brightness levels. It sort of works.
   }
  strip_colors[15] = new_color;
  //strip_colors[16] = theValue;
  strip_colors[17] = new_color;
 // strip_colors[18] = theValue;
  strip_colors[19] = new_color;
  
  post_frame();
  delay(50);
 }
}

void colorChange() {
for (int i =0; i<32; i++) {
  strip_colors[i] = 0xFF0000;
}
  post_frame();
  delay(2000);
for (int j =0; j<32; j++) {
  strip_colors[j] = 0x00FF00;
}
  post_frame();
  delay(2000);
  
for (int k =0; k<32; k++) {
  strip_colors[k] = 0x0000FF;
}
  post_frame();
  delay(2000);
  
for (int m =0; m<32; m=m+2) {
  strip_colors[m] = 0xFFFFFF;
}
  post_frame();
  delay(2000);  
  
}

void cylon() {
for (int k =0; k<32; k++) {
  strip_colors[k] = 0x000000;
}

  strip_colors[panPosition] = 0x200000;
  panPosition = panPosition + pan1;
  
  if (panPosition == 0 || panPosition == 31) {
    pan1 = -pan1;
  }
  post_frame();
  delay(25);
 
} 

//Throws random colors down the strip array
void addRandom(void) {
  int x;
  
  //First, shuffle all the current colors down one spot on the strip
  for(x = (STRIP_LENGTH - 1) ; x > 0 ; x--)
    strip_colors[x] = strip_colors[x - 1];
    
  //Now form a new RGB color
  long new_color = 0;
  for(x = 0 ; x < 3 ; x++){
    new_color <<= 8;
    new_color |= random(0xFF); //Give me a number from 0 to 0xFF
    //new_color &= 0xFFFFF0; //Force the random number to just the upper brightness levels. It sort of works.
  }
  
  strip_colors[0] = new_color; //Add the new random color to the strip
}

//Takes the current strip color array and pushes it out
void post_frame (void) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    long this_led_color = strip_colors[LED_number]; //24 bits of color data

    for(byte color_bit = 23 ; color_bit != 255 ; color_bit--) {
      //Feed color bit 23 first (red data MSB)
      
      digitalWrite(CKI, LOW); //Only change data when clock is low
      
      long mask = 1L << color_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
      
      if(this_led_color & mask) 
        digitalWrite(SDI, HIGH);
      else
        digitalWrite(SDI, LOW);
  
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}
