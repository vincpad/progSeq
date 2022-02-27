#include "progSeq.h"

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(OLED_RESET, OLED_SA0);

// Base class data member initialization (called by derived class init())
progSeq::progSeq() {
  // nothing to do here
}

void progSeq::init() {
  Serial.begin(115200);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init
  pinMode(IR, INPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void progSeq::screen(String text) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  while (text.length() > 0) {
    char firstChar = text.charAt(0);
    if (firstChar != '\n') {
      display.print(firstChar);
    } else {
      display.println();
    }
    text = text.substring(1);
  }
  display.display();
}

void progSeq::waitForButton() {
  byte value = 0;

  while (value != 0xEF)  // wait button pressed
  {
    PCF8574Write(0x1F | PCF8574Read());
    value = PCF8574Read() | 0xE0;
  }
}

void progSeq::calibrate() {
  RGB.begin();
  RGB.setPixelColor(0, 0x00FF00);
  RGB.setPixelColor(1, 0x00FF00);
  RGB.setPixelColor(2, 0x00FF00);
  RGB.setPixelColor(3, 0x00FF00);
  RGB.show();
  delay(500);
  analogWrite(PWMA, 80);
  analogWrite(PWMB, 80);
  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    if (i < 25 || i >= 75) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    } else {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    trs.calibrate();  // reads all sensors 100 times
  }
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  RGB.setPixelColor(0, 0x0000FF);
  RGB.setPixelColor(1, 0x0000FF);
  RGB.setPixelColor(2, 0x0000FF);
  RGB.setPixelColor(3, 0x0000FF);
  RGB.show();  // Initialize all pixels to 'off'
}

void progSeq::confirmCalibration() {
  byte value = 0;
  while (value != 0xEF)  // wait button pressed
  {
    PCF8574Write(0x1F | PCF8574Read());
    value = PCF8574Read() | 0xE0;
    unsigned int position = trs.readLine(sensorValues) / 200;
    display.clearDisplay();
    display.setCursor(0, 25);
    display.println("Calibration Done !!!");
    display.setCursor(0, 55);
    for (int i = 0; i < 21; i++) {
      display.print('_');
    }
    display.setCursor(position * 6, 55);
    display.print("**");
    display.display();
  }
}

void progSeq::setSpeed(int left, int right) {  // -255 to 255

  digitalWrite(AIN1, left < 0);
  digitalWrite(AIN2, left > 0);
  analogWrite(PWMA, left * (-1 + 2 * (left > 0)));

  digitalWrite(BIN1, right < 0);
  digitalWrite(BIN2, right > 0);
  analogWrite(PWMB, right * (-1 + 2 * (right > 0)));
}

void progSeq::followLine(int maxSpeed) {  // move motors according to line position

  static long integral = 0, last_proportional = 0;

  unsigned int position = trs.readLine(sensorValues);

  // The "proportional" term should be 0 when we are on the line.
  int proportional = (int)position - 2000;

  // Compute the derivative (change) and integral (sum) of the position.
  int derivative = proportional - last_proportional;
  integral += proportional;

  // Remember the last position.
  last_proportional = proportional;

  // Compute the difference between the two motor power settings,
  // m1 - m2.  If this is a positive number the robot will turn
  // to the right.  If it is a negative number, the robot will
  // turn to the left, and the magnitude of the number determines
  // the sharpness of the turn.
  int power_difference = proportional / 20 + integral / 10000 + derivative * 10;

  // Compute the actual motor settings.  We never set either motor
  // to a negative value.

  if (power_difference > maxSpeed) power_difference = maxSpeed;
  if (power_difference < -maxSpeed) power_difference = -maxSpeed;
  Serial.println(power_difference);

  if (power_difference < 0) {
    setSpeed(maxSpeed + power_difference, maxSpeed);
  }

  else {
    setSpeed(maxSpeed, maxSpeed - power_difference);
  }

  if (sensorValues[1] > 900 && sensorValues[2] > 900 && sensorValues[3] > 900) {
    // There is no line .Must Stop.
    setSpeed(0, 0);
  }
}

void progSeq::readSensors() {  // get sensors state
  trs.readLine(sensorValues);
}

int progSeq::getSensor(int index) {  // get sensors values, index 0 to 5
  return sensorValues[index];
}

int progSeq::getDistance()  // Measure the distance
{
  digitalWrite(TRIG, LOW);  // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  // set trig pin 10μs , at last 10us
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);                // set trig pin low
  float Fdistance = pulseIn(ECHO, HIGH);  // Read echo pin high level time(us)
  Fdistance = Fdistance / 58;             // Y m=（X s*344）/2
  // X s=（ 2*Y m）/344 ==》X s=0.0058*Y m ==》cm = us /58
  return (int)Fdistance;
}


void progSeq::PCF8574Write(byte data) {
  Wire.beginTransmission(Addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte progSeq::PCF8574Read() {
  int data = -1;
  Wire.requestFrom(Addr, 1);
  if (Wire.available()) {
    data = Wire.read();
  }
  return data;
}

void progSeq::beepOn(){
  PCF8574Write(0xDF & PCF8574Read());
}

void progSeq::beepOff(){
  PCF8574Write(0x20 | PCF8574Read());
}

void progSeq::setColor(int i, uint32_t _color){
  RGB.setPixelColor(i, 
    static_cast<byte>((_color >> 16) & 0xFF),
    static_cast<byte>((_color >> 8) & 0xFF),
    static_cast<byte>((_color >> 0) & 0xFF)
  );
  RGB.show();
}

void progSeq::readObstacle(){
  PCF8574Write(0xC0 | PCF8574Read());   //set Pin High
  obstacle = PCF8574Read() | 0x3F;         //read Pin
}

bool progSeq::getObstacle(byte sensor){
  return !(obstacle & sensor); // to be modified
}

int progSeq::getJoystick(){
  PCF8574Write(0x1F | PCF8574Read());
  byte value = PCF8574Read() | 0xE0;
  if(value != 0xFF)
  {
    switch(value)
    { 
      case 0xFE:
        return JOY_UP; 
      case 0xFD:
        return JOY_RIGHT;
      case 0xFB:
        return JOY_LEFT;
      case 0xF7:
        return JOY_DOWN;
      case 0xEF:
        return JOY_CENTER;
      default :
        return JOY_UNKNOWN;
    }
  }
  else return JOY_UNKNOWN;
}