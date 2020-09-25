#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
  // PRZERWANIA rx, tx, udre
  UCSR0B |= _BV(RXCIE0);
  UCSR0B |= _BV(TXCIE0);
  UCSR0B |= _BV(UDRIE0);
}

volatile char buff[20] = {};
volatile uint8_t i = 0;
volatile uint8_t j = 0;
volatile uint8_t s = 0;

volatile char buff2[20] = {};
volatile uint8_t i2 = 0;
volatile uint8_t j2 = 0;
volatile uint8_t s2 = 0;

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) 
{
  // buffor pełny
  if (s == 20) {  
    while(!(UCSR0A & _BV(UDRE0)));
  }
  // wyłączenie przerwań udre
  UCSR0B &= ~_BV(UDRIE0);  
  //zapisujemy kolejny char do wysłania w bufforze;
  buff[i] = data;
  i++;
  s++;
  if (i == 20) { i = 0; }
  // ponowne włączenie przerwań
  UCSR0B |= _BV(UDRIE0);
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  if (s2 == 0) {
    while(!(UCSR0A & _BV(RXC0)));
  }   
  int temp = i2;
  i2++;
  s2--;
  if (i2==20) { i2=0; }
  return buff2[temp];  
}

// Przerwanie wykona się kiedy zostają odebrane dane USART // odebrano char
ISR(USART_RX_vect) { 
  if (s2> 0) {
    buff2[j2] = UDR0;
    j2++;
    if(j2==20) {j2=0;}
    s2++;
  }
}

// Przerwanie wykona się kiedy UART kończy wysyłać dane // wysłano char
ISR(USART_TX_vect) { 
}

// Przerwanie opróźnienia rejestru danych USART // wykonuje się kiedy rejestr UART jest pusty
ISR(USART_UDRE_vect) { 
  if (s > 0) {
    UDR0 = buff[j];
    j++; s--;
    if (j == 20) { j = 0; } 
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

  // odmaskowanie przerwań
  sei();

  printf("Hello world!\r\n");
  printf("Another hello world!\r\n");
  printf("Hello world again!\r\n");
  printf("Hello Azeroth!\r\n");
  printf("Hello Middle-earth!\r\n\n");

  _delay_ms(10);

  //char c;
  //scanf("%c", &c);  //_delay_ms(10);
  //printf("Odczytano char: %c \r\n", c);  //_delay_ms(10);
  //int16_t a;
  //scanf("%"SCNd16, &a);  //_delay_ms(10);
  //printf("Odczytano int: %"PRId16"\r\n", a);  //_delay_ms(10);

  while(1) {
    int16_t a = 1;
    scanf("%"SCNd16, &a);
    printf("Odczytano: %"PRId16"\r\n", a);
  }
}

