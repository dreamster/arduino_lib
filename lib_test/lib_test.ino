#include "motors.h"
#include "infrared_sensors.h"
#include "ultrasonic_sensors.h"

// pins
const int kPinLed = 13;

// serial config
const bool kUseSerial = true;
const int kSerialRate = 9600;

Motors motors;
InfraredSensors irSensors;
UltrasonicSensors usSensors;

void setup() {
  
  pinMode(kPinLed, OUTPUT);
  
  if (kUseSerial) {
    Serial.begin(kSerialRate);
    // wait until the serial port is opened
    while (!Serial) continue; 
  }
  
}

void loop() {
  char buffer[30];
  
  digitalWrite(kPinLed, !(digitalRead(kPinLed)));

  // test all sensors
  int ir_sensor_r = irSensors.right();
  int ir_sensor_l = irSensors.left();
  long us_sensor_a = usSensors.a();
  long us_sensor_b = usSensors.b();
  long us_sensor_c = usSensors.c();
  sprintf(buffer, "R%.4d L%.4d A%.4d B%.4d C%.4d", 
                  ir_sensor_r, ir_sensor_l,
                  us_sensor_a, us_sensor_b, us_sensor_c);
  Serial.println(buffer);
  delay(1);
  
  motors.go(-100, 100);
  delay(500);

  motors.softStop();
  delay(200);

  motors.go(100, -100);
  delay(500);

  motors.hardStop();
  delay(200);

  motors.setLeftDirection(Motors::kDirectionBackward);
  motors.setRightDirection(Motors::kDirectionForward);
  motors.setLeftSpeed(40);
  motors.setRightSpeed(40);
  delay(500);

  motors.softStop();
  delay(200);

  motors.setLeftDirection(Motors::kDirectionForward);
  motors.setRightDirection(Motors::kDirectionBackward);
  motors.setLeftSpeed(40);
  motors.setRightSpeed(40);
  delay(500);

  motors.softStop();
  delay(200);
}
