#include <SPI.h>

#include <PString.h>
#include <SD.h>
File waypoints;
char c;
char buffer[21];
int i=1;
int q=1;
//String MaxWP; 
//String mystring[100];
String lat_lon;
//int Line, R_Line;
//String j[21];
//String HOME;
//String homy;
boolean hom = false;
int rr = 99;
int ff=0;
String tt(){
   if (SD.exists("test.txt"))//checking if the file exists
  {
    Serial.println("file available to read");//debug
    waypoints = SD.open("test.txt",FILE_READ);
    while(waypoints.available())
    {
      while ( waypoints.read() != '\n' );
      
      Serial.println(i);
      if (i==rr)
      {
         //Serial.println("Matched");// debug
         for (q=0; q<=21;q++)
         {
         c = waypoints.read();
         //Serial.println(c);
         PString mystring(buffer, sizeof(buffer),c);
         lat_lon += mystring;
         lat_lon.trim();
         //Serial.println(t[0]);
         if(mystring==";") return lat_lon;
         }
        //Serial.println(t[0]);
         break;
      }
      i++;
      
    }
    waypoints.close();
   //return i;
  }
    else
    {
      Serial.println("Could not open the file");
    } 
  
}

void setup() {
  // put your setup code here, to run once:
  
  hom =true;
  Serial.begin(9600);
  SD.begin(10);
  //MaxWP=tt();
  tt();
  
  //Serial.print("Number of waypoints: ");
  Serial.println(lat_lon);


}

void loop() {

}
