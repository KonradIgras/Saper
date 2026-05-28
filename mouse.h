#ifndef MOUSE_H
#define MOUSE_H

#include "MKL05Z4.h"

#define PS2_CLK_PORT   PTB
#define PS2_CLK_PIN    3
#define PS2_DATA_PORT  PTB
#define PS2_DATA_PIN   4

typedef struct 
{
		int16_t x;
		int16_t y;
	
		uint8_t left;
    uint8_t right;
    uint8_t middle;
} MouseData;

extern MouseData mouse;
extern int click[2];

void PS2_CLK_LOW(void);
void PS2_CLK_HIGH(void);
void PS2_DATA_LOW(void);
void PS2_DATA_HIGH(void);
void PS2_Init(void);
void waitForClockLow(void);
void waitForClockHigh(void);
void PS2_writeByte(uint8_t data);
uint8_t PS2_readByte(void);
void Decode(uint8_t byte1, uint8_t byte2, uint8_t byte3, MouseData *out);
void Mouse_Update(MouseData *m);
int Clicked(MouseData *m);

#endif
