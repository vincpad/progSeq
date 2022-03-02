#include <progSeq.h>

void setup() {
  Serial.begin(115200);
  initRobot();

  screen("Waveshare\nAlphabot2\nPress to calibrate"); // display things
  
  waitForButton(); // wait for button

  calibrate(); // turn on 180 degrees to get the values of sensors for black and white floor

  beepOn(); // make a beep
  delay(200); // wait 200ms
  beepOff(); // stop the beep

  confirmCalibration(); // wait for button while displaying line position info

  screen("Go !"); // display things
}

void loop() {
  
  int maxSpeed = 100; // set the maximum speed for the line following program

  followLine(maxSpeed); // update the sensors value

  readSensors(); // update sensors value

  // read the values that has just been updated, and stop at some conditions
  if(getSensor(0) > 500 && getSensor(4) > 500){ // get sensor n° N value
    setSpeed(0, 0);
  }

  // set all leds to red (other colors available, you can also use hex code 0xRRGGBB)
  for(int i=0; i<4; i++){
    setColor(i, RED);
  }
  
}

