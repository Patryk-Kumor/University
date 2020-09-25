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

const uint8_t eeprom_addr = 0xd0;



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


  // MAKRO CHECK
  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }

  // PINY: +, D, C, _, -
  uint16_t addr = 0; 

  while(1) {

    char command[6];
    scanf("%s", command);
    printf("%s ", command);

    if ((!strcmp(command, "time"))) {
      addr = 0x00;
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
      // read kolejnych komórek
      uint8_t sec = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t min = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t h = i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")
      // zakończenie 
      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      // WYPISANIE
      printf("\r\n%.2x:%.2x:%.2x\r\n", h, min, sec);
    }
    else if ((!strcmp(command, "date"))) {
      addr = 0x04;
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
      // read kolejnych komórek
      uint8_t date = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t month = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t year = i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")
      // zakończenie 
      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      // WYPISANIE
      printf("\r\n%.2x-%.2x-2%.1x%.2x\r\n", date, month & 0x7F, month >> 7 ,year);
    }
    else if ((!strcmp(command, "set"))) {
      scanf("%s", command);
      printf("%s ", command);
      if ((!strcmp(command, "time"))) {
        uint8_t h; uint8_t min; uint8_t sec;
        uint8_t h_c; uint8_t min_c; uint8_t sec_c;
        // pobieranie znaków
        char tab[2];
        char *end;
        scanf(" %c%c", &tab[0], &tab[1]);
        printf("%c%c:", tab[0], tab[1]);
        h = (uint8_t) strtol(tab, &end, 16);
        scanf("%c%c", &tab[0], &tab[1]);
        printf("%c%c:", tab[0], tab[1]);
        min = (uint8_t) strtol(tab, &end, 16);
        scanf("%c%c", &tab[0], &tab[1]);
        printf("%c%c", tab[0], tab[1]);
        sec = (uint8_t) strtol(tab, &end, 16);
        // KONTROLA
        h_c = (h >> 4)*10 + (h & 0x0F);
        min_c = (min >> 4)*10 + (min & 0x0F);
        sec_c = (sec >> 4)*10 + (sec & 0x0F);
        if ( (h_c > 23) || ((h & 0x0F) >= 0x0a) || ((h >> 4) >= 0x0a) ) { h=0; }
        if ( (min_c > 59) || ((min & 0x0F) >= 0x0a) || ((min >> 4) >= 0x0a) ) { min=0; }
        if ( (sec_c > 59) || ((sec & 0x0F) >= 0x0a) || ((sec >> 4) >= 0x0a) ) { sec=0; }
        //scanf("%.2x:%.2x:%.2x", h, min, sec);
        printf(" -> %.2x:%.2x:%.2x \r\n", h, min, sec);
        //printf(" (c) -> %"PRId8":%"PRId8":%"PRId8" \r\n", h_c, min_c, sec_c);
        // ZAPIS
        addr = 0x00;
        // pierwszy start z podaniem adresu
        i2cStart();
        i2cCheck(0x08, "I2C start")
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        i2cCheck(0x18, "I2C EEPROM write request")
        i2cSend(addr & 0xff);
        i2cCheck(0x28, "I2C EEPROM set address")
        // Wysłanie
        i2cSend(sec);
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cSend(min);
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cSend(h);
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cStop();
        i2cCheck(0xf8, "I2C stop")
      }
      else if ((!strcmp(command, "date"))) {
        uint8_t d; uint8_t m; uint8_t y_h; uint8_t y_l;
        uint8_t d_c; uint8_t m_c;  uint8_t y_c;
        // pobieranie znaków
        char tab[2]; 
        char *end;
        scanf(" %c%c", &tab[0], &tab[1]);
        printf("%c%c-", tab[0], tab[1]);
        d = (uint8_t) strtol(tab, &end, 16);
        scanf("%c%c", &tab[0], &tab[1]);
        printf("%c%c-", tab[0], tab[1]);
        m = (uint8_t) strtol(tab, &end, 16);
        scanf("%c%c", &tab[0], &tab[1]);
        printf("%c%c", tab[0], tab[1]);
        y_h = (uint8_t) strtol(tab, &end, 16);
        scanf("%c%c", &tab[0], &tab[1]);
        printf("%c%c", tab[0], tab[1]);
        y_l = (uint8_t) strtol(tab, &end, 16);
        // KONTROLA
        d_c = (d >> 4)*10 + (d & 0x0F);
        if ( (d_c > 31) || (d == 0) || ((d & 0x0F) >= 0x0a) || ((d >> 4) >= 0x0a) ) { d = 1; }
        m_c = (m >> 4)*10 + (m & 0x0F);
        if ( (m_c > 12) || (m== 0)  || ((m & 0x0F) >= 0x0a) || ((m >> 4) >= 0x0a) ) { m = 1; }
        uint8_t cent = 0;
        if ( y_h == 0x20 ) { cent = 0; }
        else if ( y_h == 0x21 ) { cent = 1; }
        else { y_h = 0; }
        y_c = (y_l >> 4)*10 + (y_l & 0x0F);
        if ( (y_c > 99) || ((y_l & 0x0F) >= 0x0a) || ((y_l >> 4) >= 0x0a) ) { y_l = 0; }
        //scanf("%.2x:%.2x:%.2x", h, min, sec);
        printf(" -> %.2x-%.2x-%.2x%.2x \r\n", d, m, (y_h | cent | 0x20), y_l);
        printf(" (c) -> %"PRId8":%"PRId8":%"PRId8"%"PRId8" \r\n", d_c, m_c, y_h, y_l);
        // ZAPIS
        addr = 0x04;
        // pierwszy start z podaniem adresu
        i2cStart();
        i2cCheck(0x08, "I2C start")
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        i2cCheck(0x18, "I2C EEPROM write request")
        i2cSend(addr & 0xff);
        i2cCheck(0x28, "I2C EEPROM set address")
        // Wysłanie
        i2cSend(d);
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cSend(m | (cent << 7));
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cSend(y_l);
        i2cCheck(0x28, "I2C EEPROM send data")
        i2cStop();
        i2cCheck(0xf8, "I2C stop")
      }
      else {
        printf("\r\nNieznane polecenie\r\n");
      }
    }
    else {
      printf("\r\nNieznane polecenie\r\n");
    }
  }
}

