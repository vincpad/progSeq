#include <progSeq.h>

progSeq robot;

void setup() {
  Serial.begin(115200);

  robot.screen("Waveshare\nAlphabot2\nPress to calibrate");

  robot.waitForButton(); // wait for button

  robot.calibrate();

  robot.waitForButton2(); // wait for button while displaying line position info

  robot.screen("Go !");
}

void loop() {
  
  int maxSpeed = 100;

  robot.followLine(maxSpeed);

  robot.readSensors();

  if(robot.getSensor(0) > 500 && robot.getSensor(4) > 500){
    robot.setSpeed(0, 0);
  }

  robot.cycleRGB();
}
