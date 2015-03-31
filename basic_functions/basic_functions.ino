/*
  31/MAR/2015
  Set of basic functions for the Dreamster board V1.0
  Autor: Ignacio Carballeda <carballeda.ignacio@gmail.com>
*/


//functional connections
#define MOTOR_LP  5	//Left Positive
#define MOTOR_LN  6	//Left Negative
#define MOTOR_RP  9
#define MOTOR_RN 10
#define TRIGPIN_A A3	//Triger for the Ultrasonic Sensor
#define ECHOPIN_A 8 	//Echo
#define TRIGPIN_B A4
#define ECHOPIN_B 2
#define TRIGPIN_C A5
#define ECHOPIN_C 7
#define RSENSE A1	//Measures from the IR Sensors
#define	LSENSE A0


int irSensorValue = 0;	//Value read from IR Sensor
long distance;		//Distance read from Ultrasonic Sensor


void motors_stop();
void motor(char motor, char dir, int pwm);
long us_measure(char sensor);
int ir_measure(char sensor);

void setup()
{
	pinMode( MOTOR_RP, OUTPUT );
	pinMode( MOTOR_RN, OUTPUT );
	pinMode( MOTOR_LP, OUTPUT );
	pinMode( MOTOR_LN, OUTPUT );
	pinMode( TRIGPIN_A, OUTPUT );
	pinMode( ECHOPIN_A, INPUT );
	pinMode( TRIGPIN_B, OUTPUT );
	pinMode( ECHOPIN_B, INPUT );
	pinMode( TRIGPIN_C, OUTPUT );
	pinMode( ECHOPIN_C, INPUT );
}

void loop(){

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



/*------------ULTRASONIC SENSORS-------------*/ 

long us_measure(char sensor) {		//this function recives one char ('A', 'B' or 'C') and return a long 
	long duration, distance;
	if(sensor=='A'){
		digitalWrite(TRIGPIN_A, LOW);  
		delayMicroseconds(2); 
		digitalWrite(TRIGPIN_A, HIGH);
		delayMicroseconds(10); 
		digitalWrite(TRIGPIN_A, LOW);
		duration = pulseIn(ECHOPIN_A, HIGH);
		distance = (duration/2) / 29.1;
	}
	else if(sensor=='B'){
		digitalWrite(TRIGPIN_B, LOW);  
		delayMicroseconds(2); 
		digitalWrite(TRIGPIN_B, HIGH);
		delayMicroseconds(10); 
		digitalWrite(TRIGPIN_B, LOW);
		duration = pulseIn(ECHOPIN_B, HIGH);
		distance = (duration/2) / 29.1;   
	}
	else if(sensor=='C'){
		digitalWrite(TRIGPIN_C, LOW);  
		delayMicroseconds(2); 
		digitalWrite(TRIGPIN_C, HIGH);
		delayMicroseconds(10); 
		digitalWrite(TRIGPIN_C, LOW);
		duration = pulseIn(ECHOPIN_C, HIGH);
		distance = (duration/2) / 29.1;   
	}
	
	if (distance >= 200 || distance <= 0){
		return 0;
	}
	else {
		return distance;    
	}
} 

/*------------IR SENSORS-------------*/ 

int ir_measure(char sensor){ //sensor is 'L' or 'R'
	if(sensor=='R'){
		irSensorValue = analogRead(RSENSE);
	}
	else if(sensor=='L'){
		irSensorValue = analogRead(LSENSE);		
	}
	irSensorValue = map(irSensorValue, 0, 1023, 0, 255);  // map it to the range of the analog out
	return irSensorValue;
}


/*EOF*/
