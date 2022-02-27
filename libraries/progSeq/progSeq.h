#ifndef PROGSEQ_H
#define PROGSEQ_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <TRSensors.h>
#include <Wire.h>

#include <Arduino.h>

#define PWMA 6   // Left Motor Speed pin (ENA)
#define AIN2 A0  // Motor-L forward (IN2).
#define AIN1 A1  // Motor-L backward (IN1)
#define PWMB 5   // Right Motor Speed pin (ENB)
#define BIN1 A2  // Motor-R forward (IN3)
#define BIN2 A3  // Motor-R backward (IN4)
#define PIN 7
#define NUM_SENSORS 5
#define OLED_RESET 9
#define OLED_SA0 8
#define Addr 0x20
#define IR 4  // he infrare remote receiver pin
#define ECHO 2
#define TRIG 3

#define KEY2 0x18        // Key:2
#define KEY8 0x52        // Key:8
#define KEY4 0x08        // Key:4
#define KEY6 0x5A        // Key:6
#define KEY1 0x0C        // Key:1
#define KEY3 0x5E        // Key:3
#define KEY5 0x1C        // Key:5
#define SpeedDown 0x07   // Key:VOL-
#define SpeedUp 0x15     // Key:VOL+
#define ResetSpeed 0x09  // Key:EQ
#define Repeat 0xFF      // press and hold the key

#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define WHITE 0xFFFFFF

#define RIGHT 0X40
#define LEFT  0x80

#define JOY_UNKNOWN -1
#define JOY_LEFT 1
#define JOY_RIGHT 2
#define JOY_UP 3
#define JOY_DOWN 4
#define JOY_CENTER 5


#define beep_on PCF8574Write(0xDF & PCF8574Read())
#define beep_off PCF8574Write(0x20 | PCF8574Read())

extern Adafruit_SSD1306 display;

extern Adafruit_NeoPixel RGB;

class progSeq {
 public:
 /**
  * @brief Construct a robot object
  * 
  */
  progSeq();
  /**
   * @brief Init the robot
   * 
   */
  void init();

  /**
   * @brief Blocking function that waits for the joystick button to be pressed.
   * 
   */
  void waitForButton();
  /**
   * @brief Blocking function that waits for the joystick button to be pressed, while displaying the black line position to check if the calibration has been done properly.
   * 
   */
  void confirmCalibration();
  /**
   * @brief Display a text on the oled screen
   * 
   * @param text Multiline text to display, add a `\n` to print on the next line.
   */
  void screen(String text);
  /**
   * @brief Start a calibration (the robots turns left then right to find the highest and lowest possible brightness for the floor).
   * 
   */
  void calibrate();  // calibrate line sensors
  /**
   * @brief Set the speed for left and right motors
   * 
   * @param left An integer between -255 (backwards full speed) and 255 (forward fulls speed) for the left motor
   * @param right An integer between -255 (backwards full speed) and 255 (forward fulls speed) for the right motor
   */
  void setSpeed(int left, int right);  // -255 (backward) to 255 (forward)
  /**
   * @brief Execute a follow line code.
   * @brief When this is executed in a loop, the robot will read the line position and modify its motor speeds to go forward while saying on the line.
   * 
   * @param maxSpeed The running speed of the robot (0 to 200 recommended)
   */
  void followLine(int maxSpeed);  // move motors according to line position
  /**
   * @brief Read the line sensors value and store them in RAM for further readings.
   * @brief NOTE : As it's a void, it doesn't return anything, you have to call getSensor(int index) to get the actual values for each of the 5 sensors.
   */
  void readSensors();  // update sensors state
  /**
   * @brief Get a specific line sensor value.
   * @brief NOTE : To get updated values, you must first run readSensors().
   * 
   * @param index The id of the sensor tou want to get the value from, between 0 and 5.
   * @return The value of the sensor, between 0 and 1000;.
   */
  int getSensor(int index);  // get sensors values, index 0 to 5
  /**
   * @brief Get the ultrasonic range distance.
   * 
   * @return Distance in cm. 
   */
  int getDistance();
  /**
   * @brief Read the front infrared proximity sensors values and store them in RAM for further readings.
   * @brief NOTE : As it's a void, it doesn't return anything, you have to call getObstacle(byte sensor) to get the actual values for each of the 2 sensors.
   * 
   */
  void readObstacle();
  /**
   * @brief Get a specific infrared proximity sensor value.
   * @brief NOTE : To get updated values, you must first run readObstacle().
   * 
   * @param sensor The sensor you want to read value from (`LEFT` or `RIGHT`).
   * @return true if there is an obstacle.
   * @return false if there is no obstacle.
   */
  bool getObstacle(byte sensor);
  /**
   * @brief Set the RGB LED i to the color of your choice.
   * 
   * @param i The index of the led you want to set the color.
   * @param color An RGB color, you can use `RED`, `BLUE`, `GREEN`, `BLACK` and `WHITE`, but you can also use hexadecimal codes (`0xRRGGBB`).
   */
  void setColor(int i, uint32_t color);
  /**
   * @brief Start the buzzer.
   * 
   */
  void beepOn();
  /**
   * @brief Stop the buzzer.
   * 
   */
  void beepOff();
  /**
   * @brief Get the Joystick position.
   * 
   * @return `JOY_UNKNOWN` if the position is unknown.
   * @return 'JOY_CENTER', `JOY_LEFT`, `JOY_RIGHT`, `JOY_UP` or `JOY_DOWN` in other cases.
   */
  int getJoystick();

 private:
  unsigned int sensorValues[NUM_SENSORS];

  TRSensors trs = TRSensors();

  int obstacle;

  void PCF8574Write(byte data);
  byte PCF8574Read();
};

#endif


