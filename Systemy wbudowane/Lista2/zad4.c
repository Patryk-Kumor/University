#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRC = 0b00000011;
  DDRD = 0b11111111;

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

  uint8_t i = 0;
  uint32_t sec = 250;
  // odliczanie
  while(1){
    while (sec) {
      PORTC = 1;
      PORTD = digits[i % 10];
      _delay_ms(2);

      PORTC = 2;
      PORTD = digits[i / 10];;
      _delay_ms(2);
      
      sec--;
    }
    sec=250;
    i++;
    if (i == 60){  
      while (1) {
        PORTC = 1;
        PORTD = digits[0];
        _delay_ms(2);

        PORTC = 2;
        PORTD = digits[0];;
        _delay_ms(2);
      }
    }
  }


}


