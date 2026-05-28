#ifndef OLED_H
#define OLED_H

#include "spi.h"
#include <stdint.h>

#define RES_PIN  5  // PTB
#define CS_PIN   5  // PTA
#define DC_PIN   12 // PTA

#define RES_H    PTB->PSOR = (1 << RES_PIN)
#define RES_L    PTB->PCOR = (1 << RES_PIN)
#define CS_H     PTA->PSOR = (1 << CS_PIN)
#define CS_L     PTA->PCOR = (1 << CS_PIN)
#define DC_H     PTA->PSOR = (1 << DC_PIN)
#define DC_L     PTA->PCOR = (1 << DC_PIN)

extern uint8_t buffer[1024];

void OLED_Init(void);
void OLED_Cmd(uint8_t cmd); 
void OLED_Display(void);
void DrawPixel(int x, int y, int color);
void OLED_ClearBuffer(void);

#endif
