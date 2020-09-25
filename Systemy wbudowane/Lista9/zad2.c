#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

FILE hd44780_file;

int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  uint8_t tab[5] = {
    0b10000,
    0b11000,
    0b11100,
    0b11110,
    0b11111
  };
  // zapis 5 charów
  for (uint8_t j=0; j<5; j++){ 
    LCD_WriteCommand(0x40 + j*8);
    for (uint8_t i = 0; i < 8; i++) {
      LCD_WriteData(tab[j]);
    }
  }

  uint8_t x = 0;
  uint8_t c = 0;
  while(1) {
    LCD_GoTo(x, 0);
    printf("%c", c);
    LCD_GoTo(x, 1);
    printf("%c", c);
    _delay_ms(500);
    c++;
    if (c==5) { 
      c = 0;
      x++;
    }
    if (x==16) {
      LCD_Clear();
      x = 0;
      _delay_ms(500);
    }
  }
}

