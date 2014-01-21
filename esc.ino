#include <Servo.h> 
 
Servo myservo;  
 
int val;                                   //Value for motor speed.
int analogPin = 3;                         //Potentiometer on pin 3
int servoPin = 9;                          //Servo on pin 9
int armValue=700;                           // "zero" position for arming ESC. As some wont arm with a '0' value fromthe arduino. 

void arm(){                                //Arming sequence of sending a minimum or 'joystick zero' for 2 seconds to simulate radio gear is ON and operational.  
  myservo.write(armValue); 
  delay(2500); 
}
  
void setup() { 
  
  Serial.begin(9600);
  myservo.attach(servoPin);  
  arm();
} 
 
void loop(){ 
  int val = analogRead(analogPin);         //Make a analogue reading. This is from 0-1023
  val = map(val, 0, 1023, armValue, 180);  //Scale input to use it with the servo ie from the arming value to 180.
  myservo.write(22);                      //Send servo position - Motor speed to ESC.
  Serial.println(val);                     //Send servo 
  delay(100);                              //pause for 1/10 second.
} 
