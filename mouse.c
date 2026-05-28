#include "mouse.h"

MouseData mouse = {
	.x = 512,
	.y = 256
};
int click[2];

// LOGIC STATES 
// LOW CLK 
void PS2_CLK_LOW(void)					 
{
    PS2_CLK_PORT->PCOR = (1 << PS2_CLK_PIN);
    PS2_CLK_PORT->PDDR |= (1 << PS2_CLK_PIN);
}
// HIGH CLK
void PS2_CLK_HIGH(void)					
{
    PS2_CLK_PORT->PDDR &= ~(1 << PS2_CLK_PIN);
}
// LOW DATA
void PS2_DATA_LOW(void)					
{
    PS2_DATA_PORT->PCOR = (1 << PS2_DATA_PIN);
    PS2_DATA_PORT->PDDR |= (1 << PS2_DATA_PIN);
}
// HIGH DATA 
void PS2_DATA_HIGH(void)					
{
    PS2_DATA_PORT->PDDR &= ~(1 << PS2_DATA_PIN);
}

// INITIALIZATION PS2
void PS2_Init(void)									
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    PORTB->PCR[PS2_CLK_PIN] =			//ACTIVE CLK PORT
        PORT_PCR_MUX(1) |
        PORT_PCR_PE_MASK |
        PORT_PCR_PS_MASK;

    PORTB->PCR[PS2_DATA_PIN] =		//ACTIVE DATA PORT
        PORT_PCR_MUX(1) |
        PORT_PCR_PE_MASK |
        PORT_PCR_PS_MASK;

    PS2_CLK_HIGH();								//SET HIGH
    PS2_DATA_HIGH();							//SET HIGH
}

// FALLING CLK 
void waitForClockLow(void)	
{
    while (PS2_CLK_PORT->PDIR & (1 << PS2_CLK_PIN));
}
// RISING CLK
void waitForClockHigh(void)		
{
    while (!(PS2_CLK_PORT->PDIR & (1 << PS2_CLK_PIN)));
}
// SEND BYTE
void PS2_writeByte(uint8_t data)	
{
    uint8_t parity = 1;

		PS2_DATA_LOW();						//START BIT
    waitForClockLow();
    PS2_DATA_LOW();						
    waitForClockHigh();
	
    for (uint8_t i = 0; i < 8; i++)	//8 BIT DATA
    {
        uint8_t bit = (data >> i) & 1;	
        if (bit) 
				{
					PS2_DATA_HIGH();
        }
				else     
				{
					PS2_DATA_LOW();
				}
				
        waitForClockLow();
				waitForClockHigh();

        parity ^= bit;
    }

    PS2_DATA_HIGH();						//PARITY
    waitForClockLow();
    waitForClockHigh();
					

    waitForClockLow();					//STOP
    waitForClockHigh();
}

// READ BYTE 
uint8_t PS2_readByte(void)					
{
    uint8_t data = 0;

		waitForClockHigh();				//START BIT
		waitForClockLow();
    waitForClockHigh();				

    for (uint8_t i = 0; i < 8; i++)	//8 BIT DATA
    {
        waitForClockLow();
        if (PS2_DATA_PORT->PDIR & (1 << PS2_DATA_PIN))
				{
            data |= (1 << i);
				}
        waitForClockHigh();
    }

    for (int i = 0; i < 2; i++)			//PARITY and STOP
    {
        waitForClockLow();
				waitForClockHigh();
    }

    return data;
}
// MOUSE DATA DECODING
void Decode(uint8_t byte1, uint8_t byte2, uint8_t byte3, MouseData *out)
{

		out->left   =  byte1 & 1;
    out->right  = (byte1 >> 1) & 1;
    out->middle = (byte1 >> 2) & 1;
	
    out->x += (int8_t)byte2;
    out->y -= (int8_t)byte3;
	
		
}
// GETING DATA FROM MOUSE
void Mouse_Update(MouseData *m)
{
    uint8_t ack;
    uint8_t b1, b2, b3;

    PS2_writeByte(0xEB);		//ask for data

    ack = PS2_readByte();   //0xFA
    b1  = PS2_readByte();   //buttons
    b2  = PS2_readByte();   //dx
    b3  = PS2_readByte();   //dy

    Decode(b1, b2, b3, m);

    if(m->x>1023)						//limits
		{
			m->x = 1023;
		}
		else if(m->x<0)
		{
			m->x = 0;
		}
		if(m->y>511)
		{
			m->y = 511;
		}
		else if(m->y<0)
		{
			m->y = 0;
		}
		if(m->left == 0)
		{
				click[0] = 0;
		}
		if(m->right == 0)
		{
				click[1] = 0;
		}
}
// IS MB CLICKED
int Clicked(MouseData *m)
{
		if (m->middle == 1)			//left and right click
		{
				return 3;
		}
		else if((click[0] == 0) && (m->left == 1))	//left click
		{
				click[0] = 1;
				return 1;
		}
		else if((click[1] == 0) && (m->right == 1))	//right click
		{
				click[1] = 1;
				return 2;
		}
		else
		{
				return 0;
		}
}

