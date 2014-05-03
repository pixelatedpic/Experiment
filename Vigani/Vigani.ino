#include <SD.h>
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <TinyGPS++.h>
#include "globals.h"
#include "pin_definition.h"

#define DEBUG //comment this to disable printing the debug information :)
//#define DEBUG1 //comment this to disable printing the debug information :)
//#define DummyFIX

TinyGPSPlus gps;
HMC5883L compass;
Servo ESC;
Servo rudder;

TinyGPSCustom ellipsoidalHeight(gps, "GPGGA", 11);
TinyGPSCustom h_dop(gps, "GPGGA", 8);
TinyGPSCustom northing(gps, "GPGGA", 3);
TinyGPSCustom easting(gps, "GPGGA", 5);
TinyGPSCustom fix(gps, "GPGGA", 6);




