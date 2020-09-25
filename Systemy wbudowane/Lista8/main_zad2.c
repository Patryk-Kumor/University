/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

// Kolejka
QueueHandle_t xQueue;

int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xQueue = xQueueCreate(10, sizeof(uint32_t));

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
/*
    DDRB |= _BV(PB5);

    for ( ;; )
    {
        PORTB ^= _BV(PB5);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
*/
    DDRB |= _BV(PB5);
    uint32_t time;
    for (;;) {
      if (xQueue != 0) {
        if (xQueueReceive( xQueue, 
                           &(time),
                           (TickType_t)10 )) {
            printf("Odebrano = %"PRIu32"\r\n", time);
            PORTB |= _BV(PB5);
            vTaskDelay(time / portTICK_PERIOD_MS);
            PORTB &= ~_BV(PB5);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
      }
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
    uart_init();
    stdin = stdout = stderr = &uart_file;

    char buff[5];
    char *end;

    for ( ;; )
    {
        // ODCZYT
        for (uint8_t i = 0; i < 5; i++){
            buff[i] = 0;
        }
        //puts("Podaj max 5 cyfr \r\n");
        for (uint8_t i = 0; i < 5; i++){
            buff[i] = getchar();
        }
        uint32_t count = (uint32_t)strtol(buff, &end, 10);
        // DODANIE DO KOLEJKI
        if (xQueue != 0) {
            if (xQueueSend( xQueue, 
                            (void*)&count,
                            (TickType_t)10 ) != pdPASS) {
                //printf("Nie wysłano \r\n");           
            }
            else {
                //printf("Wysłano %"PRIu32"\r\n", count);
            }
        }
    }
}
