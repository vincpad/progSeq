#include "progSeq.h"

progSeq robot;

void setup() {
  Serial.begin(115200);

  robot.screen("Waveshare\nAlphabot2\nPress to calibrate");

  robot.waitForButton(); // wait for button

  robot.calibrate();

  robot.confirmCalibration(); // wait for button while displaying line position info

  robot.screen("Go !");
}

void loop() {
  
  int maxSpeed = 100;

  robot.followLine(maxSpeed);

  robot.readSensors(); // update sensors value

  if(robot.getSensor(0) > 500 && robot.getSensor(4) > 500){ // get sensor n° N value
    robot.setSpeed(0, 0);
  }
  for(int i=0; i<4; i++){
    robot.setColor(i, RED);
  }
  
}

