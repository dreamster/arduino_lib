/*
  Test code for Dreamduino
*/
// wired connections

#define ECHOPIN_C 1
#define ECHOPIN_B 2 
#define TRIGPIN_A 3
#define TRIGPIN_B 11
#define ECHOPIN_A 12
#define TRIGPIN_C 13

// functional connections
#define MOTOR_1A 6
#define MOTOR_1B 7
#define MOTOR_2A 4
#define MOTOR_2B 5


long distance_A , mes1,mes2,mes3, prom;
long distance_B;
long distance_C;

int DISTANCE_MED=50;
int RANGE=20; //histeresis


void setup()
{
  pinMode( MOTOR_1B, OUTPUT );
  pinMode( MOTOR_2B, OUTPUT );
  pinMode( MOTOR_1A, OUTPUT );
  pinMode( MOTOR_1B, OUTPUT );
  pinMode( TRIGPIN_A, OUTPUT );
  pinMode( ECHOPIN_A, INPUT );
  pinMode( TRIGPIN_B, OUTPUT );
  pinMode( ECHOPIN_B, INPUT );
  pinMode( TRIGPIN_C, OUTPUT );
  pinMode( ECHOPIN_C, INPUT );
}


void loop(){
  while(true){
    distance_A=prom_measure_A();
    if(distance_A>=DISTANCE_MED+RANGE){
     motors_reverse();
    }
    else if(distance_A<=DISTANCE_MED-RANGE){
      motors_forward();
    }
    else if(distance_A<=DISTANCE_MED+RANGE || distance_A>=DISTANCE_MED-RANGE){
      motors_softstop();
    }
    delayMicroseconds(10000);
  }
}



/*------------MEASUREs----------se que es capocha pero bueno...hackathon---*/ 

long prom_measure_A(){
  mes1=measure_A();
  delayMicroseconds(60000);
  mes2=measure_A();
  delayMicroseconds(60000);
  mes3=measure_A();
  prom=(mes1+mes2+mes3)/3;
  return prom;
}

long prom_measure_B(){
  mes1=measure_B();
  delayMicroseconds(60000);
  mes2=measure_B();
  delayMicroseconds(60000);
  mes3=measure_B();
  prom=(mes1+mes2+mes3)/3;
  return prom;
}

long prom_measure_C(){
  mes1=measure_C();
  delayMicroseconds(60000);
  mes2=measure_C();
  delayMicroseconds(60000);
  mes3=measure_C();
  prom=(mes1+mes2+mes3)/3;
  return prom;
}

long measure_A() {
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

long measure_B() {
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
long measure_C() {
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

/*--------------MOTORES 1 Y 2-------------------*/

void motors_forward(){
  digitalWrite( MOTOR_1A, LOW );
  digitalWrite( MOTOR_1B, HIGH );
  
  digitalWrite( MOTOR_2A, LOW );
  analogWrite( MOTOR_2B, HIGH );
}

void motors_reverse(){
 digitalWrite( MOTOR_1A, HIGH );
 digitalWrite( MOTOR_1B, LOW );
 digitalWrite( MOTOR_1A, HIGH );
 digitalWrite( MOTOR_1B, LOW ); 
}

void motors_softstop(){
  digitalWrite( MOTOR_2A, LOW );
  digitalWrite( MOTOR_2B, LOW );
  digitalWrite( MOTOR_1A, LOW );
  digitalWrite( MOTOR_1B, LOW );
}

/*-----------motor1------------*/

void motor_1_forward(){
  digitalWrite( MOTOR_1A, LOW );
  digitalWrite( MOTOR_1B, HIGH );
}

void motor_1_reverse(){
 digitalWrite( MOTOR_1A, HIGH );
 digitalWrite( MOTOR_1B, LOW ); 
}

void motor_1_softstop(){
  digitalWrite( MOTOR_1A, LOW );
  digitalWrite( MOTOR_1B, LOW );
}

/*----------motor2------------*/

void motor_2_forward(){
  digitalWrite( MOTOR_2A, LOW );
  digitalWrite( MOTOR_2B, HIGH );
  
}

void motor_2_reverse(){
 digitalWrite( MOTOR_2A, HIGH );
 digitalWrite( MOTOR_2B, LOW ); 
}

void motor_2_softstop(){
  digitalWrite( MOTOR_2A, LOW );
  digitalWrite( MOTOR_2B, LOW );
}


/*EOF*/
