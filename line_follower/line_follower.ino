/*
  29/MAR/2015
  Code for testing the ultrasonic sensor, H-bridge and motors in the 1rst version of the Dreamster board 
  Autor: Ignacio Carballeda <carballeda.ignacio@gmail.com>
*/

//functional connections
#define MOTOR_LP  5 //Left Positive
#define MOTOR_LN  6 //Left Negative
#define MOTOR_RP  9
#define MOTOR_RN 10
#define TRIGPIN_A A3
#define ECHOPIN_A 8
#define ROBOT_SPEED 30
#define DIST_MAX 10
#define DIF 10
#define ERR 20
const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
int measure_l,measure_r;
long distance;

void motors_stop();
void motor(char motor, char dir, int pwm); // char motor could be 'R' (right) or 'L' (left), dir could be 'F' or 'B' , PWM int 0 to 255

void setup()
{
	pinMode( MOTOR_RP, OUTPUT );
	pinMode( MOTOR_RN, OUTPUT );
	pinMode( MOTOR_LP, OUTPUT );
	pinMode( MOTOR_LN, OUTPUT );
	pinMode( TRIGPIN_A, OUTPUT );
	pinMode( ECHOPIN_A, INPUT );
}

void loop(){
	motors_stop();
	delay(1000);
	distance=distance_measure();
        measure_l=ir_measure('L');
        measure_r=ir_measure('R');
	while(true){
		distance=distance_measure();
                measure_l=ir_measure('L');
                measure_r=ir_measure('R');
		if(distance>=DIST_MAX){
                  if(measure_l < (measure_r + ERR)){ 
                    motor('R','B',ROBOT_SPEED + DIF);
		    motor('L','B',ROBOT_SPEED - DIF);
                  }
                  else if (measure_r < (measure_l + ERR)){
                    motor('R','B',ROBOT_SPEED - DIF);
		    motor('L','B',ROBOT_SPEED + DIF);
                  }
                  else {
                    motor('R','B',ROBOT_SPEED);
		    motor('L','B',ROBOT_SPEED);
                  }
                delay(10);
                }
                else if(distance<=DIST_MAX){
                  while(distance<=DIST_MAX){
                    motors_stop();
                    delay(1000);
                    distance=distance_measure();
                  }
                }
	
	}
}


/*------------MOTORS-------------*/ 

void motors_stop(){
	digitalWrite( MOTOR_RP, LOW );
	digitalWrite( MOTOR_RN, LOW); 
	digitalWrite( MOTOR_LP, LOW );
	digitalWrite( MOTOR_LN, LOW); 
}


void motor(char motor, char dir, int pwm){	//Entries of this function are motor (R or L), direction (F or B) and PWM (0 to 255)
	if(motor=='R'){
		if(dir=='F'){
			analogWrite( MOTOR_RP,  pwm);
			digitalWrite( MOTOR_RN, LOW);
		}
		else if(dir=='B'){
			analogWrite( MOTOR_RN,  pwm );
			digitalWrite( MOTOR_RP, LOW);
		}
	}
	else if(motor=='L'){
		if(dir=='F'){
			analogWrite( MOTOR_LP,  pwm);
			digitalWrite( MOTOR_LN, LOW); 
		}
		else if(dir=='B'){
			analogWrite( MOTOR_LN,  pwm);
			digitalWrite( MOTOR_LP, LOW); 
		}
	}
}



/*------------MEASURE-------------*/ 

long distance_measure() {
	long duration, distance;
	digitalWrite(TRIGPIN_A, LOW);  
	delayMicroseconds(2); 
	digitalWrite(TRIGPIN_A, HIGH);
	delayMicroseconds(10); 
	digitalWrite(TRIGPIN_A, LOW);
	duration = pulseIn(ECHOPIN_A, HIGH);
	distance = (duration/2) / 29.1;  
	if (distance >= 200 || distance <= 0){
		return 0;
	}
	else {
		return distance;    
	}
} 


int ir_measure(char SIDE){
  // read the analog in value:
  int outputValue=0;
  if(SIDE=='R'){
    outputValue = analogRead(analogInPin0);
    // map it to the range of the analog out:
    outputValue = map(outputValue, 0, 1023, 0, 255);
  }
  // read the analog in value:
  else if(SIDE=='L'){
    outputValue = analogRead(analogInPin1);
    // map it to the range of the analog out:
    outputValue = map(outputValue, 0, 1023, 0, 255);
  }
  return outputValue;
}


/*EOF*/




