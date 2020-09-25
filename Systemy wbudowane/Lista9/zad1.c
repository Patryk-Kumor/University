#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

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

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE hd44780_file;
FILE uart_file;

int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;
  // skonfiguruj strumienie wejścia
  fdev_setup_stream(&uart_file, NULL, uart_receive, _FDEV_SETUP_READ);
  stdin = &uart_file;
  // program testowy
  uint8_t x = 0; // 0-15
  uint8_t y = 0; // 0-1
  char buff[16] = "";
  while(1) {
    LCD_GoTo(x, y);
    char temp = 1;
    scanf("%c", &temp);
    // Jeżeli znak nowej linii 
    if (temp == 13) {
      if (y == 1) { 
        y = 0; 
        LCD_Clear(); 
        LCD_GoTo(0, 0); 
        printf("%s", buff);
        x = 0; y = 1;
      }
      else{
        x = 0; y = 1;
      }
      for (uint8_t i=0; i<16; i++)
        buff[i] = ' ';
      continue;
    }
    // wpp
    else {
      printf("%c", temp);
    }
    // Kontrola wierszy - pozycji
    if (y == 1){
      buff[x] = temp;
    }
    x++;    
    if (x == 16) { y++; x=0; }
    if (y == 2) { 
      y = 0; 
      LCD_Clear(); 
      LCD_GoTo(x, y); 
      printf("%s", buff);
      x = 0; y = 1;
    }

  }
}

