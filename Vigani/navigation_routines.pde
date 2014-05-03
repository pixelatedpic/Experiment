void steering()
{
  int servopos = 0;
  int heading;
  int cou2way = calc_course_gps(dlat, dlon);
  int comp_head = get_heading();// get compass heading
  
#ifdef DEBUG
  Serial.print("file lat: ");
  Serial.println(dlat);
  Serial.print("file lon: ");
  Serial.println(dlon);
  Serial.print("GPS course to WP: ");
  Serial.println(cou2way);
  Serial.print("Compass data: ");
  Serial.println(comp_head);
#endif
  heading = cou2way - comp_head;

  //old code
  /*
  if (Heading >= 180)
   Heading -= 360;
  if (Heading <= -180)
   Heading += 360;
  // Update servo and keep with range of +/- 60
  if (Heading > 60)
   Heading = 60;
  if (Heading < -60)
   Heading = -60;

  //rudder.attach(12);
  int tr = rudder.read();
  rudder.write(90+Heading);
  Serial.print(rudder.read());
  Serial.print(",");
  Serial.print(gps.speed.knots());
  Serial.println(";");
  delay(1);*/
  //old code end

  if (heading < 0) heading += 360;

  if (heading > 0 && heading <= 180)
  {
    if (heading > 0 && heading <= 90)
    {
      servopos = map(heading, 0, 90, 90, 147);
    } else {
      servopos = 150;
    }
  }
  else
  {
    if (heading > 270 && heading <= 360)
    {
      servopos = map(heading, 270, 360, 33, 90);
    } else {
      servopos = 30;
    }
  }

  rudder.write(servopos);
#ifdef DEBUG
  Serial.print("Value to servo: ");
  Serial.println(rudder.read());
#endif
  //      Serial.print(gps.speed.knots());
  //      Serial.println(";");
  //delay(1);
}