#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define DELAY   100

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111; 
  uint8_t i = 0;
  while(1){
    // ustawianie kolejnych diod
    while(i<7){
      PORTD = (1 << i);
      _delay_ms(DELAY);
      i++;
    }
    // ustawianie kolejnych diod - wstecz
    while(i>0){
      PORTD = (1 << i);
      _delay_ms(DELAY);
      i--;
    }
  }
  return(0);
}


