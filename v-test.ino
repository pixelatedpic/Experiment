//#include <Servo.h>
#include <PWMServo.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


SoftwareSerial ss(2, 3); // RX, TX

TinyGPSPlus gps;

HMC5883L compass;
PWMServo myservo;
int pos = 90;
//#include <SPI.h>
//#include <SD.h>

//compass pin 4,5



//#define SERVO  9
//#define CENTER 90
//#define GOAL   0

//int goal = GOAL;

int arm_time=1;
int pulse=1000;
int enablePin = 6;
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
//const double DEST_LAT = 4.2029716;
//const double DEST_LON = 73.231562;
/*
Function accepts int arg, which is the required waypoint (line)
to be returned (String type).
Also if no more wps, returns string "NMWPS".
*/
//String locate_wp(int needed_wp){
//  String lat_lon=F("");
//  int curr_line=0;
//  
//  if (SD.exists("test.txt")) { //checking if the file exists
//    waypoints = SD.open("test.txt",FILE_READ);
//    
//    while(waypoints.available()) {
//     c = waypoints.read();
//     
//     if(c=='\n') {
//       curr_line++;
//     }
//     
//     if (curr_line == needed_wp) {
//       lat_lon += c;
//       lat_lon.trim();
//       
//       if(c==';') {
//         waypoints.flush();
//         waypoints.close();
//         return lat_lon;
//       }
//      }
//    }
//    waypoints.flush();
//    waypoints.close();
//    
//    if (!waypoints.available()) {
//      lat_lon=F("NMWPS");
//      return lat_lon;
//    }
//
//  } else {
//      Serial.println(F("Could not open the file"));
//  } 
//}

/*
Counts the total wap points in given file.
Uses locate_wp() function.
Returns count (type int).
*/
//int total_wps(){
//  int total_wps;
//  for (total_wps=0; total_wps<=1000; total_wps++) {
//    String check_wp;
//    check_wp = locate_wp(total_wps);
//    if (check_wp == F("NMWPS")) {
//      return total_wps;
//    }
//  }
//}

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
//    feedGPS();
//    if (gps.date.isUpdated()) {
//      Serial.println();
//      Serial.print(gps.date.value()); 
//    }
//    
//    feedGPS();
//    if (gps.time.isUpdated()) {
//      Serial.print(F("_"));
//      Serial.print(gps.time.value()); 
//    }
//    
//    Serial.print(F(","));
//    Serial.print(gps.satellites.value());
//    Serial.print(F(","));
//    Serial.print(h_dop.value());
//    
    feedGPS();
    if (gps.location.isUpdated()) {
      lat_gps = gps.location.lat();
      lon_gps = gps.location.lng();
//      Serial.print(F(","));
//      Serial.print(gps.location.lat(),6);
//      Serial.print(F(","));
//      Serial.print(northing.value());    
//      Serial.print(F(","));
//      Serial.print(gps.location.lng(),6);
//      Serial.print(F(","));
//      Serial.print(easting.value());
    } 
    
//    feedGPS();
//    Serial.print(F(","));
//    Serial.print(ellipsoidalHeight.value());

      //feedGPS();
      //if (gps.location.isUpdated()) {
      
      //}
    
    //test courseto here...
    //calc_course();
    //calc_distKm();
    
    // TODO
    // Variables needs to be assigned to above, and those variables needs to be fed to write_points here.
    //write_points(gps.date.value(),gps.time.value(),gps.satellites.value(),h_dop.value(),gps.location.lat(),northing.value(),gps.location.lng(),easting.value(),ellipsoidalHeight.value());
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
    // disttodest=0.5;
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

/*
Function descr here...
*/
//void write_points(double write_date, double write_time, int write_sats, const char *write_hdop, double write_lat, const char *write_northing, double write_lon, const char *write_easting, const char *write_elipsheight) {
//  File log_file = SD.open("abc.csv", FILE_WRITE);
//  if (log_file) {
//    log_file.print(write_date);
//    log_file.print('_');
//    log_file.print(write_time);
//    log_file.print(',');
//    log_file.print(write_sats);
//    log_file.print(',');
//    log_file.print(write_hdop);
//    log_file.print(',');
//    log_file.print(write_lat,6);
//    log_file.print(',');
//    log_file.print(write_northing);
//    log_file.print(',');
//    log_file.print(write_lon,6);
//    log_file.print(',');
//    log_file.print(write_easting);
//    log_file.print(',');
//    log_file.println(write_elipsheight);
//    log_file.close();
//  }
//}

/*
Function descr here...
*/
//float getBearing(String dest_wp){
  // get current latlon from getcurGPS func
  // Calculate Bearing/Course 
  // Return Course, Distance
//}

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

