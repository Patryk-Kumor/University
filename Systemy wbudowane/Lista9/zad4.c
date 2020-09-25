#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUZZ PB1
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define TONE(step, delay) \
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
      BUZZ_PORT |= _BV(BUZZ); \
      for (uint16_t j=0; j < step; j++) { _delay_us(1); } \
      BUZZ_PORT &= ~_BV(BUZZ); \
      for (uint16_t j=0; j < step; j++) { _delay_us(1); } \
    }

#define pause 50

#define c  988 
#define cs 932 
#define d  880 
#define ds 831 
#define e  784 
#define f  740 
#define fs 698 
#define g  659 
#define gs 622  
#define a  587 
#define as 554 
#define b  523

// STAR WARS IMPERIAL MARCH
/*
const uint16_t note[] PROGMEM = { a,a,a, f,c,a, f,c,a, e,e,e, f,c,a, f,c,a, e,e,e, f,c,a, f,c,a };
const uint16_t leng[] PROGMEM = { 500,500,500, 400,200,600, 400,200,600, 500,500,500, 400,200,600, 400,200,600,500,500,500, 400,200,600, 400,200,600 };
*/

// MARIO
const uint16_t note[] PROGMEM = { e, e, 1, e, 1, c, e, 1, g, 1, 1,  1, g, 1, 1, 1, c, 1, 1, g, 1, 1, e, 1, 1, a, 1, b, 1, as, a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1,
 1, c, 1, 1, g, 1, 1, e, 1, 1, a,  1, b, 1, as, a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1, 1, e, e, 1, e, 1, c, e, 1, g, 1, 1,  1, g, 1, 1, 1, c, 1, 1, g, 1, 1, e, 1, 1,
 a, 1, b, 1, as, a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1, 1, c, 1, 1, g, 1, 1, e, 1, 1, a,  1, b, 1, as, a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1, 1, e, e, 1, e,
 1, c, e, 1, g, 1, 1,  1, g, 1, 1, 1, c, 1, 1, g, 1, 1, e, 1, 1, a, 1, b, 1, as, a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1, 1, c, 1, 1, g, 1, 1, e, 1, 1, a,  1, b, 1, as,
 a, 1, g, e, g, a, 1, f, g, 1, e, 1, c, d, b, 1, 1 };
const uint16_t leng[] PROGMEM  = { 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55,
 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 
 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55, 50, 50, 50, 50, 50, 50, 50, 50,
 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 
 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 55, 55, 55, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50 };

const uint32_t size = sizeof(note) / 2; // tab / sizeof int16

int main() {
  BUZZ_DDR |= _BV(BUZZ);
  uint16_t n = 1;
  uint16_t l = 1;
  uint32_t i;
  while (1) {
    for (i = 0; i < size; i++) {
      n = pgm_read_word(&note[i]);
      l = pgm_read_word(&leng[i]);
      TONE(n, l); 
      TONE(1, pause); 
    }
    _delay_ms(1000);
  }
}
