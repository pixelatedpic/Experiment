void loop() {
  bool newdata = false;
  unsigned long start = millis();

  while (millis() - start < 1000) {
    if (feed_gps()) {
      newdata = true;
    }
  }
  feed_gps();
  #if (DummyFIX)
	fixed = 1;
  #else
	fixed = fix.value();
  #endif
  if (homei == false && fixed >= "1") {
    //Serial.println("fixed");
    //Serial.print("current waypoint: ");
    //  Serial.print("$");
    //  Serial.print(gps.date.value());
    //  Serial.print(",");
    //  Serial.print(gps.time.value());
    //  Serial.print(",");
#ifdef DEBUG
    Serial.print("current waypoint: ");
    Serial.println(waypoint);
#endif

    if (newdata) {
      getcur_gps();
#ifdef DEBUG
      Serial.print("GPS LAT: ");
      Serial.println(lat_gps, 6);
      Serial.print("GPS LON: ");
      Serial.println(lon_gps, 6);
#endif
    }
    sd_wp_read(); //read Lat and Lon from th SD card to compute
    steering();
    double DIS_TO_WP = calc_dist_km_gps(dlat, dlon );
#ifdef DEBUG
    Serial.print("Distance to waypoint: ");
    Serial.println(DIS_TO_WP);
#endif

    if (DIS_TO_WP < WP_Radius)//check the distance is less than WP_Radius
    {
      //ESCval = 1166;
      //Serial.println("DROP SPEED");
      if (tot_wps_infile == waypoint)
      {
        homei = true;
        motorrun = false;
        ESC.write(600);//stops motor

#ifdef DEBUG
        Serial.println("END OF TRIP");
#endif
      }

      waypoint++;
    }

    //this part works
    if (motorrun == false)
    {
      set_motor(false);
    }
    else if (motorrun == true)
    {
      set_motor(true);
    }
  }
}