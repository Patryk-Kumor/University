#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define DELAY 1000

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111; 

  // tablica liczb
  uint8_t digits[10] = {
    0b01000000, // 0
    0b01111001, // 1
    0b00100100, // 2
    0b00110000, // 3
    0b00011001, // 4
    0b00010010, // 5
    0b00000010, // 6
    0b01111000, // 7
    0b00000000, // 8
    0b00010000  // 9
  };

  // odliczanie
  while(1){
    for (uint8_t i = 0; i < 10; i++){
      PORTD = digits[i];
      _delay_ms(DELAY);
    }
  }

  return(0);
}


