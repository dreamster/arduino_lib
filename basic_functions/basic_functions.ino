/*
  2015-03-31
  Set of basic functions for the Dreamster board V1.0
  Author: Ignacio Carballeda <carballeda.ignacio@gmail.com>
*/

// functional connections
const int kMotorRP = 9;
const int kMotorRN = 10;
const int kMotorLP = 5;  // Left Positive
const int kMotorLN = 6;  // Left Negative

const int kTrigPinA = A3;  // Trigger for the Ultrasonic Sensor
const int kEchoPinA = 8;   // Echo
const int kTrigPinB = A4;
const int kEchoPinB = 2;
const int kTrigPinC = A5;
const int kEchoPinC = 7;

const int kRSense = A1;  // Measures from the IR Sensors
const int kLSense = A0;


void setup() {
  pinMode(kMotorRP, OUTPUT);
  pinMode(kMotorRN, OUTPUT);
  pinMode(kMotorLP, OUTPUT);
  pinMode(kMotorLN, OUTPUT);
  
  pinMode(kTrigPinA, OUTPUT);
  pinMode(kEchoPinA, INPUT);
  
  pinMode(kTrigPinB, OUTPUT);
  pinMode(kEchoPinB, INPUT);
  
  pinMode(kTrigPinC, OUTPUT);
  pinMode(kEchoPinC, INPUT); 
}

void loop() {

}


/*------------MOTORS-------------*/ 

void motorsStop() {
  digitalWrite(kMotorRP, LOW);
  digitalWrite(kMotorRN, LOW); 
  digitalWrite(kMotorLP, LOW);
  digitalWrite(kMotorLN, LOW); 
}

void motorSet(char motor, char dir, int pwm) {
  // parameters
  //   motor: 'R' or 'L'
  //   dir (direction): 'F' or 'B'
  //   pwm: 0 to 255
  
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


/*------------ULTRASONIC SENSORS-------------*/ 

long ultrasonicSensorMeasure(char sensor) {
  // parameters
  //   sensor: 'A', 'B' or 'C'
  
  long duration, distance;
  float distance_factor = 29.1;
  
  if (sensor == 'A') {
    digitalWrite(kTrigPinA, LOW);  
    delayMicroseconds(2); 
    digitalWrite(kTrigPinA, HIGH);
    delayMicroseconds(10); 
    digitalWrite(kTrigPinA, LOW);
    duration = pulseIn(kEchoPinA, HIGH);
    distance = (duration / 2) / distance_factor;
  } else if (sensor == 'B') {
    digitalWrite(kTrigPinB, LOW);  
    delayMicroseconds(2); 
    digitalWrite(kTrigPinB, HIGH);
    delayMicroseconds(10); 
    digitalWrite(kTrigPinB, LOW);
    duration = pulseIn(kEchoPinB, HIGH);
    distance = (duration / 2) / distance_factor;   
  } else if (sensor == 'C') {
    digitalWrite(kTrigPinC, LOW);  
    delayMicroseconds(2); 
    digitalWrite(kTrigPinC, HIGH);
    delayMicroseconds(10); 
    digitalWrite(kTrigPinC, LOW);
    duration = pulseIn(kEchoPinC, HIGH);
    distance = (duration / 2) / distance_factor;   
  }
  
  if (distance >= 200 || distance <= 0) {
    return 0;
  } else {
    return distance;    
  }
} 


/*------------IR SENSORS-------------*/ 

int infraredSensorMeasure(char sensor) {
  // parameters
  //   sensor: 'R' or 'L'
  
  int ir_sensor_value = 0;
  
  if (sensor == 'R') {
    ir_sensor_value = analogRead(kRSense);
  } else if (sensor == 'L') {
    ir_sensor_value = analogRead(kLSense);    
  }
  
  // map it to the range of the analog out
  ir_sensor_value = map(ir_sensor_value, 0, 1023, 0, 255);
  
  return ir_sensor_value;
}


/*EOF*/