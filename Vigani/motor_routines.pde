void arm()
{ //Arming
  ESC.write(armValue);
  delay(2500);
}

int set_motor(boolean motorrun)//this part works
{
  //int pulse=1250;
  if (motorrun) {

    ESC.write(ESCval);//1200/1180/1170/1165/                      //Send servo position - Motor speed to ESC.
    //Serial.println("motor runing");                     //Send servo
    delay(200);                              //pause for 1/10 second.
    //return();
  }
}
