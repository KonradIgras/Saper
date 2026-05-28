
#include "MKL05Z4.h"
#include <stdio.h>
#include "mouse.h"
#include "spi.h"
#include "random.h"
#include "oled.h"
#include "logic.h"
#include "graphics.h"

// MAIN
int main(void)
{
		int START = 1;
		int PLAY = 0;
		int helper = 0;
    PS2_Init();
		OLED_Init();
    ADC_Init(); 
	
	while(1)
	{
// START GAME
			ClearBoard();
			while(START == 1)
			{
				OLED_ClearBuffer();
				RenderGame();
				Mouse_Update(&mouse);	//get data from mouse
				DrawMouse(&mouse);		//print mouse point
				xy[1] = mouse.y;
				xy[0] = mouse.x;
				Scaling();						//scaling mouse data
				helper = Clicked(&mouse);
				ChangeCoverage(helper);
				OLED_Display();
				if(helper == 1)				//wait for first click to not generate bomb on click
				{
						PLAY = 1;
						START = 0;
				}
			}
			
			OLED_ClearBuffer();
			MyRandom(GetNoise());		//randomize bomb
			MakeBoard(EASY);  		//mode 
			RenderGame();						//Draw1 board
			OLED_Display();					//display
// PLAY TIME
			while(PLAY == 1)
			{
				OLED_ClearBuffer();
				RenderGame();			
				Mouse_Update(&mouse);
				DrawMouse(&mouse);
				xy[1] = mouse.y;
				xy[0] = mouse.x;
				Scaling();
				ChangeCoverage(Clicked(&mouse));	//show what under
				OLED_Display();
				if(Clicked(&mouse) == 3)					//reset
				{
					START = 1;
					PLAY = 0;
				}
			}
		}
	}
