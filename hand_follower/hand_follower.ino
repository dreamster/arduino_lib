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
#define ROBOT_SPEED 40


long distance;
int DISTANCE_MED=30; // distance from your hand to the robot
int RANGE=5;     //ciclo de histeresis


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
	distance=measure();
	while(true){
		distance=measure();
		if(distance>=DISTANCE_MED+RANGE){
			motor('R','F',ROBOT_SPEED);
			motor('L','F',ROBOT_SPEED);
		}
		else if(distance<=DISTANCE_MED-RANGE){
			motor('R','B',ROBOT_SPEED);
			motor('L','B',ROBOT_SPEED);
		}
		else if(distance<=DISTANCE_MED+RANGE || distance>=DISTANCE_MED-RANGE){
			motors_stop();
		}
	delay(90);
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

long measure() {
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


/*EOF*/
