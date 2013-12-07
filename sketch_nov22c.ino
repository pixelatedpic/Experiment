#include <Servo.h>


/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file  
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
     
 */
 
#include <SD.h>
#define SERVOpin 9


File myFile;
char chkLine;
int listWP;
unsigned int MaxWP; 
unsigned int CurrentWP;
Servo Rudder;
char buf[100];
char test;
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Rudder.attach(SERVOpin);
  Rudder.write(90);
  pinMode(SERVOpin, OUTPUT);

  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    return;
  }
  
  MaxWP = ListWP();
  Serial.println(MaxWP);
  //test = WP();
  WP();
  //Serial.println(test);
  CurrentWP = 1;  
  Vink();
  
  //Serial.println(test);
}

void loop()
{
    // nothing happens after setup
}
