/*
Y no tengo internet.
*/

const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
const int ledR = 12;
const int ledG = 11;
const int ledB = 13;
const int motor_rp = 5;
const int motor_rn = 6;
const int motor_lp = 9;
const int motor_ln = 10;
int outputValue0 = 0; 
int outputValue1 = 0;
int ir_times, IR_times = 2000;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(motor_rp, OUTPUT);
  pinMode(motor_rn, OUTPUT);
  pinMode(motor_lp, OUTPUT);
  pinMode(motor_ln, OUTPUT);
}

void loop() {
  led_test();
  ir_times=IR_times;
  //while(ir_times>0){
  while(1){ 
    ir_test();
    //ir_times--;
  }
  
  motor_test();
  delay(1000);
  motors_stop();
}

void led_test(){
  digitalWrite(ledR,HIGH);
  delay(1000);
  digitalWrite(ledR,LOW);
  digitalWrite(ledG,HIGH);
  delay(1000);
  digitalWrite(ledG,LOW);
  digitalWrite(ledB,HIGH);
  delay(1000);
  digitalWrite(ledB,LOW);
  delay(1000);
}


void ir_test(){
  // read the analog in value:
  outputValue0 = analogRead(analogInPin0);
  // map it to the range of the analog out:
  outputValue0 = map(outputValue0, 0, 1023, 0, 255);
  // read the analog in value:
  outputValue1 = analogRead(analogInPin1);
  // map it to the range of the analog out:
  outputValue1 = map(outputValue1, 0, 1023, 0, 255);
  // print the results to the serial monitor:
  Serial.print("sensor0 = " );
  Serial.println(outputValue0);
  Serial.print("sensor1 = " );
  Serial.println(outputValue1);
  analogWrite(ledG,outputValue1);
  analogWrite(ledB,outputValue0);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}

void motor_test(){
 digitalWrite(motor_rp,LOW);
 analogWrite(motor_rn,20);
 delay(1000);
 analogWrite(motor_rn,40);
 delay(1000);
 analogWrite(motor_rn,100);
 delay(1000);
 analogWrite(motor_rn,200);
 delay(1000);
 motors_stop();
 digitalWrite(motor_rp,LOW);
 analogWrite(motor_rn,100);
 delay(2000);
 
 motors_stop();
 
 digitalWrite(motor_rp,HIGH);
 analogWrite(motor_rn,20);
 delay(1000);
 analogWrite(motor_rn,40);
 delay(1000);
 analogWrite(motor_rn,100);
 delay(1000);
 analogWrite(motor_rn,200);
 delay(1000);
 motors_stop();
 digitalWrite(motor_rp,HIGH);
 analogWrite(motor_rn,100);
 delay(2000);
 
 motors_stop();
 
 //sssssssssssssssss
 
 digitalWrite(motor_lp,LOW);
 analogWrite(motor_ln,20);
 delay(1000);
 analogWrite(motor_ln,40);
 delay(1000);
 analogWrite(motor_ln,100);
 delay(1000);
 analogWrite(motor_ln,200);
 delay(1000);
 motors_stop();
 digitalWrite(motor_lp,LOW);
 analogWrite(motor_ln,100);
 delay(2000);
 
 motors_stop();
 
 digitalWrite(motor_lp,HIGH);
 analogWrite(motor_ln,20);
 delay(1000);
 analogWrite(motor_ln,40);
 delay(1000);
 analogWrite(motor_ln,100);
 delay(1000);
 analogWrite(motor_ln,200);
 delay(1000);
 motors_stop();
 digitalWrite(motor_lp,HIGH);
 analogWrite(motor_ln,100);
 delay(2000);
 
 motors_stop();
 
 }
 
 void motors_stop(){
 digitalWrite(motor_rp,LOW);
 digitalWrite(motor_rn,LOW);
 digitalWrite(motor_lp,LOW);
 digitalWrite(motor_ln,LOW);
 }
