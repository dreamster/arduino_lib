/*
  Test code for Dreamduino maked in a hackathon
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
#define DISTANCE_ERROR=10;


long distance_A , mes1,mes2,mes3, prom,bminusc;
long distance_B;
long distance_C;

int DISTANCE_MED=50;
int RANGE=20,i; //histeresis


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
    bminusc=b_minus_c();
    if(abs(bminusc) <= DISTANCE_ERROR){
      motors_forward();
      delay(200); //miliseconds avanzando
    }
    abs_bminusc=abs()bminusc
    else if(abs_bminusc>DISTANCE_ERROR){
      while(abs(bminusc)>DISTANCE_ERROR){
        if(bminusc>0){
          motors_stop();
          turn_left(100);
          motors_forward();
          delay(200);
          turn_right(100);
          motors_forward();
          delay(200);
        }
        else if(bminusc<0){
          motors_stop();
          turn_right(100);
          motors_forward();
          delay(200);
          turn_left(100);
          motors_forward();
          delay(200);
        }
        bminusc=b_minus_c();  
      
      }
    }
    
    delayMicroseconds(10000);
  }
}



/*------------MEASUREs----------se que es capocha pero bueno...hackathon---*/ 
long b_minus_c(){
    distance_B=prom_measure_B();
    delay(60);
    distance_C=priom_measure_C();
    delay(60);
    return(distance_B-distance_C);
}

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

void turn_right(int miliseconds){
 motor_2_forward();
 motor_1_reverse();
 i=0
 while(i<miliseconds){
 delay(1);
 i++;
 }
 motors_stop();
}
void turn_left(int miliseconds){
 motor_1_forward();
 motor_2_reverse();
 i=0
 while(i<miliseconds){
 delay(1);
 i++;
 }
 motors_stop();
}

void motors_forward(){
  digitalWrite( MOTOR_1A, LOW );
  digitalWrite( MOTOR_1B, HIGH );
  digitalWrite( MOTOR_2A, LOW );
  digitalWrite( MOTOR_2B, HIGH );
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

void motors_stop(){
  digitalWrite( MOTOR_2A, HIGH );
  digitalWrite( MOTOR_2B, HIGH );
  digitalWrite( MOTOR_1A, HIGH );
  digitalWrite( MOTOR_1B, HIGH );
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
