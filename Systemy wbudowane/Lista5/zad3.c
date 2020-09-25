#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;


// inicjalizacja ADC
void adc_init()
{
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); 
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC

}

volatile float val = 0;
volatile uint8_t i = 0;
volatile float tab[100] = {0.0};

// obsługa przerwań ukończonej konwersji 
ISR(ADC_vect) {
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  val = (float) ADC;
  tab[i] = (1.1 * 1024.0) / val;
  i++;

}

void war(){
  float sr = 0;
  for (uint8_t i = 0; i < 100; i++) {
  	sr += tab[i];
  }
  sr = sr / 100.0;
  //printf("Średnia: %f \r\n", sr );
  float war = 0;
  for (uint8_t i = 0; i < 100; i++) {
  	war += (tab[i] - sr) * (tab[i] - sr);
  }
  war = war / 100.0;
  printf("Wariancja: %"PRIu32" \r\n", (uint32_t)(war * 1000000) );
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj adc
  adc_init();

  while(1) {
    // WYNIKI DO ŚMIECI
    for (uint8_t i = 0; i < 5; i++) {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      val = (float)ADC; // weź zmierzoną wartość (0..1023)
    }

    // ADC BEZ NOISE REDUCTION
    for (uint8_t i = 0; i < 100; i++) {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      val = (float) ADC; // weź zmierzoną wartość (0..1023)
      tab[i] = (1.1 * 1024.0) / val;
      //printf("%f \r\n", tab[i] );
    }
    printf("\nBEZ => ");
    war();
    _delay_ms(100);

    // AUTO ADC_vect
    ADCSRA |= _BV(ADIE);
    // noise reduction
    SMCR |= _BV(SM0);
    //set_sleep_mode(SLEEP_MODE_ADC);
    sleep_enable(); // tam ustawia SMCR |= _BV(SE)
    sei();     
    i = 0;
    for (uint8_t j = 0; j < 100; j++) {
        sleep_mode();
    }
    cli();
    sleep_disable();
    printf("Z => ");
    war();

    break;
 }
}

