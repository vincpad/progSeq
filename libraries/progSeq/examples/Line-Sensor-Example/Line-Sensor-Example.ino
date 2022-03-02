#include <progSeq.h>

void setup()
{
  Serial.begin(115200);

  initRobot();
  
  screen("Line sensor\nexample"); // display things

  waitForButton(); // wait for button

  calibrate(); // turn on 180 degrees to get the values of sensors for black and white floor

  screen("calibrate done");

  beepOn(); // make a beep
  delay(200); // wait 200ms
  beepOff(); // stop the beep

  confirmCalibration(); // wait for button while displaying line position info
}


void loop()
{
  readSensors(); // update sensors value

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (int i = 0; i < 5; i++)
  {
    Serial.print(getSensor(i));
    Serial.print('\t'); // print a tab character
  }
  Serial.print("\n"); // print newline
  
  delay(250);
}
