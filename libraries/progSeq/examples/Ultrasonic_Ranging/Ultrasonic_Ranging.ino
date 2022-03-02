#include "progSeq.h"

void setup()
{
  Serial.begin(115200);
  initRobot();
}

void loop()
{
  int distance = getDistance(); // get distance
  if((2 < distance) && (distance < 400)){      //Ultrasonic range ranging 2cm to 400cm
    //print distance on serial
    Serial.print("Distance = ");
    Serial.print(distance);       
    Serial.println("cm");
    //print distance on screen
    screen("Distance:\n" + String(distance) + " cm"); // display things
  }
  else
  {
    Serial.println("!!! Out of range");      
  }
  delay(250);
}
