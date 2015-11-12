#include <Arduino.h>
#ifndef Dreamlib_h
#define Dreamlib_h

#define DREAMLIB_VERSION 1.0.0

#ifndef IMPORT_FROM_ARDUINO_LIBRARIES_FOLDER

char debug_string_buffer[20];
// sprintf + serial of 20 bytes takes ~200us
// sprintf + serial of 10 bytes takes ~144us
// sprintf + serial of  5 bytes takes ~108us
#define debug(formato, valor) \
  sprintf(debug_string_buffer, formato, valor); \
  Serial.print(debug_string_buffer)

#endif

#define FORWARD Motors::kDirectionForward
#define BACKWARD Motors::kDirectionBackward

class Motors {
 public:
  typedef enum MotorDirections {
    kDirectionForward = 'F',
    kDirectionBackward = 'B'
  } motorDirections_t; 
  
  Motors() {
    pinMode(kMotorRP, OUTPUT);
    pinMode(kMotorRN, OUTPUT);
    pinMode(kMotorLP, OUTPUT);
    pinMode(kMotorLN, OUTPUT);
    stop();
    
    left_motor_direction_ = 'F';
    right_motor_direction_ = 'F';
    left_motor_speed_ = 0;
    right_motor_speed_ = 0;
  }
  
  void setLeftSpeed(int speed_percentage) {
    // parameters:
    //   speed_percentage: 0 to 100
    
    left_motor_speed_ = constrain(speed_percentage, 0, 100);
    left_motor_speed_= map(left_motor_speed_, 0, 100, 0, 255);
    setMotor('L', left_motor_direction_, left_motor_speed_);
  }
  void setRightSpeed(int speed_percentage) {
    // parameters:
    //   speed_percentage: 0 to 100
    
    right_motor_speed_ = constrain(speed_percentage, 0, 100);
    right_motor_speed_= map(right_motor_speed_, 0, 100, 0, 255);
    setMotor('R', right_motor_direction_, right_motor_speed_);
  }
  
  void setLeftDirection(motorDirections_t new_direction) {
    // parameters:
    //   new_direction: motorDirections_t values
    
    left_motor_direction_ = new_direction;
    setMotor('L', left_motor_direction_, left_motor_speed_);
  }
  void setRightDirection(motorDirections_t new_direction) {
    // parameters:
    //   new_direction: motorDirections_t values
    
    right_motor_direction_ = new_direction;
    setMotor('R', right_motor_direction_, right_motor_speed_);
  }
  
  void go(int left_speed_and_direction, int right_speed_and_direction) {
    // sets all motors at once
    // parameters:
    //   left_speed_and_direction: -100 to 100
    //   right_speed_and_direction: -100 to 100
    
    // constrain speed between allowed values
    left_motor_speed_ = constrain(left_speed_and_direction, -100, 100);
    right_motor_speed_ = constrain(right_speed_and_direction, -100, 100);
    
    // change direction when speed is negative
    if (left_motor_speed_ < 0) {
      left_motor_speed_ = left_motor_speed_ * -1;
      left_motor_direction_ = kDirectionBackward;
    } else {
      left_motor_direction_ = kDirectionForward;
    }
    left_motor_speed_= map(left_motor_speed_, 0, 100, 0, 255);
    
    if (right_motor_speed_ < 0) {
      right_motor_speed_ = right_motor_speed_ * -1;
      right_motor_direction_ = kDirectionBackward;
    } else {
      right_motor_direction_ = kDirectionForward;
    }
    right_motor_speed_= map(right_motor_speed_, 0, 100, 0, 255);
    
    setMotor('L', left_motor_direction_, left_motor_speed_);
    setMotor('R', right_motor_direction_, right_motor_speed_);
    
  }
  
  void stop() {
    left_motor_speed_ = 0;
    right_motor_speed_ = 0;
    digitalWrite(kMotorLP, LOW);
    digitalWrite(kMotorLN, LOW);
    digitalWrite(kMotorRP, LOW);
    digitalWrite(kMotorRN, LOW);
  }
    
 private:
  static const int kMotorLP = 5;
  static const int kMotorLN = 6;
  static const int kMotorRP = 9;
  static const int kMotorRN = 10;

  char left_motor_direction_;
  char right_motor_direction_ ;
  int left_motor_speed_;
  int right_motor_speed_;
  
  void setMotor(char motor, char dir, int pwm) {
    // parameters
    //   motor: 'R' or 'L'
    //   dir (direction): 'F' or 'B'
    //   pwm: 0 to 255
    
    pwm = constrain(pwm, 0, 255);
    
    if (motor == 'L') {
      if (dir == 'F') {
        analogWrite(kMotorRP, pwm);
        digitalWrite(kMotorRN, LOW);
      } else if (dir == 'B') {
        analogWrite(kMotorRN, pwm);
        digitalWrite(kMotorRP, LOW);
      }
    } else if (motor == 'R') {
      if (dir == 'F') {
        analogWrite(kMotorLP,  pwm);
        digitalWrite(kMotorLN, LOW); 
      } else if (dir == 'B') {
        analogWrite(kMotorLN,  pwm);
        digitalWrite(kMotorLP, LOW); 
      }
    }
  }
};

