void write_points(double write_date, double write_time, int write_sats, const char *write_hdop, double write_lat, const char *write_northing, double write_lon, const char *write_easting, const char *write_elipsheight, double write_speed) {
  File log_file = SD.open("abc.csv", FILE_WRITE);
  if (log_file) {
    log_file.print(write_date);
    log_file.print('_');
    log_file.print(write_time);
    log_file.print(',');
    log_file.print(write_sats);
    log_file.print(',');
    log_file.print(write_hdop);
    log_file.print(',');
    log_file.print(write_lat, 6);
    log_file.print(',');
    log_file.print(write_northing);
    log_file.print(',');
    log_file.print(write_lon, 6);
    log_file.print(',');
    log_file.print(write_easting);
    log_file.print(',');
    log_file.print(write_elipsheight);
    log_file.print(',');
    log_file.println(write_speed);
    log_file.close();
  }
}