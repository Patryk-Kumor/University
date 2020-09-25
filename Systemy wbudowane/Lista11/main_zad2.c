#include <avr/sleep.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pid.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // interrupt
}

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM13 -- Phase and Frequency Correct PWM
  // CS1 -- prescaler 8
  // ICR1  = 1023
  // częstotliwość 16e6/(8*1023*2) = 977 Hz
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS11);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
  TIMSK1 |= _BV(TOIE1) | _BV(ICIE1);
}

//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//


/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */

///*

#define K_P 0.25
#define K_I 0.25
#define K_D 0.01
//*/
/*
// mała sinusoida
#define K_P     0.05
#define K_I     0.00
#define K_D     0.05
*/

/*! \brief Flags for status information
 */
struct GLOBAL_FLAGS {
  //! True when PID control loop should run one time
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {1, 7};

//! Parameters for regulator
struct PID_DATA pidData;

/*! \brief Sampling Time Interval
 *
 * Specify the desired PID sample time interval
 * With a 8-bit counter (255 cylces to overflow), the time interval value is calculated as follows:
 * TIME_INTERVAL = ( desired interval [sec] ) * ( frequency [Hz] ) / 255
 */
//! \xrefitem todo "Todo" "Todo list"
#define TIME_INTERVAL   157

/*! \brief Timer interrupt to control the sampling interval
 */
//#pragma vector = TIMER0_OVF_vect
volatile uint16_t i_t = 0;
ISR(TIMER0_OVF_vect){
  if(i_t < TIME_INTERVAL)
    i_t++;
  else{
    gFlags.pidTimer = TRUE;
    i_t = 0;
  }
}

/*! \brief Init of PID controller demo
 */
void Init(void)
{
  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData); // Scaling Factor = 128

  // Set up timer, enable timer/counte 0 overflow interrupt
  TCCR0B = (1<<CS00);
  TIMSK0 = (1<<TOIE0);
  TCNT0 = 0;
}


//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
uint8_t type;
uint16_t reference;
uint16_t v1;
uint16_t v2;

// overflow - 
ISR(TIMER1_OVF_vect){
  type = 1;
  ADMUX = _BV(REFS0); // referencja AVcc, wejście ADC0 - odczyt MOSFET
  ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC0
}
// capture -
ISR(TIMER1_CAPT_vect){
  type = 2;
  ADMUX = _BV(REFS0); // referencja AVcc, wejście ADC0 - odczyt MOSFET
  ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC0
}
// adc
ISR(ADC_vect){
  if (type == 0){
    reference = ADC; 
  }
  else if (type == 1){
    v1 = ADC;
    type = 0;
    ADMUX = _BV(REFS0) | _BV(MUX0); // referencja AVcc, wejście ADC1 - potencjometr
    ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC1
  }
  else if (type == 2){
    v2 = ADC;
    type = 0;
    ADMUX = _BV(REFS0) | _BV(MUX0); // referencja AVcc, wejście ADC1 - potencjometr
    ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC1
  }
}
//-----------------------------------------------------------------------------------------------------------------//

/*! \brief Read reference value.
 *
 * This function must return the reference value.
 * May be constant or varying
 */

int16_t Get_Reference(void)
{
  return reference;
}

/*! \brief Read system process value
 *
 * This function must return the measured data
 */
int16_t Get_Measurement(void)
{
  return v2;
}

/*! \brief Set control input to system
 *
 * Set the output from the controller as input
 * to system.
 */
uint16_t regulator = 0;
void Set_Input(int16_t inputValue)
{
/*
  inputValue *= -1;
  if (((int16_t)regulator + inputValue) < 0) {
    regulator = 0;
  }
  else if (((int16_t)regulator + inputValue) > 1023) {
    regulator = 1023;
  }
  else {
    regulator = (uint16_t)((int16_t)regulator + inputValue);
  }
  OCR1A = regulator;
*/
  inputValue = (-1 * (uint32_t)inputValue * 1023) / MAX_INT; // skalowanie 0-1023
  regulator = (uint16_t) inputValue;
  OCR1A = regulator;
}


//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//


FILE uart_file;

int main(void)
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // uruchom licznik1 - motor DC
  timer1_init();
  OCR1A = 0;

  int16_t referenceValue = 0;
  int16_t measurementValue = 0;
  int16_t inputValue = 0;

  Init();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();//__enable_interrupt();
  
  while(1) {
    if(gFlags.pidTimer)
    {
      measurementValue = Get_Measurement();
      referenceValue = Get_Reference();
      inputValue = pid_Controller(referenceValue, measurementValue, &pidData);
      Set_Input(inputValue);
      sleep_mode();	
      //printf("INPUT: %"PRId16"\r\n", inputValue);      
      gFlags.pidTimer = FALSE;
    }
    sleep_mode();

    printf("ref: %"PRId16" measure: %"PRId16" reg: %"PRIu16"\r\n", referenceValue, measurementValue, regulator);
    //printf("ref: %"PRId16" measure: %"PRId16" input: %"PRId16" reg: %"PRIu16"\r\n", referenceValue, measurementValue, inputValue, regulator);
    //_delay_ms(10);
  }
}
