#include <avr/io.h>
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

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // int8_t
  printf("Podaj dwie liczby int8!\r\n");
  int8_t a8 = 1; int8_t b8 = 1;
  scanf("%" SCNd8, &a8);
  scanf("%" SCNd8, &b8);
  printf("Podane liczby: a = %"PRId8", b = %"PRId8"\r\n", a8, b8);
  printf("dodawanie = %"PRId8"\r\n", a8 + b8);
  printf("mnożenie = %"PRId8"\r\n", a8 + b8);
  printf("dzielenie = %"PRId8"\r\n\n", a8 / b8);

  // int16_t
  printf("Podaj dwie liczby int16!\r\n");
  int16_t a16 = 1; int16_t b16 = 1;
  scanf("%" SCNd16, &a16);
  scanf("%" SCNd16, &b16);
  printf("Podane liczby: a = %"PRId16", b = %"PRId16"\r\n", a16, b16);
  printf("dodawanie = %"PRId16"\r\n", a16 + b16);
  printf("mnożenie = %"PRId16"\r\n", a16 + b16);
  printf("dzielenie = %"PRId16"\r\n\n", a16 / b16);

  // int32_t
  printf("Podaj dwie liczby int32!\r\n");
  int32_t a32 = 1; int32_t b32 = 1;
  scanf("%" SCNd32, &a32);
  scanf("%" SCNd32, &b32);
  printf("Podane liczby: a = %"PRId32", b = %"PRId32"\r\n", a32, b32);
  printf("dodawanie = %"PRId32"\r\n", a32 + b32);
  printf("mnożenie = %"PRId32"\r\n", a32 + b32);
  printf("dzielenie = %"PRId32"\r\n\n", a32 / b32);

  // float - wymaga dodania flagi przy kompilacji (uwzględniona w pliku Makefile)
  printf("Podaj dwie liczby float!\r\n");
  float af = 1.0;
  float bf = 1.0;
  scanf("%f", &af);
  scanf("%f", &bf);
  printf("Podane liczby: a = %f, b = %f \r\n", af, bf);
  float wf = af + bf;
  printf("dodawanie = %f \r\n", wf);
  wf = af * bf;
  printf("mnożenie = %f \r\n", wf);
  wf = af / bf;
  printf("dzielenie = %f \r\n\r\n", wf);

  // int64_t - nasz artmega nie obsługuje wejścia/wyjścia 64 bitowego
  // używamy tutaj wczytywania 32bitowego które niejawnie przekonwertowane jest jako 64
  // kompilator radzi aby nie robić 
  printf("Podaj dwie liczby int64!\r\n");
  int64_t a64 = 1;   int64_t b64 = 1; 
  scanf("%ld", &a64);
  scanf("%ld", &b64);
  printf("Podane liczby: a = %ld, b = %ld\r\n", a64, b64);
  printf("dodawanie = %ld \r\n", a64 + b64);
  printf("mnożenie = %ld \r\n", a64 + b64);
  printf("dzielenie = %ld \r\n", a64 / b64);

/*
  printf("Podaj liczbę 64bit \r\n"); 
  // ------------------------------------
  // tutaj możemy pobrać liczbę 64 bitową jako string,
  // który z pomocą funkcji bibliotecznych będzie przekonwertowany do inta
  // alternatywnie: można skorzystać z rozbicia inta64 na dwie liczby int32
  // ------------------------------------
  printf("Podaj tekst ():\r\n");
  char str[32];
  scanf("%[^\r\n]%*c", str);
  printf("%s \t\n", str);
*/
}

