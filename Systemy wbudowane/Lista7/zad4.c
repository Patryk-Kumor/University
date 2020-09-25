#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define MISO PD7
#define MOSI PD6
#define SS PD5
#define SCK PD4

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

// inicjalizacja SPI
void spi_init()
{
    // MISO jako wyjście
    // MOSI, SCK, ~SS na wejście
    DDRB |= _BV(PB4);

    // włącz SPI w trybie slave z zegarem 250kH
    SPCR = _BV(SPE);
}

uint8_t send(uint8_t to_send) // send and rec
{
  uint8_t rec = 0;

  // SS NA HIGH
  PORTD &= ~_BV(PD5);
  for (uint8_t i = 0; i < 8; i++) {    
    // JEŚLI BIT ZAPALONY  - SET MOSI
    if (to_send & 0x80) {
      // ZAPAL LINIĘ - HIGH
      PORTD |= _BV(PD6);
    }
    else {
      // WPP ZGAŚ - LOW
      PORTD &= ~_BV(PD6);
    }
    // SCK HI
    PORTD |= _BV(PD4);

    // MISO    
    if(PIND & _BV(PD7)) // Capture MISO
     rec |= _BV(7-i);
    else
     rec &= ~_BV(7-i);

    // SCK LO
    PORTD &= ~_BV(PD4);
    // KOLEJNY BIT
    to_send <<= 1;
  }
  // SS NA HIGH
  PORTD |= _BV(PD5);

  return rec;
}

int main()
{
// MISO   podłączone do   PD7  :  PB4 <--> PD7
// MOSI   podłączone do   PD6  :  PB3 <--> PD6
// SS     podłączone do   PD5  :  PB2 <--> PD5
// SCK    podłączone do   PD4  :  PB5 <--> PD4

  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj SPI
  spi_init();

  // ~SS, MOSI, SCK
  DDRD |= _BV(PD5) | _BV(PD6) | _BV(PD4);

  uint8_t to_send = 0;
  while (1) {
	  uint8_t to_send_original = to_send;
          // SEND SPI
	  uint8_t rec = send(to_send);
	  /* // READ SPI
	  while (!(SPSR & _BV(SPIF)));
	  SPSR |= _BV(SPIF);
	  uint8_t rec = SPDR;
          */
	  printf("\r\nWysłano: %"PRId8", odczytano: %"PRId8"\r\n", to_send_original, rec);
          to_send++;
          _delay_ms(500);
  }
}

