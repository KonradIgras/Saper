#ifndef RANDOM_H
#define RANDOM_H

#include "MKL05Z4.h"
#include <stdint.h>

extern unsigned int random_state;

void ADC_Init(void);
unsigned short ADC_Read(unsigned char port);
unsigned int GetNoise(void);
void MyRandom(unsigned int seed);
unsigned int MyRand(void);

#endif
