#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}



// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

// inicjalizacja wejścia wyjścia
void io_init()
{
  // ustaw pull-up na PD2 (INT0 )
  PORTD |= _BV(PORTD2);
  // ustaw wyzwalanie przerwania na INT0 zboczem narastającym
  EICRA |= _BV(ISC00) | _BV(ISC01);
  // odmaskuj przerwania dla INT0
  EIMSK |= _BV(INT0);
  // AUTO ADC_vect
  ADCSRA |= _BV(ADIE);
}

FILE uart_file;

volatile uint16_t val = 0;
volatile uint16_t voltage = 0;
volatile uint32_t res = 0;
volatile float x = 0.0;

// obsługa przerwań buttona
ISR(INT0_vect) {
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
}

// obsługa przerwań ukończonej konwersji 
ISR(ADC_vect) {
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    val = ADC; // weź zmierzoną wartość (0..1023)
    voltage = val;
    x = (float)val / 1024.0 * 5.0;
    voltage = (uint16_t) (x*1000);
    res = (uint32_t)(10000.0 * ((5.0 / x) - 1.0));
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj adc
  adc_init();
  // zainicjalizuj wejścia/wyjścia
  io_init();
  // odmaskuj przerwania
  sei();
  // program testowy
  while(1) {
    printf("adc: %"PRIu16", voltage: %"PRIu16" mv, rezystancja: %"PRIu32" ohms\r\n\r\n", val, voltage, res);
    _delay_ms(1000);
 }
}

