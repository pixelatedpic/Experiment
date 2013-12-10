//by pixelatedpic

#include <SPI.h>
#include <PString.h>
#include <SD.h>
File waypoints;
char c;
char buffer[21];
int i=0;
int q=0;
//String mystring[100];
String t[50];

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  SD.begin(10);
  if (SD.exists("test.txt"))//checking if the file exists
  {
    Serial.println("file available to read");//debug
    waypoints = SD.open("test.txt",FILE_READ);
    while(waypoints.available())
    {
      
      //Serial.write(waypoints.read());
      c = waypoints.read();
      
      PString mystring(buffer, sizeof(buffer),c);
      t[i] += mystring;
      t[i].trim();
      if (mystring=="\r"){
      i++;
      
      
      }
      
     // Serial.println(i);
      //delay(1000);
      //i++;
      //Serial.println(buffer);
//      if(c=='\n'){
//      }
      
    }
    waypoints.close();
  }
    else
    {
      Serial.println("Could not open the file");
    }
  
//  else
//  {
//    Serial.println("file not exist");//debug
//  }
    

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("home: ");
  Serial.println(t[0]);
 // Serial.println();
  Serial.print("w1: ");
  Serial.println(t[1]);
  //Serial.println();
  Serial.print("w2: ");
  Serial.println(t[2]);
  //Serial.println();
  Serial.print("w3: ");
  Serial.println(t[3]);
  //Serial.println();
  Serial.print("w4: ");
  Serial.println(t[4]);
  //Serial.println();
//  if (t=";"){
//    i++;
//    
//  }
 // Serial.println(i);
 // Serial.println(t.length());
  delay(10000);

}
