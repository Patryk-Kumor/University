#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PD2
#define BTN_PIN PIND
#define BTN_PORT PORTD


// inicjalizacja wejścia/wyjścia
void io_init()
{
  // ustaw pull-up na PD2
  PORTD |= _BV(PD2);
  // ustaw wyjście na PB5
  DDRB |= _BV(PB5);
}

// inicjalizacja licznika
void timer_init()
{
  // preskaler 1024
  TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
  // odmaskowanie przerwania przepełnienia licznika
  TIMSK2 |= _BV(TOIE2);
}

volatile uint8_t i = 0;
volatile uint8_t buffor[60] = {0};

// procedura obsługi przerwania przepełnienia licznika
ISR(TIMER2_OVF_vect) {
    // zapalenie/zgaszenie zgodnie z bufforem => mam na odwrót 
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
    // zapętlenie bufforu 
    i++;
    if (i==60) { i = 0; }
}

int main()
{
  // zainicjalizuj wejście wyjście
  io_init();
  // zainicjalizuj licznik 2
  timer_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  // odmaskuj przerwania
  sei();
  // pętla uśpienia
  while(1) {
    sleep_mode();
  }
}

