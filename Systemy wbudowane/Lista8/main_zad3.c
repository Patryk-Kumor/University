/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "queue.h"
#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY 1

#define mainSERIAL_TASK_PRIORITY 2

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);
static void vSerial(void* pvParameters);

xTaskHandle blink_handle;
xTaskHandle serial_handle;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Przerwanie wykona się kiedy zostają odebrane dane USART // odebrano char
ISR(USART_RX_vect) {
  // Jeśli kolejka jest niepusta
  if (xQueueIsQueueEmptyFromISR(xQueue2) == pdFALSE) {
    char temp = UDR0;
    //BaseType_t xTaskWoken = pdFALSE;
    xQueueSendFromISR( xQueue2, &temp, NULL);
  }
}
// Przerwanie opróźnienia rejestru danych USART // wykonuje się kiedy rejestr UART jest pusty
ISR(USART_UDRE_vect) {
  // Jeśli kolejka jest niepusta
  if (xQueueIsQueueEmptyFromISR(xQueue1) == pdFALSE) {
    char temp;
    //BaseType_t xTaskWoken = pdFALSE;
    xQueueReceiveFromISR(xQueue1, (void*)&temp, NULL);
    UDR0 = temp;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int uart_transmit(char c, FILE *stream) {
  // Jeśli kolejka jest pusta
  if (uxQueueSpacesAvailable(xQueue1) == 0) {
    while(!(UCSR0A & _BV(UDRE0))) {
      //taskYIELD();
      vTaskDelay(2 / portTICK_PERIOD_MS);
    }
  }
  UCSR0B &= ~_BV(UDRIE0);
  xQueueSend( xQueue1, (void*)&c, (TickType_t)10);
  UCSR0B |= _BV(UDRIE0);
  return 0;
}

int uart_receive(FILE *stream) {
  // Jeśli kolejka pełna
  if (uxQueueSpacesAvailable(xQueue2) == 10) {
    while (!(UCSR0A & _BV(RXC0))) {
      //taskYIELD();
      vTaskDelay(2 / portTICK_PERIOD_MS);
    }
    return UDR0;
  }
  else{
    char temp;
    UCSR0B &= ~_BV(RXCIE0);
    xQueueReceive(xQueue2, &(temp), (TickType_t)10 ); 
    UCSR0B |= _BV(RXCIE0); 
    return temp;  
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    DDRB |= _BV(PB5);

    for ( ;; )
    {
        PORTB ^= _BV(PB5);
        vTaskDelay(500 / portTICK_PERIOD_MS);
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
    // Create UART Queues
    xQueue1 = xQueueCreate(10, sizeof(char));
    xQueue2 = xQueueCreate(10, sizeof(char));
    // wlacz przerwania USART_RX i USART_UDRE
    UCSR0B |= _BV(RXCIE0) | _BV(UDRIE0);
    // odmaskowanie przerwań
    sei();
    char input;
    for ( ;; )
    {
        puts("\r\nHello World\r\n");
        char buff[2] = " ";
        buff[0] = getchar();
        puts("You wrote \r"); 
        puts(buff);
        //printf("You wrote %c\r\n", input); 
    }
}

