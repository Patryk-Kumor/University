#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <string.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

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
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
// -------------------------------------------------------------
// -------------------------------------------------------------


  while(1){
    if (! (BTN_PIN & _BV(BTN))) {
      break;
    }
  }

  uint8_t click = 0;
  uint16_t pressed = 0;
  uint8_t i = 1;
  uint8_t block = 0;

  uint8_t sign[20] = {0};

  char ascii_sign[9] = "";

  uint8_t j = 0;

  uint8_t count = 0;
  uint8_t space = 0;

  uint8_t x = 0;

  while(1){
    // sekundniky
    if (i == 0) {

      if (!block) {

	if (space==5)
        {
          j = 0;
          space = 0;
          // Konwertowanie tab
          x = 0; ascii_sign[0] = '\0'; 
          while (x < 18 && j < 9)
          {
            if (sign[x] & sign[x+1] & sign[x+2]){
            	x+=4; ascii_sign[j] = '-'; j++;
            }
            else if (sign[x] & !sign[x+1] ){
                x+=2; ascii_sign[j] = '.'; j++;
            }
            else {
              break;  //błąd transmisji
            }
          }
          ascii_sign[j] = '\0';
          printf("      ");
          if (!strcmp(ascii_sign, ".-")) { printf("A"); }
          else if (!strcmp(ascii_sign, "-..")) { printf("B"); }              
          else if (!strcmp(ascii_sign, "-.-.")) { printf("C"); }              
          else if (!strcmp(ascii_sign, "-..")) { printf("D"); }              
          else if (!strcmp(ascii_sign, ".")) { printf("E"); }              
          else if (!strcmp(ascii_sign, "..-.")) { printf("F"); }              
          else if (!strcmp(ascii_sign, "--.")) { printf("G"); }              
          else if (!strcmp(ascii_sign, "....")) { printf("H"); }              
          else if (!strcmp(ascii_sign, "..")) { printf("I"); }              
          else if (!strcmp(ascii_sign, ".---")) { printf("J"); }              
          else if (!strcmp(ascii_sign, "-.-")) { printf("K"); }              
          else if (!strcmp(ascii_sign, ".-..")) { printf("L"); }              
          else if (!strcmp(ascii_sign, "--")) { printf("M"); }              
          else if (!strcmp(ascii_sign, "-.")) { printf("N"); }              
          else if (!strcmp(ascii_sign, "---")) { printf("O"); }              
          else if (!strcmp(ascii_sign, ".--.")) { printf("P"); }  
          else if (!strcmp(ascii_sign, "--.-")) { printf("Q"); }                          
          else if (!strcmp(ascii_sign, ".-.")) { printf("R"); }              
          else if (!strcmp(ascii_sign, "...")) { printf("S"); }              
          else if (!strcmp(ascii_sign, "-")) { printf("T"); }              
          else if (!strcmp(ascii_sign, "..-")) { printf("U"); }              
          else if (!strcmp(ascii_sign, "...-")) { printf("V"); }              
          else if (!strcmp(ascii_sign, ".--")) { printf("W"); }              
          else if (!strcmp(ascii_sign, "-..-")) { printf("X"); }              
          else if (!strcmp(ascii_sign, "-.--")) { printf("Y"); }              
          else if (!strcmp(ascii_sign, "--..")) { printf("Z"); }        
          else if (!strcmp(ascii_sign, ".-..-")) { printf("spacja"); }                    
          else
              printf("błąd transmisji");
          j = 0;
          printf("\r\n");
          // Czyszczenie tab:
          for (x = 0; x < 18; x++) { sign[x] = 0; }
          block = 1;
        }

        else if (click & (count < 3)) {
          click = 0;
          space = 0;
          if ( j < 18) { sign[j] = 1; }
          printf("x");
          count++;
        }

        else {
          if ( j < 18) { sign[j] = 0; }
          printf("_");
          count = 0;
          space++;
        }

      }
      else {
        if (click) { block = 0; i=99; j= -1 ;}
      }

      j++;
    }

    // Kontrola przycisku w czasie tej sekundy
    if (BTN_PIN & _BV(BTN)) {
      LED_PORT &= ~_BV(LED); 
      pressed = 0;     
    }
    else {
      if (pressed >= 300) { LED_PORT |= _BV(LED); } // zapalamy gdy trzymamy za długo
      pressed++;
      click = 1;
    }

    // Opóźnienie
    _delay_ms(10);
    i++;
    i %= 150;
  }





}
