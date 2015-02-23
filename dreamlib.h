#ifndef DREAMLIB-H
#define DREAMLIB-H

#include "Arduino.h"

// The UltrasonicSensor class allows you to instance an object with 1 of the 3 available Ultrasonic sensors of your Dreamduino, A, B or C. If noone is specified, or an invalid option is selected, sensor will be initialized as sensor A.
// The "measure" method which gives you the distance measured by the instanciated sensor, with a value between 0 and 20000. A return value of -1 means an error in the measurement.

class UltrasonicSensor
{
 public:
  UltrasonicSensor(void);
  UltrasonicSensor(char sensor);
//    int calibrate(void) // This function should calibrate the lowest and higest value a measurement can get
  long measure(void);    
 private:
  int trigger_;
  int echo_;
//    long _max_distance;
//    long _min_distance;    
}


// The SingleMotor class allows you to instanciate an object with 1 of the 2 available motors of your Dreamduino, A or B. If no motor is selected, or an invalid option is selected, the object will be initialized as motor A.
// It gives a low level control of the basic functions of a motor, being able to set it foward, reverse or stoping it. You can also set the speed with the method "setSpeed()", or directly when you set the motor forward or reverse.

typedef enum{FORWARD,REVERSE} direction_t;
#define MAX_SPEED 100
#define MIN_SPEED 0


class SingleMotor
{
 public:
  SingleMotor(void);
  SingleMotor(char motor);
  void SetSpeed(int speed, direction_t direction);
  void HardStop(void);
  void SoftStop(void);
 private:
  void ValidateSpeed(int speed);
  int pin1_;
  int pin2_;
  int speed_;
}

// The CompleteMotors class allows you to instanciate an object which includes both motors. If no arguments are given, or an invalid option is selected, the object will be initialized with motor A as the right one, and motor B as the left one.
// It gives high level control of the movement of your Dreamduino, being able to set it forward, turn while moving, turn in its place, move in reverse or stop. Control of both motors is done simultaneously, so there is no need to treat them on a low level code.

typedef enum{HARDSTOP, SOFTSTOP, FORWARD, REVERSE} singlemotor_t;

class CompleteMotors
{
 public:
  CompleteMotors(void);
  CompleteMotors(char motorLeft, char motorRight); 
  void setSpeed(int speed);  
  void hardStop(void);
  void softStop(void);
  void forward(void);
  void forward(int speed);
  void reverse(void);
  void reverse(int speed);
  void forwardRight(void)
  void forwardRight(int speed)
  void forwardLeft(void)  
  void forwardLeft(int speed)  
  void turnLeft(void)  
  void turnLeft(int speed)
  void turnRight(void)
  void turnRight(int speed)
 private:
  SingleMotor motorLeft_;
  SingleMotor motorRight_;
  int _speed;
  completeMotors_t
}











#endif
