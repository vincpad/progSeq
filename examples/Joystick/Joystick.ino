#include "progSeq.h"

progSeq robot;

int Speed = 150;
void forward();
void backward();
void right();
void left();
void stop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Joystick example!!");
}

void loop() {
  // put your main code here, to run repeatedly:
  int joyValue = robot.getJoystick();
  if(joyValue != JOY_UNKNOWN)
  {
    robot.beepOn();
    switch(joyValue)
    { 
      case JOY_UP:
        forward();
        Serial.println("up");break; 
      case JOY_RIGHT:
        right();
        Serial.println("right"); break;
      case JOY_LEFT:
        left();
        Serial.println("left");break; 
      case JOY_DOWN:
        backward();
        Serial.println("down");break;
      case JOY_CENTER:
        forward();
        Serial.println("center");break;
      default :
        Serial.println("unknown\n");
    }
    robot.beepOff();
  }
}

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
