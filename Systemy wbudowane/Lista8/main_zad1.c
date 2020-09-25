/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   2

#define mainSERIAL_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
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

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vBlinkLed(void* pvParameters)
{
  PORTB |= _BV(PB4);
  DDRB |= _BV(PB5);

  uint8_t i = 0;
  uint8_t buffor[100] = {0};

  for ( ;; ) {
    // zapalenie/zgaszenie zgodnie z bufforem
    if (buffor[i]) {
      PORTB &= ~_BV(PB5);
    }
    else {
      PORTB |= _BV(PB5);
    }
    // sprawdzenie stanu przycisku i nadpisanie w bufforze
    if (PINB & _BV(PB4)) { 
      buffor[i] = 1;
    }
    else {
      buffor[i] = 0;
    }
    i++;
    // zapętlenie bufforu
    if (i == 100) { i = 0; }
    // delay czasu sprawdzania
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSerial(void* pvParameters)
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111; 
  uint8_t i = 0;
  for ( ;; ) {
    // ustawianie kolejnych diod
    while(i<7){
      PORTD = (1 << i);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      i++;
    }
    // ustawianie kolejnych diod - wstecz
    while(i>0){
      PORTD = (1 << i);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      i--;
    }
  }
}
