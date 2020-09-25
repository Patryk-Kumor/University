#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <util/delay.h>
#include <string.h>
#include "i2c.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
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

const uint8_t eeprom_addr = 0xa0;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();
  // program testowy

  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }

char command[6];
      uint16_t addr = 0;
      uint16_t len = 0;
      uint16_t i = 0;
uint8_t csum;
uint8_t data;


        uint8_t buffor[32];

        uint8_t val = 0;
        uint8_t flag = 0;


uint8_t n;
uint8_t rest;
uint8_t calc;

  while(1) {
    scanf("%s", command);
    printf("%s ", command);
    if (!strcmp(command, "read")) {
      addr = 0;
      len = 0;
      i = 0;
      // czytamy adres
      scanf("%" SCNd16, &addr);
      printf("%"PRId16"", addr);
      // czytamy długość
      scanf("%" SCNd16, &len);
      printf(" %"PRId16"", len);
      // przetwarzanie 
      printf("\r\n----READ----\r\n");
      addr &= 0x1ff; // pilnujemy długość adresu
      csum = 0; 
      printf(":%.2x ", len);
      printf("%.4x ", addr);
      printf("%.2x ", i);
      csum += len ;
      csum += addr ; 
      // pierwszy start z podaniem adresu
      i2cStart();
      i2cCheck(0x08, "I2C start")
      i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
      i2cCheck(0x18, "I2C EEPROM write request")
      i2cSend(addr & 0xff);
      i2cCheck(0x28, "I2C EEPROM set address")
      // drugi start 
      i2cStart();
      i2cCheck(0x10, "I2C second start")
      i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
      i2cCheck(0x40, "I2C EEPROM read request")
      // cykl
      while (i < len) {
        data = i2cReadAck();
        i2cCheck(0x50, "I2C EEPROM read")
        csum += data;
        printf("%.2x ", data);
        //printf("Odczytano: %.3x: %x\r\n", addr, data);
        //addr++;
        i++;
      }
      // ostatnie czytanie NOACK
      data = i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")
      //csum += data;
      //printf("%.2x ", data);
      // zakończenie 
      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      printf("%.2x \r\n", csum);
      printf("---READ-END---\r\n");
    }
    else if (!strcmp(command, "write")) {
      while (1) {
         addr = 0;
         len = 0;
         i = 0;
         val = 0;
         flag = 0;
         csum = 0;
        // CZYTANIE ROZMIARU
        char tab[2];
        char *end;
        scanf(" %c%c", &tab[0], &tab[1]);
        printf(":%c%c", tab[0], tab[1]);
        len = (uint16_t) strtol(tab, &end, 16);
        // CZYTANIE ADRESU
        char tab2[4];
        char *end2;
        scanf(" %c%c%c%c", &tab2[0], &tab2[1], &tab2[2], &tab2[3]);
        printf("%c%c%c%c", tab2[0], tab2[1], tab2[2], tab2[3]);
        addr = (uint16_t) strtol(tab2, &end2, 16);
        addr &= 0x1ff; // pilnujemy długość adresu
        // CZYTANIE TYPU
        char tab3[2];
        char *end3;
        scanf(" %c%c", &tab3[0], &tab3[1]);
        printf("%c%c", tab3[0], tab3[1]);
        flag = (uint8_t) strtol(tab3, &end3, 16);
        if (flag) { printf("\r\n"); break; }
        while (i < len) {
            // CZYTANIE WARTOŚCI
            char tab4[2];
            char *end4;
            scanf(" %c%c", &tab4[0], &tab4[1]);
            printf("%c%c", tab4[0], tab4[1]);
            val = (uint8_t) strtol(tab4, &end4, 16);
            buffor[i] = val;
            csum += val;
            //printf("(c%.2x)", csum);
            i++;       
        }       
        i = 0;
        csum += len;
        //printf("(c%.2x)", csum);
        csum += addr;
        //printf("(c%.2x)", csum);
        // CZYTANIE SUMY
        char tab4[2];
        char *end4;
        scanf(" %c%c", &tab4[0], &tab4[1]);
        printf("%c%c", tab4[0], tab4[1]);
        calc = (uint8_t) strtol(tab4, &end4, 16);
        if (calc != csum) {
          printf(" - Wyliczone: %.2x, podane: %.2x\r\n", csum, calc);
          printf(" - SUMA KONTROLNA JEST NIEZGODNA \r\n"); break;
        }
        if ((len == 0) || (len >= 32)) { break; }
        // zapis
        while (i < len) {
          i2cStart();
          i2cCheck(0x08, "I2C start")
          i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
          i2cCheck(0x18, "I2C EEPROM write request")
          i2cSend(addr & 0xff);
          i2cCheck(0x28, "I2C EEPROM set address")
          n = 0;
          //uint8_t rest = 16 - (addr % 16);
          rest = 16 - (addr & 15);        
          while (n < rest && len>i) {
            val = buffor[i];
            i2cSend(val);
            i2cCheck(0x28, "I2C EEPROM send data")
            //printf("Zapisano: %.3x: %x\r\n", addr, val);
            csum += val;
            n++;
            i++;
            addr++;
          }
          //addr +=n;
          i2cStop();
          i2cCheck(0xf8, "I2C stop")
          _delay_ms(100);
        }
        printf("\r\n");
      }
    }  
    else { 
      printf("\r\nNiepoprawne polecenie\r\n\r\n");
      continue;
    }
  }
}

