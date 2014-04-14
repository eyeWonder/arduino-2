 
void setup() 
{ 


analogWrite(6, 60);
analogWrite(5, 60);

delay(5000);

// analogWrite(5, 255);
// delay(1000);
// analogWrite(5, 120);
// delay(2000);
// analogWrite(5, 50);
// delay(2000);
analogWrite(5, 0);

analogWrite(6 , 0);

} 
 
 
void loop() 
{ 
//  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
} 
