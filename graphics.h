#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "oled.h" 
#include "mouse.h"

void DrawBombArea(int x, int y, int color);
void Draw1(int x, int y);
void Draw2(int x, int y);
void Draw3(int x, int y);
void Draw4(int x, int y);
void Draw5(int x, int y);
void Draw6(int x, int y);
void Draw7(int x, int y);
void Draw8(int x, int y);
void DrawBomb(int x, int y);
void DrawFlag(int x, int y);
void DrawMouse(MouseData *m);

#endif
