#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1

  // ICR1  = 15624
  // częstotliwość 16e6/(256*(1+1249)) = +- 50 Hz
  // wzór: datasheet 20.12.3 str. 164

  ICR1 = 1249;
  OCR1A = 94; // środek servo -> 1.5 ms prądu w całych 20ms -> 7.5% z 20ms -> 94/1249 
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS12); // 256

  DDRB |= _BV(PB1);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}



int main()
{
  // uruchom licznik
  timer1_init(); 
  // konfiguracja adc
  adc_init();
  // działanie programu
  uint16_t temp = 0;
  while(1){
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    temp = ADC;
    // wypełnienie od 32 do 143
    // 32 + x * 1023 = 143 -> wolfram x = 37/341
    OCR1A = 32 + 37 * temp / 341;
    
  }
}
