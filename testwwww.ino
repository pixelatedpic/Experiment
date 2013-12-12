#include <SPI.h>

#include <PString.h>
#include <SD.h>
File waypoints;
char c;
char buffer[21];
int i=1;
int q=1;
unsigned int MaxWP; 
//String mystring[100];
String t[1];
int Line, R_Line;
String j[21];
String HOME;
String homy;
boolean hom = false;
int tt(){
   if (SD.exists("test.txt"))//checking if the file exists
  {
    Serial.println("file available to read");//debug
    waypoints = SD.open("test.txt",FILE_READ);
    while(waypoints.available())
    {
      
      //Serial.write(waypoints.read());
      c = waypoints.read();
      
      //PString mystring(buffer, sizeof(buffer),c);
      //t[i] += mystring;
      //t[i].trim();
       
      if (c=='\r'){
      i++;
      //q++;
      
      }
      
    
      //delay(1000);
      //i++;
      //Serial.println(buffer);
//      if(c=='\n'){
//      }
      
    }
    waypoints.close();
    return i;
  }
    else
    {
      Serial.println("Could not open the file");
    } 
  
}

String tr(){
   if (SD.exists("test.txt"))//checking if the file exists
  {
    Serial.println("file available to read");//debug
    waypoints = SD.open("test.txt",FILE_READ);
    R_Line = 1;
    while(waypoints.available())
    {
      
      //Serial.write(waypoints.read());
        
        c = waypoints.read();
        //PString mystring(buffer, sizeof(buffer),c);
        if (c=='h')
        {
          hom = true;
          Serial.println("matched");
          while(hom == true)
          {
          c = waypoints.read();
          PString mystring(buffer, sizeof(buffer),c);
          HOME += mystring;
          HOME.trim();
          if(mystring=="\r") break;
          }   
        }//else{ hom = false; }
        
     // Serial.print(c);
//      if (Line == R_Line)
//        {
//        Serial.print("matched");
//        //c = waypoints.read();
//        
//        PString mystring(buffer, sizeof(buffer),c);
//        t[0] += mystring;
//        t[0].trim();
//        if(mystring=="\r") break; 
//        }
       // Serial.println(t[0]);
      //PString mystring(buffer, sizeof(buffer),c);
      //t[i] += mystring;
      //t[i].trim();
       
     // if (c=='\r'){
      //i++;
      //q++;
      
      }
      
    
      //delay(1000);
      //i++;
      //Serial.println(HOME);
//      if(c=='\n'){
//      }
      
    }
    waypoints.close();
    
    return HOME;
  }
   // else
  //  {
   //   Serial.println("Could not open the file");
   // } 
  
//}

void setup() {
  // put your setup code here, to run once:
  
  hom =true;
  Serial.begin(9600);
  SD.begin(10);
  //MaxWP=tt();
  Serial.print("Number of waypoints: ");
  Serial.println(MaxWP);
  tr();
 // Serial.print("Home Waypoint: ");
 // Serial.println(HOME);
  
  
 
//  if (SD.exists("test.txt"))//checking if the file exists
//  {
//    Serial.println("file available to read");//debug
//    waypoints = SD.open("test.txt",FILE_READ);
//    while(waypoints.available())
//    {
//      
//      //Serial.write(waypoints.read());
//      c = waypoints.read();
//      
//      PString mystring(buffer, sizeof(buffer),c);
//      t[i] += mystring;
//      t[i].trim();
//      if (mystring=="\r"){
//      i++;
//      
//      
//      }
//      
//     // Serial.println(i);
//      //delay(1000);
//      //i++;
//      //Serial.println(buffer);
////      if(c=='\n'){
////      }
//      
//    }
//    waypoints.close();
//  }
//    else
//    {
//      Serial.println("Could not open the file");
//    }
  
//  else
//  {
//    Serial.println("file not exist");//debug
//  }
    

}

void loop() {
 // Serial.println(HOME);
  // put your main code here, to run repeatedly:
  //Serial.println(t[0].length());
//  if (t[0].startsWith("h")){
//    
// //   Serial.println("tetet");
//    Serial.println(t[0]);
//  }
  //Serial.println(t[]);
  Serial.println(HOME.substring(1,19));
  /*
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
  Serial.println(t[4]);*/
  //Serial.println();
//  if (t=";"){
//    i++;
//    
//  }
 // Serial.println(i);
 // Serial.println(t.length());
  delay(10000);

}
