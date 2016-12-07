//CODER: MOHAMED AFZAL
//7th Dec 2016 (EIT PVT LTD)

#include <SoftwareSerial.h>
SoftwareSerial GSMmodem(2,3);
char currentLine[142] = "";
int currentLineIndex = 0;
bool nextLineIsMessage = false;
bool ledStatus;
String smsNumber;
String lastline;

boolean SerialReadUntil(SoftwareSerial* serial, String key, int timeout)
{

  unsigned long start = millis();

  int pos = 0;

  while(start + timeout > millis()) {
    while (start + timeout > millis() && serial->available()) {
      char a = serial->read();
      // Serial.print(a);
      if (a == key[pos]) {
        pos++;
      } 
      else {
        pos = 0;
      }
      if (pos == key.length()) {
        return true;
      }
    }
  }
  return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  GSMmodem.begin(9600);
  pinMode(13,OUTPUT);

  GSMmodem.println("AT+CMGF=1");
  if (SerialReadUntil(&GSMmodem, "OK", 1000)) {
        Serial.println("Mode OK");
      } 
      else {
        Serial.println("Mode FAIL");
      }
  delay(500);
  GSMmodem.println("AT+CNMI=1,2,0,0,0");
  if (SerialReadUntil(&GSMmodem, "OK", 1000)) {
        Serial.println("SMS Read OK");
      } 
      else {
        Serial.println("SMS Read FAIL");
      }
  GSMmodem.flush();
  Serial.flush();
  delay(2000);
  Serial.println("call me now");

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, ledStatus);

  if(GSMmodem.available()){
    //Serial.println("sms cumin");
    char lastcharRead = GSMmodem.read();
    //Serial.print(lastcharRead);//---ok
    if(lastcharRead == '\r' || lastcharRead == '\n'){
      lastline = String(currentLine);
      //Serial.println(currentLine);
      // && lastline.substring(7,18)=="+9607906608"
      if(lastline.startsWith("+CLIP:")){
        //Serial.println(lastline.substring(8,15));
        Serial.println(lastline);
        //delay(200);
        doAnything();
        
//        nextLineIsMessage = true;
        
      } //else if(lastline.length()>0){
//        if(nextLineIsMessage){
//          //Serial.println(lastline);
//
//          if(lastline.indexOf("ON")>=0){
//            ledStatus=1;
//          }else if(lastline.indexOf("OFF")>=0){
//            ledStatus=0;
//          }
//          nextLineIsMessage = false;
//        }
//      }
      for(int i=0; i < sizeof(currentLine); i++){
        currentLine[i]=(char)0;
      }
      currentLineIndex =0;
    }else {
      currentLine[currentLineIndex++] = lastcharRead;
    }
  }

}
