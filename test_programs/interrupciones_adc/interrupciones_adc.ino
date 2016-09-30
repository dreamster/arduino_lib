char debug_string_buffer[30];
#define debug(formato, valor) \
  sprintf(debug_string_buffer, formato, valor); \
  Serial.print(debug_string_buffer)

// serial config
const bool USAR_SERIAL = true;
const long SERIAL_BPS = 250000;

const int CANTIDAD_DE_SENSORES = 2;
int sensores[CANTIDAD_DE_SENSORES] = {};
byte canalesADC[CANTIDAD_DE_SENSORES] = {A1, A0};
volatile byte indiceConversion = 0;

volatile int contadorConversionesAD = 0; // para debug

void setup() {
  if (USAR_SERIAL) {
    Serial.begin(SERIAL_BPS);
  }  
  iniciarConversiones();
}

void loop() {
  contadorConversionesAD = 0;
  unsigned long timeStart = micros();
  delay(1000); // durante este tiempo se hacen las conversiones AD
  unsigned int timeEnd = round((micros() - timeStart) / 1000.0);
  debug("%4d ", contadorConversionesAD);
  debug("%4d ", sensores[0]);
  debug("%4d ", sensores[1]);
  debug("%4ums\n", timeEnd);
}

inline void iniciarConversiones() {
  byte pin;
  for (byte i = 0; i < CANTIDAD_DE_SENSORES; i++) {
    pin = canalesADC[i];
    // Arduino pin conversion
    #if defined(__AVR_ATmega32U4__)
      if (pin >= 18) pin -= 18; // allow for channel or pin numbers
      pin = analogPinToChannel(pin);
    #else
      if (pin >= 14) pin -= 14; // allow for channel or pin numbers
    #endif
    canalesADC[i] = pin;
  }  
  pin = canalesADC[indiceConversion];
  
  #if defined(ADCSRB) && defined(MUX5)
    // the MUX5 bit of ADCSRB selects whether we're reading from channels
    // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
    ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
  #endif

  // when ADLAR is low, ADCL must be read first, otherwise, reading ADCH is
  // enough (if 8 bits are sufficient)
  ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (pin & 0x07);

  // interrupt enable, start the conversion
  ADCSRA |= (1 << ADIE) | (1 << ADSC);
}


ISR(ADC_vect) {
  contadorConversionesAD++; // para debug
  
  sensores[indiceConversion] = ADC;
  if (++indiceConversion == CANTIDAD_DE_SENSORES) {
    indiceConversion = 0;
  }
  
  byte pin = canalesADC[indiceConversion];
  ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (pin & 0x07);
  ADCSRA |= _BV(ADSC); // Start next conversion  
}
