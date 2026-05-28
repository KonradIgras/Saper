#ifndef LOGIC_H
#define LOGIC_H

#include <stdint.h>

#include "graphics.h"
#include "random.h" 

#define EASY 10
#define MEDIUM 20
#define HARD 30
#define ROWS 10
#define COLS 18
#define BOMB 9
#define COVERED 1
#define FLAGGED 2
#define OPEN 0


extern int board[ROWS][COLS];
extern int board1[ROWS][COLS];
extern int xy[2];

void ClearBoard(void);
void MakeBoard(int mode); 
void RenderGame(void);
void Scaling(void);
void ChangeCoverage(int change);

#endif
