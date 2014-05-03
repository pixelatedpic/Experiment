void setup() {
  // put your setup code here, to run once:
  //hom =true;
  Serial.begin(19200);
  Serial1.begin(9600);
  SD.begin(sd_cs_pin);
  //ss.begin(9600);
  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setup_hmc5883l(); //setup the HMC5883L

  //Serial.println(F("Calculating total WPs ..."));
  tot_wps_infile = total_wps();
#ifdef DEBUG
  Serial.print(F("Total WPS in file = "));
  Serial.println(tot_wps_infile);
#endif

  delay(500);

  File log_file = SD.open("abc.csv", FILE_WRITE);
  if (log_file) {
    log_file.println("#########################################");
    String header = ("date_time(UTC), sats-in-use, hdop, lat, northing, lon, easting, ellipsiodal-height, speed(Knots)");
    log_file.println(header);
    log_file.flush();
    log_file.close();
  } else {
#ifdef DEBUG
    Serial.println(F("Couldn't open log (aquired GPS) file"));
#endif
  }

  //Serial.println("Align rudder");
  rudder.attach(servo_pin);
  rudder.write(90);
  delay(10);
  //Serial.println("Rudder done");
  //rudder.detach();
  tot_wps_infile--;
  //waypoint=1;
  motorrun = true;

  //Serial.println("Start motor ARMING");
  ESC.attach(esc_pin);
  arm();
  //Serial.println("Motor Armed");

  ESCval = 1250;
  //delay(10000);

}
