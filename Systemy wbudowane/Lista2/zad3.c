#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB


#define BTN_PIN PINB
#define BTN_PORT PORTB
#define BTN1 PB4
#define BTN2 PB3
#define BTN3 PB2



int main() {
  BTN_PORT |= _BV(BTN1);
  BTN_PORT |= _BV(BTN2);
  BTN_PORT |= _BV(BTN3);
  LED_DDR |= _BV(LED);

  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111; 

  //PORTD = 0b11111111; // lampki zapalone
  PORTD = 0b00000000; // lampki zgaszone

  uint8_t dec = 0;

  uint8_t loc1 = 0;
  uint8_t loc2 = 0;
  uint8_t loc3 = 0;

  while(1){

    if ( (BTN_PIN & _BV(BTN1)) && loc1) { // if przycisk puszczony i jest blokada - zdjeta blokada
      loc1 = 0;
    }
    else {  //if przycisk nacisniety, sprawdzamy nacisniecie ponownie oraz czy nie ma blokady - zakladamy blokade i robimy dalsze rzeczy
      if (!(BTN_PIN & _BV(BTN1)) && !loc1 ) {
        _delay_ms(1);       
        if (!(BTN_PIN & _BV(BTN1))) {
          loc1 = 1;
	        dec = 0;
          PORTD = 0;
        }  
      }
    }

    if ( (BTN_PIN & _BV(BTN2)) && loc2) { // if przycisk puszczony i jest blokada - zdjeta blokada
      loc2 = 0;
    }
    else {  //if przycisk nacisniety, sprawdzamy nacisniecie ponownie oraz czy nie ma blokady - zakladamy blokade i robimy dalsze rzeczy
      if (!(BTN_PIN & _BV(BTN2)) && !loc2 ) {
        _delay_ms(1);       
        if (!(BTN_PIN & _BV(BTN2))) {
          loc2 = 1;
	        dec--;
          PORTD = dec ^ (dec >> 1 );
        }  
      }
    }

    if ( (BTN_PIN & _BV(BTN3)) && loc3) { // if przycisk puszczony i jest blokada - zdjeta blokada
      loc3 = 0;
    }
    else {  //if przycisk nacisniety, sprawdzamy nacisniecie ponownie oraz czy nie ma blokady - zakladamy blokade i robimy dalsze rzeczy
      if (!(BTN_PIN & _BV(BTN3)) && !loc3 ) {
        _delay_ms(1);       
        if (!(BTN_PIN & _BV(BTN3))) {
          loc3 = 1;
	        dec++;
          PORTD = dec ^ (dec >> 1 );
        }  
      }
    }

    _delay_ms(40);       
  }
}
