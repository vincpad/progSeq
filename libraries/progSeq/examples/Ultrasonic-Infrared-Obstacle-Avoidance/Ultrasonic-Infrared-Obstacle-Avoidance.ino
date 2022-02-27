#include "progSeq.h"

progSeq robot;

int Speed = 120;
unsigned long lasttime = 0;

void setup()
{
  robot.init();
  Serial.begin(115200);  
  Serial.println("Ultrasonic infrared Obstacle Avoidance example");  
}

void loop()
{
  int distance = 0;
  if(millis() - lasttime >200){ // every 200ms
    lasttime = millis();
    distance = robot.getDistance(); // get ultrasonic distance 
    Serial.print("distance = ");  // print distance on serial
    Serial.print(distance);
    Serial.println("cm");
  }
  
  robot.readObstacle(); // update the infrared sensors

  distance = 100;

  if((distance < 15) || robot.getObstacle(RIGHT) || robot.getObstacle(LEFT))      //Ultrasonic range ranging 2cm to 400cm
  {
    Serial.println(robot.getObstacle(LEFT));
    robot.setSpeed(Speed, 0); // go right
    delay(200); // wait
    robot.setSpeed(0, 0); // stop
  }
  else
  {
    Serial.println("fw");
    robot.setSpeed(Speed, Speed); // go forward  
  }
}