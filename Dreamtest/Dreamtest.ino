/*
  Test code for Dreamster
*/
// wired connections

#define ECHOPIN_C 1
#define ECHOPIN_B 2 
#define TRIGPIN_A 3
#define TRIGPIN_B 11
#define ECHOPIN_A 12
#define TRIGPIN_C 13

// functional connections
#define MOTOR_1A 6// Motor B PWM Speed
#define MOTOR_1B 7// Motor B Direction

#define MOTOR_2A 4// Motor A PWM Speed
#define MOTOR_2B 5// Motor A Direction


long distance;
int DISTANCE_MED=50;
int RANGE=20; //ciclo de histeresis

long measure();
void motors_forward();
void motors_reverse();
void motors_softstop();


void setup()
{
  Serial.begin (9600);
  pinMode( MOTOR_1B, OUTPUT );
  pinMode( MOTOR_2B, OUTPUT );
  pinMode( MOTOR_1A, OUTPUT );
  pinMode( MOTOR_1B, OUTPUT );
  pinMode( TRIGPIN_A, OUTPUT );
  pinMode( ECHOPIN_A, INPUT );
}


void loop(){
motors_stop();
delay(1000);
motors_forward();
delay(3000);
    distance=measure();
  while(true){
    distance=measure();
    //Serial.println(distance);
    if(distance>=DISTANCE_MED+RANGE){
     motors_reverse();
 //    Serial.println("reversa");
    }
    else if(distance<=DISTANCE_MED-RANGE){
     // motors_forward();
   //   Serial.println("adelante");
    }
    else if(distance<=DISTANCE_MED+RANGE||distance>=DISTANCE_MED-RANGE){
      motors_stop();
     // Serial.println("detenido");
    }
    delay(90);
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

/*--------------MOTORES A Y B-------------------*/

void motors_reverse(){
 digitalWrite( MOTOR_1A, HIGH );
 digitalWrite( MOTOR_1B, LOW );
 digitalWrite( MOTOR_2A, HIGH );
 digitalWrite( MOTOR_2B, LOW );
  
}

void motors_forward(){

 digitalWrite( MOTOR_2A, LOW );
 digitalWrite( MOTOR_2B, HIGH );
 digitalWrite( MOTOR_1A, LOW );
 digitalWrite( MOTOR_1B, HIGH ); 
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


/*EOF*/
