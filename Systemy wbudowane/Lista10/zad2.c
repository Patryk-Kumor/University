#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // Phase and Frequency Correct PWM top=ICR1
  // częstotliwość 16e6/(256*(56)*2) = +- 558 Hz
  ICR1 = 56;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS12); // preskaler 256
  DDRB |= _BV(PB1);
  TIMSK1 |= _BV(TOIE1) | _BV(ICIE1); // interrupt
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // interrupt
}

uint8_t type;
uint16_t v1;
uint16_t v2;
uint16_t p;
// overflow - 
ISR(TIMER1_OVF_vect){
  type = 1;
  ADMUX = _BV(REFS0); // referencja AVcc, wejście ADC0 - Odczyt MOSFET
  ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC0
}
// capture -
ISR(TIMER1_CAPT_vect){
  type = 2;
  ADMUX = _BV(REFS0); // referencja AVcc, wejście ADC0 - Odczyt MOSFET
  ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC0
}
// adc
ISR(ADC_vect){
  if (type == 0){
    p = ADC;
    OCR1A = p / 18;
  }
  else if (type == 1){
    v1 = ADC;
    type = 0;
    ADMUX = _BV(REFS0) | _BV(MUX0); // referencja AVcc, wejście ADC1 - Potencjometr
    ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC1
  }
  else if (type == 2){
    v2 = ADC;
    type = 0;
    ADMUX = _BV(REFS0) | _BV(MUX0); // referencja AVcc, wejście ADC1 - Potencjometr
    ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC1
  }
}


FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj ADC
  adc_init();

  // uruchom licznik
  timer1_init();

  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();

  // (adc * (5000 / 1024)) = wynik w mV
  while(1) {
    //printf("pot: %"PRIu32" v1: %"PRIu32" v2: %"PRIu32"\r\n", (uint32_t)p, (uint32_t)v1, (uint32_t)v2 );
    printf("pot: %"PRIu32" v1: %"PRIu32" v2: %"PRIu32"\r\n", (uint32_t)p, (uint32_t)((float)v1 * (5000.0 / 1024.0)), (uint32_t)((float)v2 * (5000.0 / 1024.0)));
    sleep_mode();
  }
}
