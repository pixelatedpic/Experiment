#include <Servo.h>
//#include <PWMServo.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


SoftwareSerial ss(2, 3); // RX, TX
TinyGPSPlus gps;
Servo ESC;  
HMC5883L compass;
Servo rudder;

int val;                                   //Value for motor speed.
int analogPin = 3;                         //Potentiometer on pin 3
int ESCpin = 6;                          //Servo on pin 9
int armValue=700;                           // "zero" position for arming ESC. As some wont arm with a '0' value fromthe arduino. 





int pos = 90;
unsigned long time;
boolean tt = true;
int arm_time=1;
int pulse=1000;
//int enablePin = 6;
int in1Pin = 4;
int in2Pin = 7;
boolean motorrun=false;
//int potPin = 0;
int speed;
boolean reverse=false;
String fixed;
//File waypoints;
char c=0;
char byteRead;
int tot_wps_infile;
int blah=1;
int blah2=1;
double lat_gps;
double lon_gps;
String fix_gps;
int waycount = 4;
int waypoint = 0;
boolean homei = false;
//String logfilename="20131217-01.csv";
TinyGPSCustom ellipsoidalHeight(gps, "GPGGA", 11);
TinyGPSCustom h_dop(gps, "GPGGA", 8);
TinyGPSCustom northing(gps, "GPGGA", 3);
TinyGPSCustom easting(gps, "GPGGA", 5);
TinyGPSCustom fix(gps, "GPGGA", 6);


double wlat, wlon;

void arm(){                                //Arming sequence of sending a minimum or 'joystick zero' for 2 seconds to simulate radio gear is ON and operational.  
  ESC.write(armValue); 
  delay(2500); 
}
/*
Function descr here...
Uses TinyGPS++ lib.
*/
bool feedGPS() {
  while (ss.available()) {
    if (gps.encode(ss.read())) {
      return true;    
    }
  }
  return false;
}

/*
Function descr here...
timestamp, lat, lon, z
Uses TinyGPS++ lib.
*/
void getcurGPS() {
  
  feedGPS();
  fix_gps = fix.value();
  //Serial.println(fix_gps);
  if (fix_gps=="1")
 {
   
    feedGPS();
    if (gps.location.isUpdated()) {
      lat_gps = gps.location.lat();
      lon_gps = gps.location.lng();

    } 
}
}

double calc_course(const double wlat, const double wlon) {
    //const double DEST_LAT = 4.2029716;
    //const double DEST_LON = 73.231562;
    double coursetodest =
      gps.courseTo(
        lat_gps,
        lon_gps,
        wlat,
        wlon);
    //Serial.println();
    //Serial.print(coursetodest);
    //Serial.print(gps.cardinal(coursetodest));
    return coursetodest;   
}

double calc_distKm(const double wlat, const double wlon) {
    //const double DEST_LAT = 4.2029716;
    //const double DEST_LON = 73.231562;
    double disttodest =
      gps.distanceBetween(
        lat_gps,
        lon_gps,
        wlat,
        wlon) ;/// 1000.0;
    //Serial.println();
    //Serial.print(disttodest);
    //disttodest=0.5;
    if (disttodest < 1)//9 meter radius
    {
      if(waycount==waypoint){
        homei = true;
        motorrun = false;
        Serial.println("END OF TRIP");
      }
      waypoint+=1;
    }    
    return disttodest;
}



void setupHMC5883L(){
  //Setup the HMC5883L, and check for errors
  int error;
  error = compass.SetScale(1.3); //Set the scale of the compass.
  if(error != 0) ;//Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0);// Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
}

float getHeading(){
  //Get the reading from the HMC5883L and calculate the heading
  MagnetometerScaled scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float declinationAngle = -0.05235;
  float heading = atan2(scaled.YAxis, scaled.XAxis)+declinationAngle;
  
  // If you have an EAST declination, use += declinationAngle, if you have a WEST declination, use -= declinationAngle
  //heading -= declinationAngle;
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2 * PI;
  // Check for wrap due to addition of declination.
  if(heading > 2 * PI)
    heading -= 2 * PI;
  //-0.0523598776
  return (int) (heading * 180 / M_PI); //radians to degrees
}

