const int armValue = 800; //"zero" position for arming ESC. As some wont arm with a '0' value from the arduino.

unsigned long time;
boolean motorrun = false;
int speed;
boolean reverse = false;
String fixed;
File waypoints;
char c = 0;
char byteRead;
int tot_wps_infile;
double lat_gps;
double lon_gps;
double alat;
double alon;
double blat;
double blon;
String fix_gps;
int waypoint;
boolean homei = false;
double wlat, wlon;
double dlat, dlon;
int ESCval;
double WP_Radius = 3; // radius which select next waypoint and compute