#define X_PIN     0             // X Axis input (analog pin #)
#define Y_PIN     1             // Y Axis input (analog pin #)
#define Z_PIN     2             // Z Axis input (analog pin #)
#define SENS_PIN 3                      // accelerometer sensitivity (analog pin #)
#define PMW_PIN 9                      // output for PWM or LED for now

int sens = 10;
int x,y,z;

void setup(){
 Serial.begin(9600);

// sleep pin wired to 3.3v through 10k reistor

 pinMode(X_PIN, INPUT);                       // 160 - 200 / 300 - 350 / 485 - 510
 pinMode(Y_PIN, INPUT);                       // 160 - 200 / 300 - 350 / 500 - 530
 pinMode(Z_PIN, INPUT);                       // 160 - 200 / 465 - 510
 pinMode(SENS_PIN, INPUT);                  // potentiomenter

 Serial.println("Test started!");
 
}


void loop()
 x = analogRead(X_PIN);
 y = analogRead(Y_PIN);
 z = analogRead(Z_PIN);

 checkLimits();

 // Serial.print(millis()) ;
 Serial.print(", x=");
 Serial.print(x) ;
 Serial.print(", y=");
 Serial.print(y) ;
 Serial.print(", z=");
 Serial.println(z) ;
 delay(500);
}




int checkLimits()
{
 if ( x < (300 - sens) || x > (350 + sens) )
 {
   Serial.println('x is over the limit') ;
 }

}

