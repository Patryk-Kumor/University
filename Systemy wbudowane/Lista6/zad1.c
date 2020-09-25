#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

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

  // PRZERWANIA
  UCSR0B |= _BV(RXCIE0);

  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// Przerwanie wykona się kiedy zostają odebrane dane USART // odebrano char
ISR(USART_RX_vect) {  
  // UDR0 = UDR0;
  // odbiór
  char c = UDR0; 
  // wysłanie
  UDR0 = c;
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);
  // odmaskowanie przerwań
  sei();
  while (1) {
    sleep_mode();
  }
}

