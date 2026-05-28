#include "random.h"
#include "spi.h"

unsigned int random_state = 1; 

// INITIALIZATION ADC
void ADC_Init(void) 
{	// Enable clock for ADC0 module 
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; 
    ADC0->CFG1 = ADC_CFG1_ADIV(1) | ADC_CFG1_MODE(2) | ADC_CFG1_ADICLK(0);
    ADC0->SC3 = 0;	// Single conversion mode
}

// GET ANALOG VALUE 
unsigned short ADC_Read(unsigned char port) 
{
    ADC0->SC1[0] = port; 	// Start conversion
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)); 	//Wait for Conversion Complete (COCO) flag 
    return (unsigned short)ADC0->R[0];	// Return the 10-bit digital result
}

// SEED 
unsigned int GetNoise(void) 
{
		// Collects 32 bits of thermal noise from a floating pin
    unsigned int seed = 0;
    for(int i = 0; i < 32; i++) 
		{
        seed = (seed << 1) | (ADC_Read(3) & 1);	// Shift left and capture the Least Significant Bit (LSB) of ADC channel 3
        delay_us(100); 
    }
    return seed;
}

// GENERATOR 
void MyRandom(unsigned int seed) 
{ 
    random_state = seed; 
}

unsigned int MyRand(void) 
{
		// LCG parameters
		random_state = 1103515245 * random_state + 12345;
		return (random_state / 65536) % 32768;
}
