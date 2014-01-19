
int atime=1;
void setup(){
 
  for (atime=0;atime<500;atime+=1)
  {
  analogWrite(9,125);
  delayMicroseconds(1100);
  analogWrite(9,0);
  delay(20-(1000/1000));
  }
  
  
}


void loop(){
  

  
 // for (atime=0;atime<500;atime+=1)
 // {
//  analogWrite(9,125);
//  delayMicroseconds(1100);
//  analogWrite(9,0);
//  delay(20-(atime/1000));
 // }
  //delayMicroseconds(1900);
//  analogWrite(9,0);
//  delayMicroseconds(1900)

int pulse=1250;
//
//       
//     // Serial.print("Motor status: ");
//     // Serial.println(motorrun);
  analogWrite(9,255);
  delayMicroseconds(1200);
  //delay(100);
  analogWrite(9,0);
  delay(20-(1200/1000));  
}
