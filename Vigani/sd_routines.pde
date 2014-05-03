//read a specific waypoint lat,lon from SD card.
void sd_wp_read() 
{
  String returned_wp;
  returned_wp = locate_wp(waypoint);

  String latdff = returned_wp.substring(0, 8); //read the line and take out what we need
#ifdef DEBUG1
  Serial.print("file lat: ");
  Serial.println(latdff);
#endif
  char latbuf[latdff.length()];
  latdff.toCharArray(latbuf, latdff.length());
  dlat = atof(latbuf);


  String londff = returned_wp.substring(9, 18);
#ifdef DEBUG1
  Serial.print("file lon: ");
  Serial.println(londff);
#endif
  char lonbuf[londff.length()];
  londff.toCharArray(lonbuf, londff.length());
  dlon = atof(lonbuf);
}

String locate_wp(int needed_wp) {
  String lat_lon = "";
  int curr_line = 0;

  if (SD.exists("wp.txt")) { //checking if the file exists
    waypoints = SD.open("wp.txt", FILE_READ);

    while (waypoints.available())
    {
      c = waypoints.read();

      if (c == '\n')
      {
        curr_line++;
      }

      if (curr_line == needed_wp)
      {
        lat_lon += c;
        lat_lon.trim();

        if (c == ';')
        {
          waypoints.flush();
          waypoints.close();
          return lat_lon;
        }
      }
    }
    waypoints.flush();
    waypoints.close();

    if (!waypoints.available()) {
      lat_lon = "NMWPS";
      return lat_lon;
    }

  } else {
#ifdef DEBUG
    Serial.println(F("Could not open the file"));
#endif
  }
}

/*
Counts the total wap points in given file.
Uses locate_wp() function.
Returns count (type int).
*/
int total_wps()
{
  int total_wps;
  for (total_wps = 0; total_wps <= 1000; total_wps++)
  {
    String check_wp;
    check_wp = locate_wp(total_wps);
    if (check_wp == "NMWPS")
    {
      return total_wps;
    }
  }
}