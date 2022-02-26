#include "progSeq.h"

progSeq robot;

void setup()
{
  Serial.begin(115200);
  robot.screen("Line sensor\nexample"); // display things

  robot.waitForButton(); // wait for button

  robot.calibrate(); // turn on 180 degrees to get the values of sensors for black and white floor

  robot.screen("calibrate done");

  robot.beepOn(); // make a beep
  delay(200); // wait 200ms
  robot.beepOff(); // stop the beep

  robot.confirmCalibration(); // wait for button while displaying line position info
}


void loop()
{
  robot.readSensors(); // update sensors value

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (int i = 0; i < 5; i++)
  {
    Serial.print(robot.getSensor(i));
    Serial.print('\t'); // print a tab character
  }
  Serial.print("\n"); // print newline
  
  delay(250);
}
