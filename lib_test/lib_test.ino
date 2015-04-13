#include "motors.h"
#include "infrared_sensors.h"
#include "ultrasonic_sensors.h"

// pins
const int kPinLed = 13;
const int kPinLedRed = 12;
const int kPinLedGreen = 11;

// serial config
const bool kUseSerial = true;
const int kSerialRate = 9600;

Motors motors;
InfraredSensors irSensors;
UltrasonicSensors usSensors;

long us_sensor_a;
long us_sensor_b;
long us_sensor_c;

char buffer[50];

void setup() {
  
  pinMode(kPinLed, OUTPUT);
  pinMode(kPinLedRed, OUTPUT);
  pinMode(kPinLedGreen, OUTPUT);
  digitalWrite(kPinLedRed, LOW);
  digitalWrite(kPinLedGreen, LOW);  
  digitalWrite(kPinLed, LOW);  
  
  if (kUseSerial) {
    Serial.begin(kSerialRate);
    // wait until the serial port is opened
    //while (!Serial) continue; 
  }
  
  test_leds();
  leds_off();
}

void test_leds() {
  digitalWrite(kPinLedRed, HIGH);
  delay(1000);
  digitalWrite(kPinLedRed, LOW);
  
  digitalWrite(kPinLedGreen, HIGH);
  delay(1000);
  digitalWrite(kPinLedGreen, LOW);
  
  digitalWrite(kPinLed, HIGH);
  delay(1000);
  digitalWrite(kPinLed, LOW);

}

void leds_off() {
  digitalWrite(kPinLedRed, LOW);
  digitalWrite(kPinLedGreen, LOW);
  digitalWrite(kPinLed, LOW);
}

void loop() {
  digitalWrite(kPinLed, !(digitalRead(kPinLed)));
  
  leds_off();
  
  // test all sensors
  int ir_sensor_r = irSensors.right();
  int ir_sensor_l = irSensors.left();
  us_sensor_a = 666;
  us_sensor_b = 666;
  us_sensor_c = 666;
  us_sensor_a = usSensors.a();
  us_sensor_b = usSensors.b();
  us_sensor_c = usSensors.c();
  sprintf(buffer, "Sensor A: %.4d ", us_sensor_a);
  Serial.print(buffer);
  delay(1);
  sprintf(buffer, "Sensor B: %.4d ", us_sensor_b);
  Serial.print(buffer);
  delay(1);
  sprintf(buffer, "Sensor C: %.4d\n", us_sensor_c);
  Serial.print(buffer);
  delay(1);

 
  if (us_sensor_a < 10) {
    digitalWrite(kPinLedRed, HIGH);
    motors.go(-25, -25);
  } else {
    motors.go(25, 25);
  }
  if (us_sensor_b < 10) {
    digitalWrite(kPinLed, HIGH);
  }
  if (us_sensor_c < 10) {
    digitalWrite(kPinLedGreen, HIGH);
  }
  delay(1000);
  
}
