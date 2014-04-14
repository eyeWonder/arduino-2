// Miguel Sanchez 2008
// try it at your own risk
//
//
// OOPS!! I've made a mistake in the previous version: 
//
// THIS IS THE CORRECT SCHEMATIC  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//  
//   +5                       +5
//   /         arduino         /
//   \<------+ 2       1 +---->\  10 K potentiometer
//   /         analog          /
//   \         inputs          \
//   GND                      GND
//
//  arduino     ULN2003
//           +-----------+
//           |           | 
//  9 -------+ 2      15 +-R---LED--+
//           |           |     RED  |
//           |           |          |
//  10-------+ 3      14 +-R--LED---+
//           |           |   GREEN  |
//           |           |          |  
//  11-------+ 4      13 +-R--LED---+
//           |      8    |    BLUE  |
//           +------+----+          |
//                  |               |
//                GND             +12V
//R=22 OHM/1W (for 3W RGB LEDs)


int r=0;                           
int g=0;                           
int b=0;

void rgb(int r, int g, int b) {
  analogWrite(9,r);
  analogWrite(11,g);
  analogWrite(10,b);
 }


void brgb(int r, int g, int b, int time) {
  int i;
  for(i=0;i<10;i++) {
  analogWrite(9,r);
  analogWrite(11,g);
  analogWrite(10,b);
  delay(time/20);
  analogWrite(9,0); analogWrite(10,0); analogWrite(11,0);
  delay(time/20);
  }
}

void setup() 
{ 
  Serial.begin(9600); // only for debug purposes
} 

int button() {
  return (1+analogRead(2)/4); // no longer useful
}
 
int bright() {
  return (analogRead(1)/4);
}
 
void slow_random_switch(int max) {
 while(true) {
 rgb(random(max),random(max),random(max));
 delay(3000);
 }
}

void slow_random_fading(int max) // slow random fading 
{ 
  int color,i,value,time=100; 
  while(true) {
  color=random(1,4); 
  value=random(0,max);
  switch(color) {
  case 1: 
    if(r>value) for(i=r;i>value;i--) {
      rgb(i,g,b); 
      delay(time); 
    }
    else for(i=r;i<value;i++) {
      rgb(i,g,b); 
      delay(time); 
    }
    r=value;
    break;
  case 2: 
    if(g>value) for(i=g;i>value;i--) {
      rgb(r,i,b); 
      delay(time); 
    }
    else for(i=g;i<value;i++) {
      rgb(r,i,b); 
      delay(time); 
    }
    g=value;
    break;
  case 3: 
    if(b>value) for(i=b;i>value;i--) {
      rgb(r,g,i); 
      delay(time); 
    }
    else for(i=b;i<value;i++) {
      rgb(r,g,i); 
      delay(time); 
    }
    b=value;
    break;
  } 
  delay(3000);
  Serial.print(r); 
  Serial.print(" "); 
  Serial.print(g); 
  Serial.print (" "); 
  Serial.println(b);
 }
} 

void candle(int max) {
  int value;
  while(true) {
    value=random(max/4,max);
    rgb(value,value*5/10-random(max/10),0);
    delay(30+random(40));
  }  
}

void rainbow(int max) {
  while(true) {
    rgb(max,0,0); delay(3000); // red
    rgb(0,max,0); delay(3000); // green
    rgb(0,0,max); delay(3000); // blue
    rgb(max,max,0); delay(3000); // yellow
    rgb(max/2,0,max/2); delay(3000); // purple
    rgb(max,0,max); delay(3000); // fuschia
    rgb(0,0,max/2); delay(3000); // navy
    rgb(0,max/2,max/2); delay(3000); // teal
    rgb(0,max,max); delay(3000); // aqua
    rgb(max/2,max/2,0); delay(3000); // olive
    rgb(0,max/2,0); delay(3000); // lime
    rgb(max/2,max/2,max/2); delay(3000); // grey
    rgb(max,max,max); delay(3000); // white    
  }
}

void rainbow2() {
 while(true) {
   
	for(int i = 0; i < 256; i++) {rgb(255,i,0); delay(100);  }
        for(int i = 0; i < 256; i++) {rgb(255-i,255,0); delay(100);  }	
        for(int i = 0; i < 256; i++) {rgb(0,255,i); delay(100);  }
        for(int i = 0; i < 256; i++) {rgb(0,255-i,255); delay(100);  }
        for(int i = 0; i < 256; i++) {rgb(i,0,255); delay(100);  }
        for(int i = 0; i < 256; i++) {rgb(255,0,255-i); delay(100);  }
 } 
}
void loop() {

int b;  
b=bright(); Serial.print(b);
switch(button()/50) {  
case 0: 
 Serial.println("FADING");
 brgb(100,0,0,3000);  
 slow_random_fading(b); break;
case 1:
 Serial.println("SWITCH");
 brgb(0,100,0,3000); 
 slow_random_switch(b); break;
case 2: 
Serial.println("RAINBOW");
 brgb(100,100,0,3000);
 rainbow(b); break;
case 3: 
Serial.println("CANDLE");
// brgb(150,100,100,3000);
 candle(b); break;
default:
Serial.println("RAINBOW2"); 
 brgb(0,100,100,3000);
 rainbow2(); break;
} 
}//  arduino  ULN2003
//   +5      +-----------+     +5
//   /       |           |     /
//   \<------+ 2       1 +---->\  10 K potentiometer
//   /       |           |     /
//   \       |           |     \
//   GND     |           |    GND
//           |           |
//  9 -------+ 2      15 +-R---LED--+
//           |           |     RED  |
//           |           |          |
//  10-------+ 3      14 +-R--LED---+
//           |           |   GREEN  |
//           |           |          |  
//  11-------+ 4      13 +-R--LED---+
//           |      8    |    BLUE  |
//           +------+----+          |
//                  |               |
//                GND             +12V

//R=22 OHM/1W (for 3W RGB LEDs)

