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

//for ping
const int pingPin = 11;
long duration, cm;

#define STRIP_LENGTH 32 //32 LEDs on this strip
long strip_colors[STRIP_LENGTH];

void setup() {
  Serial.begin(9600);
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
pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  

  panPosition = map(cm, 12, 110, 0, 31);
  if (panPosition>31){
    cm = 15;
  }
  changePosition(panPosition);
//stopLed();
//colorChange();
//cylon();
}


int changePosition(int panPosition) {
for (int k =0; k<32; k++) {
  strip_colors[k] = 0x000000;
}
  strip_colors[panPosition] = 0x200000;
  post_frame();
  delay(25); 
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

void stopLed(){while(1){}}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
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
