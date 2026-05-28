#include "spi.h"

void delay_us(int t) 	//delay in microseconds
{ 
		for(volatile int i=0; i<t*5; i++); 
}
void delay_ms(int t) 	//delay in milliseconds
{ 
		for(volatile int i=0; i<t*4000; i++); 
}
//SPI Master transmission
void SW_SPI_Write(uint8_t data) 
{
    for(int i=0; i<8; i++) 
		{
        SCK_L;				// Pull Clock Low to prepare data setup
        if(data & 0x80) 
				{
					MOSI_H; 		// Set MOSI line based on the Most Significant Bit
				}
				else 
				{
					MOSI_L;
				}
        delay_us(1); 	// Small delay for signal stabilization
        SCK_H; 				//Pull Clock High to trigger OLED data sampling (Rising Edge) 
        delay_us(1);
        data <<= 1;		//Shift data left to process the next bit
    }
}
