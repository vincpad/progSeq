#include "progSeq.h"

int Speed = 120;
unsigned long lasttime = 0;
int distance = 0;

void setup()
{
  Serial.begin(115200);  
  initRobot();
  Serial.println("Ultrasonic infrared Obstacle Avoidance example");  
}

void loop()
{
  if(millis() - lasttime >200){ // every 200ms
    lasttime = millis();
    distance = getDistance(); // get ultrasonic distance 
    Serial.print("distance = ");  // print distance on serial
    Serial.print(distance);
    Serial.println("cm");
    screen("distance :\n" + String(distance) + " cm");
  }
  
  readObstacle(); // update the infrared sensors

  if((distance < 15) || getObstacle(RIGHT) || getObstacle(LEFT))      //Ultrasonic range ranging 2cm to 400cm
  {
    Serial.println(getObstacle(LEFT));
    setSpeed(Speed, 0); // go right
    delay(200); // wait
    setSpeed(0, 0); // stop
  }
  else
  {
    setSpeed(Speed, Speed); // go forward  
  }
}