/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "semphr.h"
#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainFOTO_TASK_PRIORITY   1
#define mainPOTENCJO_TASK_PRIORITY   1
#define mainTERMO_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vFoto(void* pvParameters);
static void vPotencjo(void* pvParameters);
static void vTermo(void* pvParameters);

/******************************************************************************/

xTaskHandle foto_handle;
xTaskHandle potencjo_handle;
xTaskHandle termo_handle;

SemaphoreHandle_t xsem1;
SemaphoreHandle_t xsem2;

/******************************************************************************/

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  // włącz ADC
  ADCSRA |= _BV(ADEN); 
  // AUTO ADC_vect
  ADCSRA |= _BV(ADIE);
}

/******************************************************************************/
/******************************************************************************/

int main(void)
{
    // UART
    uart_init();
    stdin = stdout = stderr = &uart_file;
    // ADC
    adc_init();
    // Przerwania
    sei();
    // Semafory
    xsem1 = xSemaphoreCreateMutex();
    xsem2 = xSemaphoreCreateCounting(1,0); //(max,initial)
    
    // Create task.
    xTaskCreate
        (
         vFoto,
         "foto",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainFOTO_TASK_PRIORITY,
         &foto_handle
        );
    xTaskCreate
        (
         vPotencjo,
         "potencjo",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainPOTENCJO_TASK_PRIORITY,
         &potencjo_handle
        );
    xTaskCreate
        (
         vTermo,
         "termo",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainTERMO_TASK_PRIORITY,
         &termo_handle
        );
    // Start scheduler.
    vTaskStartScheduler();
    return 0;
}

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/
volatile uint16_t adc_val;

// obsługa przerwań ukończonej konwersji 
ISR(ADC_vect) {
  if (xsem2 != NULL) { 
    xSemaphoreGiveFromISR(xsem2, pdFALSE);
  }
}

// Zwracanie wartości ADC
uint16_t readADC(uint8_t mux){
  ADMUX &= 0b11110000;
  ADMUX |= mux;
  ADCSRA |= _BV(ADSC);
  xSemaphoreTake(xsem2, portMAX_DELAY);
  uint16_t v = ADC;
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  return v;
}

/******************************************************************************/
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

static void vFoto(void* pvParameters)
{
  for (;;) {
    if (xSemaphoreTake(xsem1, portMAX_DELAY) == pdTRUE) {
      uint16_t val = readADC(0);
      //printf("Foto %"PRIu16"\r\n", val);
      char buffer[4];
      utoa (val,buffer,10);
      puts(buffer);
      puts("\rF\r\n");
      xSemaphoreGive(xsem1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    else {
      //vTaskDelay(1 / portTICK_PERIOD_MS);
    }
  }
}
static void vPotencjo(void* pvParameters)
{
  for (;;) {
    if (xSemaphoreTake(xsem1, portMAX_DELAY) == pdTRUE) {
      uint16_t val = readADC(1);
      //printf("Potencjo %"PRIu16"\r\n", val);
      char buffer[4];
      utoa (val,buffer,10);
      puts(buffer);
      puts("\rP\r\n");
      xSemaphoreGive(xsem1);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    else {
      //vTaskDelay(2 / portTICK_PERIOD_MS);
    }
  }
}
static void vTermo(void* pvParameters)
{
  for (;;) {
    if (xSemaphoreTake(xsem1, portMAX_DELAY) == pdTRUE) {
      uint16_t val = readADC(2);
      //printf("Termo %"PRIu16"\r\n", val);
      char buffer[4];
      utoa (val,buffer,10);
      puts(buffer);
      puts("\rT\r\n");
      xSemaphoreGive(xsem1);
      vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    else {
      //vTaskDelay(3 / portTICK_PERIOD_MS);
    }
  }
}

