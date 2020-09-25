/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainHEAT_TASK_PRIORITY   2

#define mainSERIAL_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vHeat(void* pvParameters);

static void vSerial(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/
// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0) | _BV(REFS1); // Internal 1.1V voltage reference with external capacitor at AREF pin
  DIDR0   = _BV(ADC0D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}
volatile uint16_t temperature;
volatile uint16_t set_temperature;
/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;
    adc_init();

    set_temperature = 466;
    // Create task.
    xTaskHandle heat_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vHeat,
         "heat",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainHEAT_TASK_PRIORITY,
         &heat_handle
        );

    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/


static void vHeat(void* pvParameters)
{
    DDRB |= _BV(PB5);
    uint16_t v;

    for ( ;; )
    {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      while (!(ADCSRA & _BV(ADIF))) taskYIELD(); // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      v = ADC; // weź zmierzoną wartość (0..1023)
      temperature = v;

      if (v >= set_temperature) { // GRZAŁKA OFF jeśli temp jest wyższa niż set
      	PORTB &= ~_BV(PB5);
      }
      if (v <= (set_temperature - 10)) { // GRZAŁKA ON jeśli temp jest niższa niż set - 1
        PORTB |= _BV(PB5);
      }

      vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

static void vSerial(void* pvParameters)
{
    char command = ' ';

    for ( ;; )
    {   
      command = getchar();
      if (command == 's') {
        puts("SET \r");
        char buff[5];
        char *end;
        for (uint8_t i=0; i<3; i++) {
          buff[i] = getchar();
        }
        buff[4] = 0;
        buff[3] = ' ';
        uint16_t count = (uint16_t)strtol(buff, &end, 10);
        char liczba[4];
        utoa (count,liczba,10);
        puts(liczba);
        puts("\r");
        // Print
        buff[4] = buff[3];
        buff[3] = buff[2];
        buff[2] = '.';
        buff[4] = 0;
        puts(buff);
        puts("\r");
        // make set temperature
        float tempo = ( 0.5 + ((float) count) / 1000.0 ) * (1024.0 / 1.1 );
        set_temperature = (uint16_t) tempo;
      }
      else if (command == 'a') {
        puts("ADC \r");
        uint16_t val = temperature;
        // Print
        char liczba[4];
        utoa (val,liczba,10);
        puts(liczba);
        puts("\r");
      }
      else if (command == 't') {
        puts("TEMPERATURE \r");
        uint16_t val = temperature;
        float temp= (((float)val) * 1.1) / 1024.0;
        temp = temp - 0.5;
        temp = temp / 0.01;
        val = (uint16_t)(temp*100);
        // Print
        char liczba[5];
        utoa (val,liczba,10);
        liczba[4] = liczba[3];
        liczba[3] = liczba[2];
        liczba[2] = '.';
        liczba[4] = 0;
        puts(liczba);
        puts("\r");
      }
      else if (command == 'c') {
        puts("DEFAULT TEMPERATURE \r");
        uint16_t val = set_temperature;
        float temp= (((float)val) * 1.1) / 1024.0;
        temp = temp - 0.5;
        temp = temp / 0.01;
        val = (uint16_t)(temp*100);
        // Print
        char liczba[5];
        utoa (val,liczba,10);
        liczba[4] = liczba[3];
        liczba[3] = liczba[2];
        liczba[2] = '.';
        liczba[4] = 0;
        puts(liczba);
        puts("\r");
      }
    }
}
