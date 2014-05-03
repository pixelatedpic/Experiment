
void setup_hmc5883l() {
  //Setup the HMC5883L, and check for errors
  int error;
  error = compass.SetScale(1.3); //Set the scale of the compass.
  if (error != 0) ; //Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if (error != 0); // Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
}

float get_heading() {
  //Serial.println("Fetch heading from compass: ");
  //Get the reading from the HMC5883L and calculate the heading
  MagnetometerScaled scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float declinationAngle = -0.05235;
  float heading = atan2(scaled.YAxis, scaled.XAxis) + declinationAngle;

  // If you have an EAST declination, use += declinationAngle, if you have a WEST declination, use -= declinationAngle
  heading -= declinationAngle;
  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;
  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;
  //-0.0523598776

  //Serial.println(heading);
  return (int) (heading * 180 / M_PI); //radians to degrees
}
