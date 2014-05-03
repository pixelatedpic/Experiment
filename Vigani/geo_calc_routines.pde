// calculate course between parameter values and current GPS position
double calc_course_gps(const double wlat, const double wlon) {
  double coursetodest =
    gps.courseTo(
      lat_gps,
      lon_gps,
      wlat,
      wlon);
  return coursetodest;
}

// calculate distance between parameter values and current GPS position
double calc_dist_km_gps(const double wlat, const double wlon) {
  double disttodest = gps.distanceBetween(lat_gps, lon_gps, wlat, wlon);
  return disttodest;
}

// calculate course between parameter values 
double calc_course_ab(const double alat, const double alon, const double blat, const double blon) {
  double coursetodest =
    gps.courseTo(
      alat,
      alon,
      blat,
      blon);
  return coursetodest;
}

// calculate distance between parameter values and current GPS position
double calc_dist_km_ab(const double alat, const double alon, const double blat, const double blon) {
  double disttodest = gps.distanceBetween(alat, alon, blat, blon);
  return disttodest;
}
