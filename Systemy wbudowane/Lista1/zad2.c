#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

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

  // --------------------------------------

  // KODY MORSA:
  const char morse[][10] = {
        ".-",	// a
        "-...",	
        "-.-.", 
        "-..", 
        ".", 
        "..-.", 
        "--.", 
        "....", 
        "..", 
        ".---", 
        "-.-", 
        ".-..", 
        "--", 
        "-.", 
        "---", 
        ".--.", 
        "--.-", 
        ".-.", 
        "...", 
        "-", 
        "..-", 
        "...-", 
        ".--",  
        "-..-",  
        "-.--",
        "--.."	// z 
  };

  // dioda zgaszona na starcie
  LED_DDR |= _BV(LED);

  // podawanie tekstu do wymrygania w kodzie Morse'a
  printf("Podaj tekst:\r\n");
  char str[32];
  scanf("%[^\r\n]%*c", str);
  printf("%s \t\n", str);
  printf("Podano tekst - poczekaj aż dioda przestanie mrygać\r\n\r\n"); 

  // mryganie
  for(int i = 0; i<32; i++){
    char znak = tolower(str[i]);
    // przekazywanie mrygania dla jednego znaku ascii
    if (znak >= 97 && znak <= 122){
      printf("Znak: %c, ", znak);
      int j = znak-97;
      printf("kod: %s\r\n", morse[j]); 
      // przekazywanie mrugniecia po mrugnieciu dla jednego znaku ascii
      for (short c = 0; morse[j][c] != 0; c++){
        // kropka w kodzie Morse'a - trwa tyle co przerwa miedzy kropka/kreska
	if (morse[j][c] == 46){
          printf("   .  \r\n"); // single mryg
          // zapalona na sekundę
          LED_PORT |= _BV(LED);
          _delay_ms(1000);
        }
        // kreska w kodzie Morse'a - 3x czas kropki
	else{ 
	  printf("   -  \r\n"); // single mryg
          // zapalona na 3. sekundy
          LED_PORT |= _BV(LED);
          _delay_ms(3000);
        }
        // przerwa pomiedzy kropka/kreska
        // zgaszona na sekundę
        LED_PORT &= ~_BV(LED);
        _delay_ms(1000);
      }
    }
    // spacja
    else if (znak == 32){
      printf("Spacja \r\n"); 
        // zgaszona na 10 sekund
        LED_PORT &= ~_BV(LED);
        _delay_ms(10000);
    }
    // zakończenie
    else if (znak == 0) { break; }
    // znak nieobsługiwany
    else { printf("Znak nieobsługiwany \r\n"); }
  } 

  // dioda zgaszona na koniec
  LED_DDR |= _BV(LED);

}

