/*
  Tilt compensated HMC5883L + ADXL345 (GY-80). Output for HMC5883L_compensation_processing.pde
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-magnetometr-hmc5883l.html
  GIT: https://github.com/jarzebski/Arduino-HMC5883L
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_ADXL345_U.h>


/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12346);

//HMC5883L compass;
//ADXL345 accelerometer;

float heading1;
float heading2;

void setup()
{
  Serial.begin(9600);
  
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
   
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_16_G);	

}

// No tilt compensation
float noTiltCompensate()
{
  sensors_event_t magevent; 
  mag.getEvent(&magevent);
  float heading = atan2(magevent.magnetic.y, magevent.magnetic.x);
  return heading;
}
 
// Tilt compensation
float tiltCompensate()
{
  // Pitch & Roll 

  float roll;
  float pitch;
  
  sensors_event_t accevent; 
  accel.getEvent(&accevent);
  
  roll = asin(accevent.acceleration.y);
  pitch = asin(-accevent.acceleration.x);

  if (roll > 0.78 || roll < -0.78 || pitch > 0.78 || pitch < -0.78)
  {
    return -1000;
  }

  // Some of these are used twice, so rather than computing them twice in the algorithem we precompute them before hand.
  float cosRoll = cos(roll);
  float sinRoll = sin(roll);  
  float cosPitch = cos(pitch);
  float sinPitch = sin(pitch);

  sensors_event_t magevent; 
  mag.getEvent(&magevent);
  // Tilt compensation
  float Xh = magevent.magnetic.x * cosPitch + magevent.magnetic.z * sinPitch;
  float Yh = magevent.magnetic.x * sinRoll * sinPitch + magevent.magnetic.y * cosRoll - magevent.magnetic.z * sinRoll * cosPitch;

  float heading = atan2(Yh, Xh);

  return heading;
}

// Correct angle
float correctAngle(float heading)
{
  if (heading < 0) { heading += 2 * PI; }
  if (heading > 2 * PI) { heading -= 2 * PI; }

  return heading;
}

void loop()
{
  // Read vectors
/*  Vector mag = compass.readNormalize();
  Vector acc = accelerometer.readScaled();*/

  // Calculate headings
  heading1 = noTiltCompensate();
  heading2 = tiltCompensate();

  if (heading2 == -1000)
  {
    heading2 = heading1;
  }

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (-0.05235) / (180 / M_PI);
  heading1 -= declinationAngle;
  heading2 -= declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  heading1 = correctAngle(heading1);
  heading2 = correctAngle(heading2);

  // Convert to degrees
  heading1 = heading1 * 180/M_PI; 
  heading2 = heading2 * 180/M_PI; 

  // Output
  Serial.print(heading1);
  Serial.print(":");
  Serial.println(heading2);

  delay(100);
}

