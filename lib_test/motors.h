#include <Arduino.h>

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
    hardStop();
  }
  
  void setLeftSpeed(byte speed_percentage) {
    // parameters:
    //   speed_percentage: 0 to 100
    
    left_motor_speed_ = constrain(speed_percentage, 0, 100);
    left_motor_speed_= map(speed_percentage, 0, 100, 0, 255);
    setMotor('L', left_motor_direction_, left_motor_speed_);
  }
  void setRightSpeed(byte speed_percentage) {
    // parameters:
    //   speed_percentage: 0 to 100
    
    right_motor_speed_ = constrain(speed_percentage, 0, 100);
    right_motor_speed_= map(speed_percentage, 0, 100, 0, 255);
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
    if (left_speed_and_direction < 0) {
      left_motor_speed_ = map(left_speed_and_direction, -100, 0, 0, 255);
      left_motor_direction_ = kDirectionBackward;
    } else {
      left_motor_speed_= map(left_speed_and_direction, 0, 100, 0, 255);
      left_motor_direction_ = kDirectionForward;
    }
    if (right_speed_and_direction < 0) {
      right_motor_speed_ = map(right_speed_and_direction, -100, 0, 0, 255);
      right_motor_direction_ = kDirectionBackward;
    } else {
      right_motor_speed_= map(left_speed_and_direction, 0, 100, 0, 255);
      right_motor_direction_ = kDirectionForward;
    }
    setMotor('L', left_motor_direction_, left_motor_speed_);
    setMotor('R', right_motor_direction_, right_motor_speed_);
  }
  
  void hardStop() {
    digitalWrite(kMotorLP, LOW);
    digitalWrite(kMotorLN, LOW);
    digitalWrite(kMotorRP, LOW);
    digitalWrite(kMotorRN, LOW);
    softStop();
  }
    
  void softStop() {
    left_motor_speed_ = 0;
    right_motor_speed_ = 0;
    setMotor('L', left_motor_direction_, left_motor_speed_);
    setMotor('R', right_motor_direction_, right_motor_speed_);    
  }
    
 private:
  static const int kMotorLP = 5;
  static const int kMotorLN = 6;
  static const int kMotorRP = 9;
  static const int kMotorRN = 10;

  char left_motor_direction_ = 'F';
  char right_motor_direction_ = 'F';
  byte left_motor_speed_ = 0;
  byte right_motor_speed_ = 0;
  
  void setMotor(char motor, char dir, byte pwm) {
    // parameters
    //   motor: 'R' or 'L'
    //   dir (direction): 'F' or 'B'
    //   pwm: 0 to 255
    
    pwm = constrain(pwm, 0, 255);
    
    if (motor == 'R') {
      if (dir == 'F') {
        analogWrite(kMotorRP, pwm);
        digitalWrite(kMotorRN, LOW);
      } else if (dir == 'B') {
        analogWrite(kMotorRN, pwm);
        digitalWrite(kMotorRP, LOW);
      }
    } else if(motor == 'L') {
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

/*EOF*/