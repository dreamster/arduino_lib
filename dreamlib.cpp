//////////////////////////////////////////////////////////////////////
///////////// ULTRASONIC SENSOR CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////

void UltrasonicSensor::UltrasonicSensor(void) {
  trigger_ = ULTRASONIC_SENSOR_TRIGGER_A;
  echo_ = ULTRASONIC_SENSOR_ECHO_A;
}

void UltrasonicSensor::UltrasonicSensor(char sensor) {
  if(sensor == 'A') {
    trigger_ = ULTRASONIC_SENSOR_TRIGGER_A;
    echo_ = ULTRASONIC_SENSOR_ECHO_A;
  }
  else if(sensor == 'B') {
    trigger_ = ULTRASONIC_SENSOR_TRIGGER_B;
    echo_ = ULTRASONIC_SENSOR_ECHO_B;
  }
  else if(sensor == 'C') {
    _trigger = ULTRASONIC_SENSOR_TRIGGER_C;
    _echo = ULTRASONIC_SENSOR_ECHO_C;
  }
  else
    REPORT ERROR
}

// DEFINIR
//////////////////////////////////////
long UltrasonicSensor::measure(void) {
} 
//////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////
///////////// SINGLE MOTOR CLASS /////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void SingleMotor::SingleMotor(void) {
  REPORT ERROR
}  

void SingleMotor::SingleMotor(char motor) {
  if (motor == 'A') {
    pin1_ = MOTOR_PIN_1_A;
    pin2_ = MOTOR_PIN_2_A;
  }
  else if(motor == 'B') {
    pin1_ = MOTOR_PIN_1_B;
    pin2_ = MOTOR_PIN_2_B;
  }
  else {
    REPORT ERROR  
  }
  speed_ = MIN_SPEED;
}  

void SingleMotor::ValidateSpeed(int speed) {
  if (speed < MIN_SPEED || speed > MAX_SPEED) {
    REPORT ERROR
  }
}

void SingleMotor::SetSpeed(int speed, direction_t direction) {
  ValidateSpeed(speed);
  speed_ = speed;

  int pwm_duty;

  if (direction == FORWARD) {
    digitalWrite(pin1_, HIGH);
    pwm_duty = (MIN_PWM + _speed * (MAX_SPEED - MIN_PWM) / MAX_SPEED );
  }
  else {
    digitalWrite(pin1_, LOW);
    pwm_duty = ( MAX_SPEED - (MIN_PWM + _speed*(MAX_SPEED-MIN_PWM)/MAX_SPEED));
  }
  analogWrite(pin2_, pwm_duty);
}

void SingleMotor::HardStop(void) {
  digitalWrite(pin1_, HIGH);
  digitalWrite(pin2_, HIGH);
}

void SingleMotor::SoftStop(void) {
  digitalWrite(pin1_, LOW);
  digitalWrite(pin2_, LOW);
}


//////////////////////////////////////////////////////////////////////
///////////// COMPLETE MOTORS CLASS //////////////////////////////////
//////////////////////////////////////////////////////////////////////


void CompleteMotors::CompleteMotors(void): _motorLeft('A'), _motorRight('B') {
  _speed = MIN_SPEED;
}

void CompleteMotors::CompleteMotors(char motorLeft, char motorRight): _motorLeft(motorLeft), _motorRight(motorRight) {
  if(motor1==motor2) REPORT ERROR; 
  _speed = MIN_SPEED;
}

void CompleteMotors::setSpeed(int speed) {
  _speed = speed;
  _motorLeft.setSpeed(_speed);
  _motorRight.setSpeed(_speed);
}

void CompleteMotors::hardStop(void) {
  _motorLeft.hardStop();
  _motorRight.hardStop();
}

void CompleteMotors::softStop(void) {
  _motorLeft.softStop();
  _motorRight.softStop();
}

void forward(void) {
  _motorLeft.forward();
  _motorRight.forward();
}

void reverse(void) {
  _motorLeft.reverse();
  _motorRight.reverse();
}

void forwardRight(void) {
  _motorLeft.forward();
  _motorRight.softStop();
}

void forwardLeft(void) {
  _motorLeft.softStop();
  _motorRight.forward();
}

void turnRight(void) {
  _motorLeft.forward();
  _motorRight.reverse();
}

void turnLeft(void) {
  _motorLeft.reverse();
  _motorRight.forward();
}










