#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_R PB6
#define LED_G PD5
#define LED_B PB3

#define LED_DDR DDRB
#define LED_PORT PORTB

static uint8_t arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 14, 14, 15, 15, 16, 1,
  7, 17, 18, 19, 19, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 28, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 53, 54, 55, 56, 57, 58, 60, 60};
static uint8_t arr2[] = {60, 58, 57, 56, 55, 54, 53, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 30, 29, 28, 27, 26, 25, 25, 24, 23, 22, 22, 21, 20, 19, 
  19, 18, 17, 17, 16, 15, 15, 14, 14, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void timers_init()
{
  TCCR0A = _BV(COM0A1) | _BV(COM0B1);
  TCCR0A |= _BV(WGM01) | _BV(WGM00); // FAST PWM
  TCCR0B |= _BV(CS00); // 1Hz

  TCCR2A = _BV(COM2A1);
  TCCR2A |= _BV(WGM21) | _BV(WGM20); // FAST PWM
  TCCR2B |= _BV(CS20); // 1Hz

  // ustaw piny wyjście
  DDRD |= _BV(LED_R);
  DDRD |= _BV(LED_G); 
  DDRB |= _BV(LED_B);
}

void rgb(uint8_t r, uint8_t g, uint8_t b)
{
  // włączony - 0, wyłączony - 255 (na odwrót niż być powinno)
  OCR0B = 255 - r;	// red
  OCR2A = 255 - g;	// green
  OCR0A = 255 - b;	// blue
}
void hsv(uint8_t h, uint8_t s, uint8_t v) // (255,255,255)
{
  if (v==0) { rgb(0,0,0); }
  else{
    uint8_t region = h / 43;
    uint8_t rem = (h - (region  * 43)) *6;
    uint8_t P = (v * (255 - s)) >> 8;
    uint8_t Q = (v * (255 - ((s * rem) >> 8))) >> 8;
    uint8_t T = (v * (255 - ((s * (255 - rem)) >> 8))) >> 8;
    if (region == 0) {
      rgb(v,T,P);
    }
    else if  (region == 1) {
      rgb(Q,v,P);
    }
    else if  (region == 2) {
      rgb(P,v,T);
    }
    else if  (region == 3) {
      rgb(P,Q,v);
    }
    else if (region == 4) {
      rgb(T,P,v);
    }
    else {
      rgb(v,P,Q);
    }
  }
}

int main()
{
  uint8_t i = 0;
  timers_init();
  // oddech
  while(1) {
    uint8_t c = rand();
    i = 0; rgb(0,0,0); _delay_ms(300);
    while (i < 100) {
      hsv(c, 255, i << 1);
      i++;
      for (int j = 0; j < arr2[i] >> 1 ; j++ ) {  _delay_ms(1);  };
    }
    i = 0; 
    while (i < 100) {
      hsv(c, 255, (100-i)<<1);
      i++;
      for (int j = 0; j < arr1[i] >> 1 ; j++ ) {  _delay_ms(1);  };
    }
  }
}

