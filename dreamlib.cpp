//////////////////////////////////////////////////////////////////////
///////////// ULTRASONIC SENSOR CLASS ////////////////////////////////
//////////////////////////////////////////////////////////////////////

void UltrasonicSensor::UltrasonicSensor(void)
{
	_trigger = ULTRASONIC_SENSOR_TRIGGER_A;
	_echo = ULTRASONIC_SENSOR_ECHO_A;
}

void UltrasonicSensor::UltrasonicSensor(char sensor)
{
	if(sensor == 'B')
	{
		_trigger = ULTRASONIC_SENSOR_TRIGGER_B;
		_echo = ULTRASONIC_SENSOR_ECHO_B;
	}
	else if(sensor == 'C')
	{
		_trigger = ULTRASONIC_SENSOR_TRIGGER_C;
		_echo = ULTRASONIC_SENSOR_ECHO_C;
	}
	else
	{
		_trigger = ULTRASONIC_SENSOR_TRIGGER_A;
		_echo = ULTRASONIC_SENSOR_ECHO_A;
	}
}

// DEFINIR
//////////////////////////////////////
long UltrasonicSensor::measure(void)
{
}
//////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////
///////////// SINGLE MOTOR CLASS /////////////////////////////////////
//////////////////////////////////////////////////////////////////////


void SingleMotor::SingleMotor(void)
{
	_pin1 = MOTOR_PIN_1_A;
	_pin2 = MOTOR_PIN_2_A;
	_speed = 0;
}	

void SingleMotor::SingleMotor(char motor)
{
	if(motor == 'B')
	{
		_pin1 = MOTOR_PIN_1_B;
		_pin2 = MOTOR_PIN_2_B;
	}
	else
	{	
		_pin1 = MOTOR_PIN_1_A;
		_pin2 = MOTOR_PIN_2_A;
	}
	_speed = 0;
}	

void SingleMotor::setSpeed(int speed)
{
	if(speed >= 0) _speed=speed;
	else _speed=0;
}

void SingleMotor::hardStop(void)
{
	digitalWrite(_pin1, HIGH);
	digitalWrite(_pin2, HIGH);
}

void SingleMotor::softStop(void)
{
	digitalWrite(_pin1, LOW);
	digitalWrite(_pin2, LOW);
}

void SingleMotor::forward(void)
{
	digitalWrite(_pin1, HIGH);
	analogWrite(_pin2, _speed);
}

void SingleMotor::forward(int speed)
{
	setSpeed(speed);
	digitalWrite(_pin1, HIGH);
	analogWrite(_pin2, _speed);
}

void SingleMotor::reverse(void)
{
	digitalWrite(_pin1, LOW);
	analogWrite(_pin2, _speed);
}

void SingleMotor::reverse(int speed)
{
	setSpeed(speed);
	digitalWrite(_pin1, LOW);
	analogWrite(_pin2, _speed);
}


//////////////////////////////////////////////////////////////////////
///////////// COMPLETE MOTORS CLASS //////////////////////////////////
//////////////////////////////////////////////////////////////////////

void CompleteMotors::CompleteMotors(void)
{
	_motorLeft = SimpleMotor('A');
	_motorRight = SimpleMotor('B');
	_speed = 0;
}

void CompleteMotors::CompleteMotors(char motor1)
{
	if (motor1='A')
	{
		_motorLeft = SimpleMotor('A');
		_motorRight = SimpleMotor('B');
	}
	else
	{
		_motorLeft = SimpleMotor('B');
		_motorRight = SimpleMotor('A');
	}
	_speed = 0;
}

void CompleteMotors::setSpeed(int speed)
{
	if(speed >= 0) _speed=speed;
	else _speed=0;
	_motorLeft.setSpeed(_speed);
	_motorRight.setSpeed(_speed);
}

void CompleteMotors::hardStop(void)
{
	_motorLeft.hardStop();
	_motorRight.hardStop();
}

void CompleteMotors::softStop(void)
{
	_motorLeft.softStop();
	_motorRight.softStop();
}

void forward(void)
{
	_motorLeft.forward();
	_motorRight.forward();
}

void forward(int speed)
{
	setSpeed(speed);
	_motorLeft.forward();
	_motorRight.forward();
}

void reverse(void)
{
	_motorLeft.reverse();
	_motorRight.reverse();
}

void reverse(int speed)
{
	setSpeed(speed);
	_motorLeft.reverse();
	_motorRight.reverse();
}

void forwardRight(void)
{
	_motorLeft.forward();
	_motorRight.softStop();
}

void forwardRight(int speed)
{
	setSpeed(speed);
	_motorLeft.forward();
	_motorRight.softStop();
}

void forwardLeft(void)
{
	_motorLeft.softStop();
	_motorRight.forward();
}

void forwardLeft(int speed)
{
	setSpeed(speed);
	_motorLeft.softStop();
	_motorRight.forward();
}


void turnRight(void)
{
	_motorLeft.forward();
	_motorRight.reverse();
}

void turnRight(int speed)
{
	setSpeed(speed);
	_motorLeft.forward();
	_motorRight.reverse();
}

void turnLeft(void)
{
	_motorLeft.reverse();
	_motorRight.forward();
}

void turnLeft(int speed)
{
	setSpeed(speed);
	_motorLeft.reverse();
	_motorRight.forward();
}










