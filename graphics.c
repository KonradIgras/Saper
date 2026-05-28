#include "graphics.h"

// BACKGROUND (COVERED/OPEN) 
void DrawBombArea(int x, int y, int color) 
	{
    for(int yy = 0; yy < 8; yy++) 
		{
        for(int xx = 0; xx < 8; xx++) 
				{
            if((xx == 0 || xx == 7 || yy == 0 || yy == 7) && color == 1) 
						{
                DrawPixel(x + xx, y + yy, 1);
            } 
						else 
						{
                DrawPixel(x + xx, y + yy, 0);
            }
        }
    }
}

// 1 
void Draw1(int x, int y) 
{
    DrawBombArea(x, y, 0); 
    for(int i = 1; i <= 6; i++) 
		{
				DrawPixel(x + 4, y + i, 1);
		}
    DrawPixel(x + 3, y + 2, 1); 
    DrawPixel(x + 2, y + 3, 1);
    DrawPixel(x + 3, y + 6, 1); 
    DrawPixel(x + 5, y + 6, 1);
}

// 2 
void Draw2(int x, int y) 
{
    DrawBombArea(x, y, 0);
    for(int i = 2, n = 5; i <= 5; i++, n--) 
		{ 
        DrawPixel(x + i, y + 6, 1); 
        DrawPixel(x + i, y + n, 1); 
    }
    DrawPixel(x + 2, y + 2, 1); 
    DrawPixel(x + 3, y + 1, 1); 
    DrawPixel(x + 4, y + 1, 1);
}

// 3 
void Draw3(int x, int y)
{
  DrawBombArea(x ,y ,0);
	for(int i = 2; i <= 6; i++)
	{
		if(i != 4)
		{
			DrawPixel(x + 5, y + i, 1);
		}
	}
	DrawPixel(x + 4, y + 4, 1);
	DrawPixel(x + 2, y + 2, 1);
	DrawPixel(x + 2, y + 6, 1);
	for(int i = 1; i <= 7; i+=6)
	{
		for(int n = 3; n <= 4; n++)
		{
			DrawPixel(x + n, y + i, 1);
		}
	}
}
// 4 
void Draw4(int x, int y)
{
    DrawBombArea(x, y, 0);
    for(int i = 1; i <= 5; i++)
    {
        DrawPixel(x + i, y + 4, 1);
        DrawPixel(x + 4, y + i, 1);
    }
    DrawPixel(x+4,y+6,1);
    for(int i = 1, j = 3; i <= 3; i++,j--)
    {
        DrawPixel(x + i, y + j, 1);
    }
}
// 5 
void Draw5(int x, int y)
{
    DrawBombArea(x,y,0);
    for(int i = 2; i <= 5; i++)
    {
        DrawPixel(x + i, y + 1, 1);
        if(i <= 4)
        {
            DrawPixel(x + i, y + 3, 1);
            DrawPixel(x + i, y + 6, 1);
        }
    }
    DrawPixel(x + 2, y + 2, 1);
    DrawPixel(x + 5, y + 4, 1);
    DrawPixel(x + 5, y + 5, 1);
}
// 6
void Draw6(int x, int y)
{
    DrawBombArea(x, y, 0);
    for(int i = 2; i <= 6; i++)
    {
        DrawPixel(x + 2, y + i, 1);
    }
    for(int i = 3; i <= 4; i++)
    {
        for(int j = 7; j >= 1; j-=3)
        {
            DrawPixel(x + i, y + j, 1);
        }
    }
    DrawPixel(x + 5, y + 2, 1);
    DrawPixel(x + 5, y + 5, 1);
    DrawPixel(x + 5, y + 6, 1);
}
// 7
void Draw7(int x, int y)
{
    DrawBombArea(x, y, 0);
    for(int i = 2; i <= 5; i++)
    {
        DrawPixel(x + i, y + 1, 1);
    }
    for(int i = 4; i <= 6; i++)
    {
        DrawPixel(x + 3, y + i, 1);
    }
    DrawPixel(x + 4, y + 3, 1);
    DrawPixel(x + 5, y + 2, 1);
}
// 8 
void Draw8(int x, int y)
{
    DrawBombArea(x, y, 0);
    Draw3(x, y);
    DrawPixel(x + 2, y + 3, 1);
    DrawPixel(x + 3, y + 4, 1);
    DrawPixel(x + 2, y + 5, 1);
}

// DRAW BOMB 	
void DrawBomb(int x, int y) 
{
    for(int i = 1; i <= 6; i++) 
		{
        for(int n = 1; n <= 6; n++) 
				{
            if((i == 1 && n == 1) || (i == 6 && n == 6) || (i == 1 && n == 6) || (i == 6 && n == 1)) 
						{
                DrawPixel(x + i, y + n, 1);
            }
        }
    }
    for(int i = 2; i <= 5; i++) 
		{
        for(int n = 2; n <= 5; n++) 
				{
            if(!((i == 2 && n == 2) || (i == 5 && n == 5) || (i == 2 && n == 5) || (i == 5 && n == 2))) 
						{
                DrawPixel(x + i, y + n, 1);
            }
        }
    }
}

// DRAW FLAG	 
void DrawFlag(int x, int y) 
{
    Draw1(x, y);
    for(int i = 1; i <= 3; i++) 
		{
			DrawPixel(x + i, y + 4, 1);
		}
    DrawPixel(x + 3, y + 3, 1);
    DrawPixel(x + 2, y + 6, 1); 
    DrawPixel(x + 6, y + 6, 1);
		DrawPixel(x + 1, y + 2, 1);
		DrawPixel(x + 1, y + 3, 1);
		DrawPixel(x + 2, y + 2, 1);
}

// DRAW CURSOR 
void DrawMouse(MouseData *m)
{
		if((m->left == 1)||(m->right == 1))
		{
			for(int i = -1; i <= 1; i++)
			{
				for(int j = -1; j <= 1; j++)
				{
					DrawPixel((m->x)/8 + i, (m->y)/8 + j, 1);
				}
			}
		}
		else
		{
			DrawPixel((m->x) / 8, (m->y) / 8, 1);
		}
}