class InfraredSensors {
 public:
  InfraredSensors() {
    // no pin initialization: analogRead doesn't need setting pinMode 
    // to OUTPUT to work
    right_sensor_ = 'R';
    left_sensor_ = 'L';
  }
  
  int left() {
    return infraredSensorMeasure(left_sensor_);
  }
  int right() {
    return infraredSensorMeasure(right_sensor_);
  }
    
 private:
  static const int kRSense = A0;
  static const int kLSense = A1;

  char right_sensor_ ;
  char left_sensor_;
  
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

class UltrasonicSensors {
 public:
  UltrasonicSensors() {
    pinMode(kTriggerPinA, OUTPUT);
    pinMode(kEchoPinA, INPUT);
    
    pinMode(kTriggerPinB, OUTPUT);
    pinMode(kEchoPinB, INPUT);
    
    pinMode(kTriggerPinC, OUTPUT);
    pinMode(kEchoPinC, INPUT); 
    
    last_good_known_value_a_ = 0;
    last_good_known_value_b_ = 0;
    last_good_known_value_c_ = 0;
    
    // measuring 400 cm (the sensor's maximum sensing distance) 
    // takes at most, 24 ms
    sensor_timeout_us_ = 24L * 1000L;
    
  }
  
  long a() {
    return ultrasonicSensorMeasure(kSensorA);
  }
  long b() {
    return ultrasonicSensorMeasure(kSensorB);
  }
  long c() {
    return ultrasonicSensorMeasure(kSensorC);
  }
  void setMaximumSensingDistance(int distance) {
    distance = constrain(distance, 0, 400);
    // measuring 400 cm (the sensor's maximum sensing distance) 
    // takes at most, 24 ms
    sensor_timeout_us_ = distance * 60L;
  }
    
 private:
  static const int kTriggerPinA = A3; 
  static const int kEchoPinA = 8;
  static const int kTriggerPinB = A4;
  static const int kEchoPinB = 2;
  static const int kTriggerPinC = A5;
  static const int kEchoPinC = 7;
  static const char kSensorA = 'A';
  static const char kSensorB = 'B';
  static const char kSensorC = 'C';

  int last_good_known_value_a_;
  int last_good_known_value_b_;
  int last_good_known_value_c_;
  unsigned int sensor_timeout_us_;
  
  int ultrasonicSensorMeasure(char sensor) {
    // parameters:
    //   sensor: 'A', 'B' or 'C'
    
    const int kNumberOfSamples = 2; // only 16 readings fit inside an int
    unsigned int duration = 0;
    int distance = 0;
    int pin_trigger = 0;
    int pin_echo = 0;
    int last_good_known_value = 0;
    
    if (sensor == kSensorA) {
      pin_trigger = kTriggerPinA;
      pin_echo = kEchoPinA;
      last_good_known_value = last_good_known_value_a_;
    } else if (sensor == kSensorB) {
      pin_trigger = kTriggerPinB;
      pin_echo = kEchoPinB;
      last_good_known_value = last_good_known_value_b_;
    } else if (sensor == kSensorC) {
      pin_trigger = kTriggerPinC;
      pin_echo = kEchoPinC;
      last_good_known_value = last_good_known_value_c_;
    }
    // read n times and average the readings    
    for (int i = 0; i < kNumberOfSamples; i++) {
      digitalWrite(pin_trigger, HIGH);
      digitalWrite(pin_trigger, LOW);
      duration = pulseIn(pin_echo, HIGH, sensor_timeout_us_);
      distance += duration * 5L / 291L; // us to cm
    }
    distance = distance / kNumberOfSamples;
    
    if (distance >= 4000 || distance <= 0) {
      distance = last_good_known_value;
    } else {
      if (sensor == kSensorA) {
        last_good_known_value_a_ = distance;
      } else if (sensor == kSensorB) {
        last_good_known_value_b_ = distance;
      } else if (sensor == kSensorC) {
        last_good_known_value_c_ = distance;
      }
    }
    
    return (distance + last_good_known_value) / 2;
  } 
};

class Leds {
 public:
  Leds() {
    pinMode(kPinLedBlue, OUTPUT);
    pinMode(kPinLedRed, OUTPUT);
    pinMode(kPinLedGreen, OUTPUT);
  }
  
  void blueOn() {
    digitalWrite(kPinLedBlue, HIGH);
  }
  void blueOff() {
    digitalWrite(kPinLedBlue, LOW);
  }
  void blueToggle() {
    digitalWrite(kPinLedBlue, (digitalRead(kPinLedBlue) == 0 ? HIGH : LOW));
  }
  
  void redOn() {
    digitalWrite(kPinLedRed, HIGH);
  }
  void redOff() {
    digitalWrite(kPinLedRed, LOW);
  }
  void redToggle() {
    digitalWrite(kPinLedRed, (digitalRead(kPinLedRed) == 0 ? HIGH : LOW));
  }
  
  void greenOn() {
    digitalWrite(kPinLedGreen, HIGH);
  }
  void greenOff() {
    digitalWrite(kPinLedGreen, LOW);
  }
  void greenToggle() {
    digitalWrite(kPinLedGreen, (digitalRead(kPinLedGreen) == 0 ? HIGH : LOW));
  }
  
 private:
  // pins
  static const int kPinLedBlue = 13;
  static const int kPinLedRed = 12;
  static const int kPinLedGreen = 11;

};

#endif