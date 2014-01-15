
//

int pin = 7;
unsigned long pulse;
boolean detect_remote = false;

void setup()
{
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(13, OUTPUT);
}


void rem_detect()
{
  pulse = pulseIn(pin, HIGH, 25000);
  if(pulse>0)
  {
    detect_remote = true;
  }
  else
  {  
    detect_remote = false;     
  }  
}

void loop()
{
  rem_detect();
  if (detect_remote)
  {
    Serial.println("Remote Activated");
    digitalWrite(13,HIGH);
  }
  else
  {
    Serial.println("Micro-controller Mode");
    digitalWrite(13,LOW);
  }
  
  
  //pulse = pulseIn(pin, HIGH, 25000);
 // if
  //Serial.println(duration);
  //if(duration>1000 && duration < 1900){
 //   if(duration>0){
  //Serial.println(duration);
//  Serial.println("ON");
//  }
//  else
//  {
//    Serial.println("OFF");  
//  }
  delay(200);
}
