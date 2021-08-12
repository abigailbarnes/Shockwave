#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* main : run the evidence functions above */
int main(int argc, char *argv[])
{
    int i = 1; // 0 would be the name of the program

    int width;
    int height;
    int run;
    enum type boardtype;

    int widthcounter = 0;
    int heightcounter = 0;
    int runcounter = 0;
    int typecounter = 0;

    while(i < argc)
    {
    	if(strcmp(argv[i], "-w") == 0)
    	{
    		width = atoi(argv[i + 1]);
    		widthcounter++;
    	}
    	else if(strcmp(argv[i], "-h") == 0)
    	{
    		height = atoi(argv[i + 1]);
    		heightcounter++;
    	}
    	else if(strcmp(argv[i], "-r") == 0)
    	{
    		run = atoi(argv[i + 1]);
    		runcounter++;
    	}
    	else if(strcmp(argv[i], "-m") == 0)
    	{
    		boardtype = MATRIX;
    		typecounter++;
    		i--;
    	}
    	else if(strcmp(argv[i], "-b") == 0)
    	{
    		boardtype = BITS;
    		typecounter++;
    		i--;
    	}
    	i += 2;
    }

    if(runcounter == 0 || heightcounter == 0 || widthcounter == 0 || typecounter == 0)
    {
    	fprintf(stderr, "cannot create board, given inputs must be w, h, run");
    }





    char ch1;
    char ch2;

    game* g = new_game(run, width, height, MATRIX);


    while(game_outcome(g) == IN_PROGRESS)
    {
    	board_show(g->b);

    	if(celltype(g) == BLACK)
    	{
    		printf("Black:");
    	}
    	else
    	{
    		printf("White:");
    	}

    	scanf("%c%c%*c", &ch1, &ch2);

    	if(ch1 == '!') //indicating a shockwave
    	{
    		if(ch2 == 'N')
    		{
    			shockwave(g, N);
    		}
    		else if(ch2 == 'E')
    		{
    			shockwave(g, E);
    		}
    		else if(ch2 == 'S')
    		{
    			shockwave(g, S);
    		}
    		else if(ch2 == 'W')
    		{
    			shockwave(g, W);
    		}
    		switch_player(g);
    	}
    	else //indicating a position to be played, parse to int using ASCII
    	{
   			int rowascii = ch1;
   			int colascii = ch2;

   			int row = 0;
   			int col = 0;

   			if(rowascii >= 49 && rowascii <= 57)
   			{
   				row = rowascii - 48;
   			}
   			else if(rowascii >= 65 && rowascii <=90)
   			{
   				row = rowascii - 55;
   			}
   			else if(rowascii >= 97 && rowascii <= 122)
   			{
   				row = rowascii - 61;
   			}



   			if(colascii >= 49 && colascii <= 57)
   			{
   				col = colascii - 48;
   			}
   			else if(colascii >= 65 && colascii <=90)
   			{
   				col = colascii - 55;
   			}
   			else if(colascii >= 97 && colascii <= 122)
   			{
   				col = colascii - 61;
   			}



   			pos p = make_pos(row, col);

    		place_piece(g, p);
    	}

    	if(game_outcome(g) == BLACK_WIN)
    	{
    		printf("Black Won!\n");
    		board_show(g->b);
    	}
    	else if(game_outcome(g) == WHITE_WIN)
    	{
    		printf("White Won!\n");
    		board_show(g->b);
    	}
    	else if(game_outcome(g) == DRAW)
    	{
    		printf("Draw: No @inners :(\n");
    		board_show(g->b);
    	}

    }

    return 0;
}