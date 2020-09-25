#include <avr/io.h>
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

void timer1_init()
{
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
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
  timer1_init();

  volatile int8_t a8 = 0; volatile int8_t b8 = 1; volatile int8_t sum8 = 0; volatile int8_t prod8 = 0; volatile int8_t frac8 ;
  volatile int16_t a16 = 0; volatile int16_t b16 = 1; volatile int16_t sum16 = 0; volatile int16_t prod16 = 0; volatile int16_t frac16 = 0;
  volatile int32_t a32 = 0; volatile int32_t b32 = 1; volatile int32_t sum32 = 0; volatile int32_t prod32 = 0; volatile int32_t frac32 = 0;
  volatile int64_t a64 = 0; volatile int64_t b64 = 1; volatile int64_t sum64 = 0; volatile int64_t prod64 = 0; volatile int64_t frac64 = 0;
  volatile float af = 0; volatile float bf = 1; volatile float sumf = 0; volatile float prodf = 0; volatile float fracf = 0;
  uint16_t a = TCNT1; uint16_t b = TCNT1; 


  // int8_t
  printf("Podaj dwie liczby int8!\r\n");
  scanf("%" SCNd8, &a8); scanf("%" SCNd8, &b8);
  printf("Podane liczby: a = %"PRId8", b = %"PRId8"\r\n", a8, b8);   
  a = TCNT1; 
  // dodawanie int8
  sum8 = a8 + b8;
  b = TCNT1;
  printf("-dodawanie = %"PRId8"\r\n czas w cyklach = %"PRId16"\r\n", sum8, b - a);
  a = TCNT1;
  // mnozenie int8
  prod8 = a8 * b8;
  b = TCNT1;
  printf("-mnozenie = %"PRId8"\r\n czas w cyklach = %"PRId16"\r\n", prod8, b - a);
  a = TCNT1;
  // dzielenie int8
  frac8 = a8 / b8;
  b = TCNT1;
  printf("-dzielenie = %"PRId8"\r\n czas w cyklach = %"PRId16"\r\n", frac8, b - a);


  // int16_t
  printf("\r\nPodaj dwie liczby int16!\r\n");
  scanf("%" SCNd16, &a16); scanf("%" SCNd16, &b16);
  printf("Podane liczby: a = %"PRId16", b = %"PRId16"\r\n", a16, b16);              
  a = TCNT1; 
  // dodawanie int16
  sum16 = a16 + b16;
  b = TCNT1;
  printf("-dodawanie = %"PRId16"\r\n czas w cyklach = %"PRId16"\r\n", sum16, b - a);
  a = TCNT1;
  // mnozenie int16
  prod16 = a16 * b16;
  b = TCNT1;
  printf("-mnozenie = %"PRId16"\r\n czas w cyklach = %"PRId16"\r\n", prod16, b - a);
  a = TCNT1;
  // dzielenie int16
  frac16 = a16 / b16;
  b = TCNT1;
  printf("-dzielenie = %"PRId16"\r\n czas w cyklach = %"PRId16"\r\n", frac16, b - a);


  // int32_t
  printf("\r\nPodaj dwie liczby int32!\r\n");
  scanf("%" SCNd32, &a32); scanf("%" SCNd32, &b32);
  printf("Podane liczby: a = %"PRId32", b = %"PRId32"\r\n", a32, b32);         
  a = TCNT1; 
  // dodawanie int16
  sum32 = a32 + b32;
  b = TCNT1;
  printf("-dodawanie = %"PRId32"\r\n czas w cyklach = %"PRId16"\r\n", sum32, b - a);
  a = TCNT1;
  // mnozenie int16
  prod32 = a32 * b32;
  b = TCNT1;
  printf("-mnozenie = %"PRId32"\r\n czas w cyklach = %"PRId16"\r\n", prod32, b - a);
  a = TCNT1;
  // dzielenie int16
  frac32 = a32 / b32;
  b = TCNT1;
  printf("-dzielenie = %"PRId32"\r\n czas w cyklach = %"PRId16"\r\n", frac32, b - a);


  // int64_t
  printf("\r\nPodaj dwie liczby int64! \r\n");
  scanf("%" SCNd32, &a32); scanf("%" SCNd32, &b32);
  printf("Podane liczby: a = %"PRId32", b = %"PRId32"\r\n", a32, b32); 
  // konwersja na int64
  a64 = (uint64_t) a32; b64 = (uint64_t) b32; 
  a = TCNT1; 
  // dodawanie int64
  sum64 = a64 + b64;
  b = TCNT1;
  printf("-dodawanie = int64 \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  a = TCNT1;
  // mnozenie int64
  prod64 = a64 * b64;
  b = TCNT1;
  printf("-mnozenie = int64 \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  a = TCNT1;
  // dzielenie int64
  frac64 = a64 / b64;
  b = TCNT1;
  printf("-dzielenie = int64 \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  // do warningów
  sum64++; prod64++; frac64++;


  // float
  printf("\r\nPodaj (not rly) dwie liczby float!\r\n");
  af = 123.231; bf = 12.54;
  printf("Podane liczby: a = 123.231, b = 12.54\r\n"); 
  a = TCNT1; 
  // dodawanie float
  sumf = af + bf;
  b = TCNT1;
  printf("-dodawanie = float \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  a = TCNT1;
  // mnozenie float
  prodf = af * bf;
  b = TCNT1;
  printf("-mnozenie = float \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  a = TCNT1;
  // dzielenie float
  fracf = af / bf;
  b = TCNT1;
  printf("-dzielenie = float \r\n czas w cyklach = %"PRId16"\r\n", b - a);
  // do warningów
  sumf++; prodf++; fracf++;
}

