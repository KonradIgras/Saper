#ifndef SPI_H
#define SPI_H

#include "MKL05Z4.h"
#include <stdint.h> 

#define MOSI_PIN 0
#define SCK_PIN  1

#define MOSI_H   PTB->PSOR = (1 << MOSI_PIN)
#define MOSI_L   PTB->PCOR = (1 << MOSI_PIN)
#define SCK_H    PTB->PSOR = (1 << SCK_PIN)
#define SCK_L    PTB->PCOR = (1 << SCK_PIN)

void delay_us(int t);
void delay_ms(int t);
void SW_SPI_Write(uint8_t data);

#endif
