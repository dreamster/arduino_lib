#include <Arduino.h>

class InfraredSensors {
 public:
  InfraredSensors() {
    // no initialization: analogRead doesn't need setting pinMode 
    // to OUTPUT to work
  }
  
  int left() {
    return infraredSensorMeasure(left_sensor_);
  }
  int right() {
    return infraredSensorMeasure(right_sensor_);
  }
    
 private:
  static const int kRSense = A1;
  static const int kLSense = A0;

  char right_sensor_ = 'R';
  char left_sensor_ = 'L';
  
  int infraredSensorMeasure(char sensor) {
    // parameters:
    //   sensor: 'R' or 'L'
    
    int ir_sensor_value = 0;
    
    if (sensor == 'R') {
      ir_sensor_value = analogRead(kRSense);
    } else if (sensor == 'L') {
      ir_sensor_value = analogRead(kLSense);    
    }
    
    return ir_sensor_value;
  }
};

