#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define DETEKTOR PB0
#define DIODA_IR PB1

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


void timer_init()
{
  ICR1 = 421; // do 37.9kHz
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer_init();
  // config wejścia wyjścia
  DDRB |= _BV(LED) | _BV(DIODA_IR);
  DDRB &= ~_BV(DETEKTOR);
  PORTB |= _BV(DETEKTOR);
  while (1) {
    // wypełnienie
    OCR1A = ICR1/8;
    // sprawdzanie stanu
    if (PINB & _BV(DETEKTOR)) {
      PORTB &= ~_BV(LED); // OFF
    }
    else {
      PORTB |= _BV(LED); // ON
    }
    // debug
    // printf("Odczytano: %"PRIu8"\r\n", PINB & _BV(DETEKTOR));
  }
/*
#define LED PB5
#define DETEKTOR PB0
#define DIODA_IR PB1
*/
}