void setup() {
  // put your setup code here, to run once:
  //hom =true;
  Serial.begin(115200);
  ss.begin(9600);
  
  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L
  
  myservo.attach(SERVO_PIN_A);
  myservo.write(90);
  delay(10);
  myservo.detach();
  
  
  pinMode(enablePin,OUTPUT);
  for(arm_time=0;arm_time<500;arm_time +=1)
  {
     digitalWrite(enablePin,HIGH);
     delayMicroseconds(1100);
     digitalWrite(enablePin,LOW);
     delay(20-(pulse/1000));
  }
  

  //SD.begin(10);
  

  //pinMode(in1Pin, OUTPUT);
  //pinMode(in2Pin, OUTPUT);
  //pinMode(enablePin, OUTPUT);

  //Serial.println(F("Calculating total WPs ..."));
  //tot_wps_infile = total_wps();
  //Serial.print(F("Total WPS in file = "));
  //Serial.println(tot_wps_infile);
  //Serial.println();
  
 // delay(2000);

//  File log_file = SD.open("abc.csv", FILE_WRITE);
//  if (log_file) {
//    log_file.println(F("#########################################")); 
//    String header = F("date_time(UTC), sats-in-use, hdop, lat, northing, lon, easting, ellipsiodal-height");
//    log_file.println(header);
//    log_file.flush();
//    log_file.close();
//  } else {
//    Serial.println(F("Couldn't open log (aquired GPS) file"));
//  } 

  waypoint=1;
  //speed = 0;// speed of motor
  //analogWrite(enablePin, 10);
  //delay(1000);
  motorrun=true;
  
}

//int speedset(){
//  speed = analogRead(potPin) / 4;
//  return speed; 
//}
 
int setMotor(boolean motorrun)//this part works
{
  int pulse=1185;
  Serial.print("Motor status: ");
  Serial.println(motorrun);
  if(motorrun){
    digitalWrite(enablePin,HIGH);
     delayMicroseconds(pulse);
     digitalWrite(enablePin,LOW);
     delay(20-(pulse/1000));  
  //analogWrite(enablePin, speeed);
  //digitalWrite(in1Pin, !reverse );
  //digitalWrite(in2Pin, reverse);
  }
  else{
  //analogWrite(enablePin, speed);
  //analogWrite(enablePin, 0);
  //digitalWrite(in1Pin, 0);
  //digitalWrite(in2Pin, 0); 
      //digitalWrite(enablePin,HIGH);
     //delayMicroseconds(pulse);
     //digitalWrite(enablePin,HIGH);
     //delayMicroseconds(1020);
     digitalWrite(enablePin,LOW);
     //delay(20-(1020/1000));
     //delay(20-(pulse/1000));
    
  }
  //return();
}


void loop() {
 // pulse=1290;
  bool newdata = false;
  unsigned long start = millis();
  
  while (millis() - start < 1000) {
    if (feedGPS()) {
      newdata = true;
    }
  }
  feedGPS();
  fixed = fix.value();
  //Serial.println(fixed);
  //&& fixed >="1"
  if (homei==false && fixed >="1"){
  //Serial.println("fixed");
  Serial.print("current waypoint: ");
  Serial.println(waypoint);  
//  
//    bool newdata = false;
//  unsigned long start = millis();
//  
//  while (millis() - start < 1000) {
//    if (feedGPS()) {
//      newdata = true;
//    }
//  }
  
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
      myservo.detach(); 
      myservo.attach(SERVO_PIN_A);
      myservo.write(100  + error1);
      delay(10);
      
  if(motorrun==false){//this part works
  setMotor(false);
  //myservo.detach(); 
  }
  else if (motorrun==true){
  setMotor(true);
  //SERVO_PIN_A
  }
  //else{
  //setMotor(false);
  //}
  }
  
  
  
}
//const double DEST_LAT = 4.2029716;
//const double DEST_LON = 73.231562;


//  float heading = getHeading();
//  Serial.println(heading);
//  delay(100); //only here to slow down the serial print
//  setMotor();
  
//  if (blah==1) {
//    int getwp;
//    tot_wps_infile--;
//    for (getwp=0; getwp<=tot_wps_infile; getwp++) {
//      String returned_wp;
//      returned_wp = locate_wp(getwp);
//      delay (100);
//      Serial.print(F("Returned lat_lon="));
//      Serial.println(returned_wp);
//    }
//    blah++;
//  }
  
  /*
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isUpdated()) {
      Serial.print(gps.location.lat());
      Serial.print(" , ");
      Serial.println(gps.location.lng());
  }
  */


  
  
 /* if (blah2<=100) {
    getcurGPS();
    blah2++;
    Serial.println();
    delay(500);
  }
*/
  
//void done(){
//setMotor(reverse);
//Serial.println();
//Serial.println("Tadaaa Back to home");
//}
