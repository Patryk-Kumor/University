#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
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



FILE uart_file;



// inicjalizacja licznika 1
void timer1_init()
{
  // WGM1  = 0000 -- tryb normal
  // prescaler 1
  TCCR1B = _BV(CS10);
  // odmaskowanie przerwania input capture
  TIMSK1 |= _BV(ICIE1); 
}

// inicjalizacja licznika 2
void timer2_init()
{
  // WGM1  = 0000 -- tryb normal
  // preskaler 1024
  TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
  // odmaskowanie przerwania przepełnienia licznika
  TIMSK2 |= _BV(TOIE2);
}

volatile uint32_t i = 0;
volatile uint8_t c = 0;

// procedura obsługi przerwania input capture counter1
ISR(TIMER1_CAPT_vect) {
  i++;
}

// procedura obsługi przerwania przepełnienia licznika counter2
// interrupt frequency (Hz) = (Arduino clock speed 16,000,000Hz) / (prescaler * (compare match register + 1))
// -- odpala się raz na 16.66us => sekunda jest odliczana co 60interr.
// 1000 / 16.66 = +-60
ISR(TIMER2_OVF_vect) {
  c++;
  if (c == 60) {
    printf("%"PRIu32"\r\n", i );
    i = 0; c = 0;
  }
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj 
  timer1_init();
  timer2_init();

  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);
  // odmaskuj przerwania
  sei();
  // pętla uśpienia
  while(1) {
    sleep_mode();
  }
}

