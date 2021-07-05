#ifndef PROGSEQ_H
#define PROGSEQ_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX2.h>
#include <Adafruit_SSD13062.h>
#include <TRSensors.h>
#include <Wire.h>

#define PWMA   6           //Left Motor Speed pin (ENA)
#define AIN2   A0          //Motor-L forward (IN2).
#define AIN1   A1          //Motor-L backward (IN1)
#define PWMB   5           //Right Motor Speed pin (ENB)
#define BIN1   A2          //Motor-R forward (IN3)
#define BIN2   A3          //Motor-R backward (IN4)
#define PIN 7
#define NUM_SENSORS 5
#define OLED_RESET 9
#define OLED_SA0   8
#define Addr 0x20
#define IR  4              //he infrare remote receiver pin 
#define ECHO   2
#define TRIG   3

#define KEY2 0x18                 //Key:2 
#define KEY8 0x52                 //Key:8 
#define KEY4 0x08                 //Key:4 
#define KEY6 0x5A                 //Key:6 
#define KEY1 0x0C                 //Key:1 
#define KEY3 0x5E                 //Key:3 
#define KEY5 0x1C                 //Key:5
#define SpeedDown 0x07            //Key:VOL-
#define SpeedUp 0x15              //Key:VOL+
#define ResetSpeed 0x09           //Key:EQ
#define Repeat 0xFF               //press and hold the key

#define beep_on  PCF8574Write(0xDF & PCF8574Read())
#define beep_off PCF8574Write(0x20 | PCF8574Read())

Adafruit_SSD1306 display(OLED_RESET, OLED_SA0);

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

class progSeq
{
  public:
	
		progSeq();

		void waitForButton();

		void waitForButton2();

		void screen(String text);

		void calibrate(); // calibrate line sensors

		void setSpeed(int left, int right); // -255 to 255
	  
		void followLine(int maxSpeed); // move motors according to line position

		void readSensors(); // get sensors state

		int getSensor(int index); // get sensors values, index 0 to 5

		int getDistance();

		void cycleRGB();

	private:
		
		unsigned int sensorValues[NUM_SENSORS];

		TRSensors trs =   TRSensors();

		uint32_t Wheel(byte WheelPos);
		void PCF8574Write(byte data);
		byte PCF8574Read();

};

#endif
