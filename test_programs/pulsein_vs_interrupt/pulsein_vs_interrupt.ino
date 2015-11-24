#include <Dreamlib.h>

// serial config
const bool USAR_SERIAL = true;
const long SERIAL_BPS = 115200;
const int kTriggerPinC = A5;
const int kEchoPinC = 7;

volatile bool is_counting;

void setup() {
  // set inputs and outputs
  pinMode(kTriggerPinC, OUTPUT);
  pinMode(kEchoPinC, INPUT); 
  
  // start Serial and attach an interrupt to one of the ultrasonic sensor,
  // when the pin changes from HIGH to LOW (FALLING)
  Serial.begin(SERIAL_BPS);
  // note: on the Leonardo, only pins 0, 1, 2, 3, 7 have interrupts
  attachInterrupt(digitalPinToInterrupt(kEchoPinC), stop_counter, FALLING);
}

void loop() {
  unsigned long start;
  long pulse;
  long manual_pulse;
  
  // do a manual measure, using an interruption to detect when the pulse
  // has changed from HIGH to LOW, and use micros() to measure how long it
  // took
  digitalWrite(kTriggerPinC, HIGH);
  digitalWrite(kTriggerPinC, LOW);
  is_counting = true;
  start = micros();
  while(is_counting) {
    // wait
  }
  // this value has been determined empirically
  manual_pulse = (micros() - start) - 456;
  delay(1);
  
  // disable interrupts and perform a normal pulseIn without timeout
  noInterrupts();
  digitalWrite(kTriggerPinC, HIGH);
  digitalWrite(kTriggerPinC, LOW);
  pulse = pulseIn(kEchoPinC, HIGH);
  interrupts();
  delay(1);
  
  // log results
  debug("Interrupt: %.4li ", manual_pulse * 50L / 291L);
  debug("PulseIn: %.4li\n", pulse * 50L / 291L);
}

void stop_counter() {
  is_counting = false;
}