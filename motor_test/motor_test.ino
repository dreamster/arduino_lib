/*
  29/MAR/2015
  Code for testing the H-bridge and motors in the 1rst version of the Dreamster board 
  Autor: Ignacio Carballeda <carballeda.ignacio@gmail.com>
*/

// functional connections
#define MOTOR_LP  5 //pin Left Positive
#define MOTOR_LN  6 //pin Left Negative
#define MOTOR_RP  9 //pin Right Positive
#define MOTOR_RN 10 //pin Right Negative

void motors_stop();
void motor(char motor, char dir, int pwm); // motor could be 'R' or 'L', dir could be 'F' or 'B' , PWM int 0 to 255 (max speed)

void setup()
{
	pinMode( MOTOR_RP, OUTPUT );
	pinMode( MOTOR_RN, OUTPUT );
	pinMode( MOTOR_LP, OUTPUT );
	pinMode( MOTOR_LN, OUTPUT );
}

void loop(){
	motor('R','F',50); 		//testing Right motor at diferent speeds
	delay(2000);
	motor('R','F',100);		//increase speed
	delay(2000);
	motor('R','F',200);
	delay(2000);
	motors_stop();
	delay(1000);

	motor('R','B',50);
	delay(2000);
	motor('R','B',100);
	delay(2000);
	motor('R','B',200);
	delay(2000);
	motors_stop();
	delay(1000);


	motor('L','F',50);		//testing left motor at diferent speeds
	delay(2000);
	motor('L','F',100);
	delay(2000);
	motor('L','F',200);
	delay(2000);
	motors_stop();
	delay(1000);

	motor('L','B',50);
	delay(2000);
	motor('L','B',100);
	delay(2000);
	motor('L','B',200);
	delay(2000);
	motors_stop();
	delay(1000);

}


void motors_stop(){				//this function stop both motors
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


/*EOF*/
