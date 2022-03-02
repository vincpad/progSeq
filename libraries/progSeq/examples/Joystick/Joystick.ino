#include "progSeq.h"

int Speed = 150;

// define functions that will be trigerred by the joystick
void forward(){
  setSpeed(Speed, Speed);
}
void backward(){
  setSpeed(-Speed, -Speed);
}
void right(){
  setSpeed(Speed, -Speed); 
}
void left(){
  setSpeed(-Speed, Speed);
}
void stop(){
  setSpeed(0, 0);
}

void setup() {
  Serial.begin(115200);
  
  initRobot();
  
  screen("Move joystick"); // display things
}

void loop() {
  int joyValue = getJoystick(); // read the joystick position
  if(joyValue != JOY_UNKNOWN) // if the position is a known one
  {
    switch(joyValue)
    { 
      case JOY_UP:
        forward();
        Serial.println("up"); // send text serial port
        screen("up"); // display text
        break; 
      case JOY_RIGHT:
        right();
        Serial.println("right"); // send text serial port
        screen("right"); // display text
        break;
      case JOY_LEFT:
        left();
        Serial.println("left"); // send text serial port
        screen("left"); // display text
        break; 
      case JOY_DOWN:
        backward();
        Serial.println("down"); // send text serial port
        screen("down"); // display text
        break;
      case JOY_CENTER:
        stop();
        Serial.println("center"); // send text serial port
        screen("center"); // display text
        break;
      default :
        Serial.println("unknown"); // send text serial port
        screen("unknown"); // display text
    }
  }
}