int setMotor(boolean motorrun)//this part works
{
 
//int pulse=1250;
  if(motorrun){
       
  ESC.write(1000);                      //Send servo position - Motor speed to ESC.
  Serial.println("motor runing");                     //Send servo 
  delay(200);                              //pause for 1/10 second.
  //return();
  }
}


void setup() {
  // put your setup code here, to run once:
  //hom =true;
  Serial.begin(115200);
  //ss.begin(9600);
  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L
   
  
  Serial.println("Align rudder");
  rudder.attach(9);
  rudder.write(90);
  delay(10);
  Serial.println("Rudder done");
 
  

 
  //rudder.detach();
  
  waypoint=1;
  motorrun=true;
  
  Serial.println("Start motor ARMING");
  ESC.attach(ESCpin);
  arm();
  Serial.println("Motor Armed");
  //delay(10000);
}
 


void loop() {
  
//  ESC.write(800);                      //Send servo position - Motor speed to ESC.
//  Serial.println("motor runing");                     //Send servo 
//  delay(100);
 // motor(tt);
 //time = millis();
 //Serial.println(time);
 // pulse=1290;
  //Serial.println("loop debug 1");
  bool newdata = false;
  unsigned long start = millis();
  
  while (millis() - start < 1000) {
    if (feedGPS()) {
      newdata = true;
    }
  }
  feedGPS();
  fixed = fix.value();
  //Serial.println("loop debug 2");
  //Serial.println(fixed);
  //&& fixed >="1"
 // motor(tt);
  if (homei==false){
  //Serial.println("fixed");
  Serial.print("current waypoint: ");
  Serial.println(waypoint);  

  
  if (newdata) {
    getcurGPS();
    Serial.print("GPS LAT: ");
    Serial.println(lat_gps,6);
    Serial.print("GPS LON: ");
    Serial.println(lon_gps,6);    
  }
  
  if (waypoint==1)
  {	
    wlat = 4.207753;//waypoint one
    wlon = 73.543100;
    //return;
  }
  if (waypoint==2)
  {
    wlat = 4.207705;//waypoint two
    wlon = 73.543248;
    //return;
  }
  if (waypoint==3)
  {
    wlat = 4.207630;//waypoint three
    wlon = 73.543218;
    //return;
  }
  if (waypoint==4)
  {
    wlat = 4.207772;//waypoint four
    wlon = 73.542977;
    //return;
  }
   
   //comment above for debug. below part ok
  double dit2way = calc_distKm(wlat, wlon);
  Serial.print("Distance to waypoint: ");
  Serial.println(dit2way);
  //calc_course(wlat, wlon);
  double cou2way = calc_course(wlat, wlon);
  Serial.print("GPS Bearing to waypoint: ");
  Serial.println(cou2way);
 
  int heading = getHeading();
  Serial.print("Compass data: ");
  Serial.println(heading);
  
//  double dit2way;
//  double cou2way;
//  int heading;
      //int angle = getDegrees();cou2way
      int error1 = cou2way - heading;
      if (error1 >= 180)
        error1 -= 360;
      if (error1 <= -180)
        error1 += 360;
      // Update servo and keep with range of +/- 60
      if (error1 > 60)
        error1 = 60;
      if (error1 < -60)
        error1 = -60;
     // rudder.detach(); 
      rudder.attach(9);
      rudder.write(100  + error1);
      delay(1);
      
 // ESC.write(800);                      //Send servo position - Motor speed to ESC.
  //Serial.println("motor runing");                     //Send servo 
 // delay(100);
 
 //unsigned long ttt = millis();
  
 // while (millis() - ttt < 100) {     
  if(motorrun==false){//this part works
    setMotor(false);
  //rudder.detach(); 
  }
    else if (motorrun==true){
    setMotor(true);
  //SERVO_PIN_A
  }
  //else{
  //setMotor(false);
  }
 // }
}

