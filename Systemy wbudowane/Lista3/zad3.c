#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

int main()
{
  // zainicjalizuj ADC
  adc_init();
  // dioda
  LED_DDR |= _BV(LED);
  // tablica wartosci:
  uint8_t arr[] = {0,0,0,0,0,0,1,1,1,1,2,2,2,3,3,4,4,5,5,6,6,7,8,8,9,10,11,11,12,13,14,15,16,17,18,19,20,21,23,24,25,26,28,29,30,32,33,35,36,38,39,41,42,44,46,47,49,51,53,54,56,57,58,59,60};
  // mierz napięcie
  uint16_t my_delay;
  uint16_t v;
  uint32_t i;
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    v = ADC; // weź zmierzoną wartość (0..1023)
    my_delay = arr[v >> 4];
    // DIODA
    LED_PORT |= _BV(LED);  // ZAPALENIE
    for (i = 0; i < my_delay; i++) { _delay_us(1); }
    LED_PORT &= ~_BV(LED); // ZGASZENIE
  }
}

