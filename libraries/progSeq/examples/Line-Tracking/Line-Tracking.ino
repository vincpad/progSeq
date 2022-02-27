#include <progSeq.h>

progSeq robot;

void setup() {
  robot.init();
  Serial.begin(115200);
  Serial.println("1");
  robot.screen("Waveshare\nAlphabot2\nPress to calibrate"); // display things
  Serial.println("2");
  robot.waitForButton(); // wait for button

  robot.calibrate(); // turn on 180 degrees to get the values of sensors for black and white floor

  robot.beepOn(); // make a beep
  delay(200); // wait 200ms
  robot.beepOff(); // stop the beep

  robot.confirmCalibration(); // wait for button while displaying line position info

  robot.screen("Go !"); // display things
}

void loop() {
  
  int maxSpeed = 100; // set the maximum speed for the line following program

  robot.followLine(maxSpeed); // update the sensors value

  robot.readSensors(); // update sensors value

  // read the values that has just been updated, and stop at some conditions
  if(robot.getSensor(0) > 500 && robot.getSensor(4) > 500){ // get sensor n° N value
    robot.setSpeed(0, 0);
  }

  // set all leds to red (other colors available, you can also use hex code 0xRRGGBB)
  for(int i=0; i<4; i++){
    robot.setColor(i, RED);
  }
  
}

