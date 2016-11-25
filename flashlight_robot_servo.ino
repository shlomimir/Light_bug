#include <Servo.h>

Servo servoRight;  // create servo object to control a servo
Servo servoLeft;

int servoRightPin = 10;
int servoLeftPin = 9;

int lightPinR = 0;  //define a pin for Photo resistor
int lightPinL = 1;
int lightPinC = 2;
int ledPin = 11;   //define a pin for LED

int lightReadingRight;
int lightToleranceRight; // Sensor reading needed to trigger right turn

int lightReadingCenter;
int lightToleranceCenter; // Sensor reading needed to trigger forward movement

int lightReadingLeft;
int lightToleranceLeft; // Sensor reading needed to trigger left turn

void setup()
{
  Serial.begin(9600);  //Begin serial communcation

  servoRight.attach(servoRightPin);
  servoLeft.attach(servoLeftPin);

  // calibrate during the first five seconds
  int sensorMax;

  while (millis() < 5000) {
    int sensorValueR = analogRead(lightPinR);
    int sensorValueL = analogRead(lightPinL);
    int sensorValueC = analogRead(lightPinC);

    // record the maximum sensor value
    if (sensorValueR > sensorMax) {
      sensorMax = sensorValueR;
    }
    else if (sensorValueL > sensorMax) {
      sensorMax = sensorValueL;
    }
    else if (sensorValueC > sensorMax) {
      sensorMax = sensorValueC;
    }

    //set sensor tolerances to max + extra
    lightToleranceRight = sensorMax + 50;
    lightToleranceLeft = sensorMax + 50;
    lightToleranceCenter = sensorMax + 50;
    Serial.println(sensorMax);
  }
}

void loop()
{
  lightReadingRight = analogRead(lightPinR);
  Serial.print(" Right: ");
  Serial.print(lightReadingRight); //Write the value of the photoresistor to the serial monitor.

  lightReadingLeft = analogRead(lightPinL);
  Serial.print(" , Left: ");
  Serial.print(lightReadingLeft);

  lightReadingCenter = analogRead(lightPinC);
  Serial.print(" , Center: ");
  Serial.print(lightReadingCenter);

  Serial.print(" , Max: ");
  Serial.println(lightToleranceCenter);

  //Move forward if enough light is detected from center
  if (lightReadingCenter > lightToleranceCenter)
  {
    servoRight.write(180);
    servoLeft.write(0);
  }
  else if (lightReadingRight > lightToleranceRight) //turn right
  {
    servoRight.write(0);
    servoLeft.write(0);
  }
  else if (lightReadingLeft > lightToleranceLeft) //turn left
  {
    servoRight.write(180);
    servoLeft.write(180);
  }
  else { //stop
    servoRight.write(90);
    servoLeft.write(90);
  }

  delay(10); //short delay for faster response to light.
}
