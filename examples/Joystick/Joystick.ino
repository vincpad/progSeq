#include "progSeq.h"

progSeq robot;

int Speed = 150;

// define functions that will be trigerred by the joystick
void forward(){
  robot.setSpeed(Speed, Speed);
}
void backward(){
  robot.setSpeed(-Speed, -Speed);
}
void right(){
  robot.setSpeed(Speed, -Speed); 
}
void left(){
  robot.setSpeed(-Speed, Speed);
}
void stop(){
  robot.setSpeed(0, 0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  robot.screen("Move joystick"); // display things
}

void loop() {
  int joyValue = robot.getJoystick(); // read the joystick position
  if(joyValue != JOY_UNKNOWN) // if the position is a known one
  {
    switch(joyValue)
    { 
      case JOY_UP:
        forward();
        Serial.println("up"); // send text serial port
        robot.screen("up"); // display text
        break; 
      case JOY_RIGHT:
        right();
        Serial.println("right"); // send text serial port
        robot.screen("right"); // display text
        break;
      case JOY_LEFT:
        left();
        Serial.println("left"); // send text serial port
        robot.screen("left"); // display text
        break; 
      case JOY_DOWN:
        backward();
        Serial.println("down"); // send text serial port
        robot.screen("down"); // display text
        break;
      case JOY_CENTER:
        stop();
        Serial.println("center"); // send text serial port
        robot.screen("center"); // display text
        break;
      default :
        Serial.println("unknown"); // send text serial port
        robot.screen("unknown"); // display text
    }
  }
}


