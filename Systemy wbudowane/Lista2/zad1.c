#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB



int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

  uint8_t i = 0;
  uint8_t buffor[100] = {0};

  while(1){
    // zapalenie/zgaszenie zgodnie z bufforem
    if (buffor[i]) {
      LED_PORT &= ~_BV(LED);
    }
    else {
      LED_PORT |= _BV(LED);
    }
    // sprawdzenie stanu przycisku i nadpisanie w bufforze
    if (BTN_PIN & _BV(BTN)) { // zgaszony
      buffor[i] = 1;
    }
    else { //zapalony
      buffor[i] = 0;
    }
    i++;
    // zapętlenie bufforu
    i = i % 100;
    // delay czasu sprawdzania
    _delay_ms(10);
  }
}
