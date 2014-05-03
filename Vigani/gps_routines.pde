bool feed_gps() {
  while (Serial1.available()) {
    if (gps.encode(Serial1.read())) {
      return true;
    }
  }
  return false;
}

void getcur_gps()
{
  feed_gps();
  fix_gps = fix.value();
  //Serial.println(fix_gps);
  if (fix_gps >= "1")
  {
    feed_gps();
    if (gps.location.isUpdated())
    {
      lat_gps = gps.location.lat();
      lon_gps = gps.location.lng();
      write_points(gps.date.value(), gps.time.value(), gps.satellites.value(), h_dop.value(), gps.location.lat(), northing.value(), gps.location.lng(), easting.value(), ellipsoidalHeight.value(), gps.speed.knots());
    }
  }
}