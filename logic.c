#include "logic.h"

int board[ROWS][COLS] = {0};
int board1[ROWS][COLS];
int xy[2];

// CLEARING BOARD 
void ClearBoard(void)
{
		for (int i = 0; i < ROWS; i++) 
		{
        for (int j = 0; j < COLS; j++) board[i][j] = 0;
    }
		for (int i = 0; i < ROWS; i++) 
		{
        for (int j = 0; j < COLS; j++) board1[i][j] = COVERED;
    }
}

// MAKING RANDOM BOARD 
void MakeBoard(int mode) 
{
    int placed = 0;
    while(placed < mode) 
		{
        int bx = MyRand() % (COLS - 2); 		//choosing place for bomb
        int by = MyRand() % (ROWS - 2); 
        
        if (board[by + 1][bx + 1] != BOMB) 	//if not ocupied place bomb
				{
						board[by + 1][bx + 1] = BOMB;
            placed++;												//count how many bombs
        }
    }

    if (board[xy[1] + 1][xy[0] + 1] == BOMB) //if mouse click at the start on bomb, change place of bomb
		{
        board[xy[1] + 1][xy[0] + 1] = 0;
			
        for (int i = 1; i < ROWS - 1; i++) 
				{
            for (int j = 1; j < COLS - 1; j++) 
						{
                if (board[i][j] != BOMB && (i != xy[1] + 1 || j != xy[0] + 1)) 
								{
                    board[i][j] = BOMB; 
                    i = ROWS; break;
                }
            }
        }
    }
		int bombs_nearby = 0;
		
    for (int i = 1; i < ROWS - 1; i++) 			//count bombs around 
		{
        for (int j = 1; j < COLS - 1; j++) 
			{
					if (board[i][j] == BOMB) 
					{
							continue;
					}
					else
					{
						bombs_nearby = 0;
						for (int yy = -1; yy <= 1; yy++)
						{
								for (int xx = -1; xx <= 1; xx++)
								{
										if (board[i + yy][j + xx] == BOMB) 
										{
										bombs_nearby++;
										}
								}
						}	
						board[i][j] = bombs_nearby;
					}
			}
    }
}

// RENDERING ON SCREEN
void RenderGame(void) 
{
		int x_pixel; 
    int y_pixel;
    for(int i = 1; i < ROWS - 1; i++) 
		{
        for(int j = 1; j < COLS - 1; j++) 
				{
            x_pixel = (j - 1) * 8; 				//scaling
            y_pixel = (i - 1) * 8;

            if(board1[i][j] == COVERED) 
						{
                DrawBombArea(x_pixel, y_pixel, 1);
            }
            else if(board1[i][j] == FLAGGED) 
						{
                DrawFlag(x_pixel, y_pixel);
            }
            else 
						{ 
                if(board[i][j] == BOMB) 						//Map reveal
								{
                    DrawBomb(x_pixel, y_pixel);
										for (int k = 0; k < ROWS; k++) 
										{
												for (int l = 0; l < COLS; l++) board1[k][l] = OPEN;
										}
                }
                else if(board[i][j] == 1) 
								{
                    Draw1(x_pixel, y_pixel);
                }
                else if(board[i][j] == 2) 
								{
                    Draw2(x_pixel, y_pixel);
                }
								else if(board[i][j] == 3) 
								{
                    Draw3(x_pixel, y_pixel);
                }
                else if(board[i][j] == 4) 
								{
                    Draw4(x_pixel, y_pixel);
                }
								else if(board[i][j] == 5) 
								{
                    Draw5(x_pixel, y_pixel);
                }
                else if(board[i][j] == 6) 
								{
                    Draw6(x_pixel, y_pixel);
                }
								else if(board[i][j] == 7) 
								{
                    Draw7(x_pixel, y_pixel);
                }
                else if(board[i][j] == 8) 
								{
                    Draw8(x_pixel, y_pixel);
                }
                else 
								{
										DrawBombArea(x_pixel, y_pixel, 0);
                }
            
						if(board[i][j] == 0)											//reveal all empty squares around
						{
								for(int a = -1; a<=1; a++)
								{
										for(int b = -1; b<=1; b++)
										{
												if(board[i + b][j + a] != BOMB && board1[i + b][j + a] != FLAGGED)
												{
														board1[i + b][j + a] = OPEN;
												}
										}
								}					
						}
					}
        }
    }
		DrawMouse(&mouse);
    OLED_Display(); 
}
// SCALING MOUSE DATA
void Scaling(void)
{
	xy[0] = xy[0]/64;
	xy[1] = xy[1]/64;
}

// REVEAL OR FLAG 
void ChangeCoverage(int change)
{
		if((change == 1) && (board1[xy[1]+1][xy[0]+1] == COVERED))
		{
				board1[xy[1]+1][xy[0]+1] = OPEN;																//uncover
		}
		else if((change == 2) && (board1[xy[1]+1][xy[0]+1] == COVERED))
		{
				board1[xy[1]+1][xy[0]+1] = FLAGGED;															//flag
		}
		else if((change == 2) && (board1[xy[1]+1][xy[0]+1] == FLAGGED))
		{
				board1[xy[1]+1][xy[0]+1] = COVERED;															//cover
		}
		else
		{}
}
