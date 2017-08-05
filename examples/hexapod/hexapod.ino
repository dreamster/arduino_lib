#include <Dreamlib.h>

// serial configs
const bool USAR_SERIAL = true;
const long SERIAL_BPS = 115200;

Motors motors;
InfraredSensors ir_sensors;
Leds leds;

void setup() {
  if (USAR_SERIAL) {
    Serial.begin(SERIAL_BPS);
  }
}

void loop() {
  leds.redOn();
  leds.greenOff();
  motors.go(50, 50);
  delay(3000);
  
  leds.redOff();
  leds.greenOn();
  motors.go(-50, -50);
  delay(3000);

  leds.redOff();
  leds.greenOff();
  motors.go(0, 0);
  delay(3000);

}
