/*
########### dreamsterbot.org ###########

 This is an example of a basic Dreamsterbot code. 
 It avoids obstacles using 3 sensors. 
 Also changes the led intesity acording to the distance sensed.
   */

const int TriggerPinA = A3;
const int EchoPinA = 8;
const int TriggerPinB = A4;
const int EchoPinB = 2;
const int TriggerPinC = A5;
const int EchoPinC = 7;
// A= adelenate
int DistanceA_mm;
int DistanceB_mm;
int DistanceC_mm;
const int ledA = 13;
const int ledR = 12;
const int ledV = 11;
int outA;
int outB;
int outC;

// IN1 = P  / IN2 = L
int kMotorLP = 5;
int kMotorLN = 6;
int kMotorRP = 9;
int kMotorRN = 10;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledV,OUTPUT);
  pinMode(TriggerPinA, OUTPUT);
  pinMode(EchoPinA, INPUT);
  pinMode(TriggerPinB, OUTPUT);
  pinMode(EchoPinB, INPUT);
  pinMode(TriggerPinC, OUTPUT);
  pinMode(EchoPinC, INPUT);
  Serial.begin(9600);
 
 digitalWrite(ledA,LOW);
 digitalWrite(ledR,LOW);
 digitalWrite(ledV,LOW);
 
  digitalWrite(kMotorLP, LOW);
 digitalWrite(kMotorLN, LOW);
 digitalWrite(kMotorRP, LOW);
 digitalWrite(kMotorRN, LOW);
}

   int  readSensor(int trigger, int echo)
 {
   int duration;
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   duration = pulseIn(echo, HIGH);
   if (duration < 0) duration = 0;
   return ((duration / 2.9) / 2);
 }
 
void loop() {
  
 DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
 DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
 DistanceC_mm = readSensor(TriggerPinC, EchoPinC);
 
  outA = map(DistanceA_mm, 0, 1023, 120, 255);
  analogWrite(ledR, outA);
  outB = map(DistanceB_mm, 0, 1023, 0, 255);
  analogWrite(ledA, outB);
  outC = map(DistanceC_mm, 0, 1023, 0, 255);
  analogWrite(ledV, outC);

  Serial.print("DistanceA = ");
  Serial.print(DistanceA_mm);
  Serial.print (" mm // ");
  Serial.println (outA, DEC);

  Serial.print("DistanceB = ");
  Serial.print(DistanceB_mm);
  Serial.print (" mm // ");
  Serial.println (outB, DEC);

  Serial.print("DistanceC = ");
  Serial.print(DistanceC_mm);
  Serial.print (" mm // ");
  Serial.println (outB, DEC);

   if (DistanceA_mm < 200 && DistanceB_mm < 200) {
     while(DistanceA_mm<200){ 
      analogWrite(kMotorLP, 20); 
      analogWrite(kMotorLN, 60); 
      analogWrite(kMotorRP, 60); 
      analogWrite(kMotorRN, 20);
      DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
      DistanceB_mm = readSensor(TriggerPinB, EchoPinB);
      }
    delay(200);
   }
 
 
   if (DistanceA_mm < 200 && DistanceC_mm < 200) {
     while(DistanceA_mm<200){ 
     analogWrite(kMotorLP, 60); 
     analogWrite(kMotorLN, 20); 
     analogWrite(kMotorRP, 20); 
     analogWrite(kMotorRN, 60);
     DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
     DistanceC_mm = readSensor(TriggerPinB, EchoPinB);
     delay(200);
   }
   }
 
   while(DistanceA_mm <200){ 
     analogWrite(kMotorLP, 60); 
    analogWrite(kMotorLN, 20); 
    analogWrite(kMotorRP, 20); 
    analogWrite(kMotorRN, 60);
    DistanceA_mm = readSensor(TriggerPinA, EchoPinA);
    delay(200);
   }
 
  analogWrite(kMotorLP, 80); 
  analogWrite(kMotorLN, 0); 
  analogWrite(kMotorRP, 80); 
  analogWrite(kMotorRN, 0);
  delay(200);
}
  
   

