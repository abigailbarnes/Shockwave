#include <stdio.h>
#include <stdlib.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


/* new_game : creating a new game with an empty board */
game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type)
	    {
	    	if(type == BITS)
	    	{
	    		fprintf(stderr, "type cannot be BITS");
	    		exit(1);
	   		}

	   		if((run > width) || (run > height))
	   		{
	   			fprintf(stderr, "run value not within bounds");
	   			exit(1);
	   		}

	    	game* g = (game*)malloc(sizeof(game));
	    	if(g == NULL)
	    	{
	    		fprintf(stderr, "game not allocated");
	    		exit(1);
	    	}

	   		 board* b = board_new(width, height, type);

	    	g->run = run;
	    	g->b = b;
	    	g->player = BLACKS_TURN;

	    	return g;
	    }

/* game_free : frees the game */
void game_free(game* g)
{
	board_free(g->b);
	free(g);
	return;
}


/* place_piece : place the piece on the board in specific position */
int place_piece(game* g, pos p)
{
	if(board_get(g->b, p) == EMPTY)
	{
		if(g->player == BLACKS_TURN)
		{
			board_set(g->b, p, BLACK);
			g->player = WHITES_TURN;
		}
		else
		{
			board_set(g->b, p, WHITE);
			g->player = BLACKS_TURN;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

/* switch_player : switch the player who's turn it is */
void switch_player(game* g)
{
	if(g->player == BLACKS_TURN)
	{
		g->player = WHITES_TURN;
	}
	else
	{
		g->player = BLACKS_TURN;
	}
}

/* opposite : returns the opposide of the current player
			  returns the player who's turn it IS NOT */
cell opposite(game* g)
{
	if(g->player == BLACKS_TURN)
	{
		return WHITE;
	}
	else
	{
		return BLACK;
	}
}


/* celltype : returns the type of cell associated 
with the turn of the player who's turn it is*/
cell celltype(game* g)
{
	if(g->player == BLACKS_TURN)
	{
		return BLACK;
	}
	else
	{
		return WHITE;
	}
}

/* shockwave_helper_north : shockwaves board north */
void shockwave_helper_north(game* g)
{
	unsigned int counter = 0;
	unsigned int upperbound = g->b->height;

	unsigned int c;
	int r;
	int i;

	pos p;
	pos update;

	for(c = 0; c < g->b->width; c++)
	{
		//printf("column check :%u\n", c);
		for(r = (upperbound - 1); r >= 0; r--)
		{
			p = make_pos(r, c);
			if(board_get(g->b, p) == celltype(g))
			{
				counter++;
				board_set(g->b, p, EMPTY);
			}
			else if((board_get(g->b, p) ==  opposite(g)))
			{
				i = 1;
				while(i <= counter)
				{
					update = make_pos((r + i), c);
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			else if(r == 0)
			{
				i = 0;
				while(i < counter)
				{
					update = make_pos((r + i), c);
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			
		}
	}
}


/* shockwave_helper_south : shockwaves board south */
void shockwave_helper_south(game* g)
{
	unsigned int counter = 0;
	unsigned int upperbound = g->b->height;

	unsigned int c;
	int r;
	int i;

	pos p;
	pos update;

	for(c = 0; c < g->b->width; c++)
	{
		for(r = 0; r < upperbound; r++)
		{
			
			p = make_pos(r, c);
			if(board_get(g->b, p) == celltype(g))
			{
				counter++;
				board_set(g->b, p, EMPTY);
			} 
			else if((board_get(g->b, p) ==  opposite(g)))
			{
				i = 1;
				while(i <= counter)
				{
					printf("in the while loop");
					update = make_pos((r - i), c);
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			else if(r == upperbound - 1)
			{
				i = 0;
				while(i < counter)
				{
					update = make_pos((r - i), c);
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			
		}
	}
}


/* shockwave_helper_east : shockwaves board east */
void shockwave_helper_east(game* g)
{
	unsigned int counter = 0;
	unsigned int upperbound = g->b->height;

	unsigned int c;
	int r;
	int i;

	pos p;
	pos update;

	for(r = 0; r < upperbound; r++)
	{
		for(c = 0; c < g->b->width; c++)
		{
			p = make_pos(r, c);
			if(board_get(g->b, p) == celltype(g))
			{
				counter++;
				board_set(g->b, p, EMPTY);
			} 
			else if((board_get(g->b, p) ==  opposite(g)))
			{
				i = 1;
				while(i <= counter)
				{
					update = make_pos(r, (c - i));
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			else if(c == g->b->width - 1)
			{
				i = 0;
				while(i < counter)
				{
					update = make_pos(r, (c - i));
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
		}
	}
}


/* shockwave_helper_west : shockwaves board west */
void shockwave_helper_west(game* g)
{
	unsigned int counter = 0;
	unsigned int upperbound = g->b->height;
	unsigned int rightmost = g->b->width;

	unsigned int c;
	int r;
	int i;

	pos p;
	pos update;

	for(r = 0; r < upperbound; r++)
	{
		for(c = rightmost; c > 0; c--)
		{
			p = make_pos(r, c - 1);
			if(board_get(g->b, p) == celltype(g))
			{
				counter++;
				board_set(g->b, p, EMPTY);
			} 
			else if((board_get(g->b, p) ==  opposite(g)))
			{
				i = 1;
				while(i <= counter)
				{
					update = make_pos(r, (c - 1+ i));
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
			else if(c - 1 == 0)
			{
				i = 0;
				while(i < counter)
				{
					update = make_pos(r, (c - 1 + i));
					board_set(g->b, update, celltype(g));
					i++;
				}
				
				counter = 0;
				i = 0;
			}
		}
	}
}

/* shockwave : shockwaves the board according to inputted direction */
void shockwave(game* g, direction d)
{
	if(d == N)
	{
		shockwave_helper_north(g);
	}
	else if(d == S)
	{
		shockwave_helper_south(g);
	}
	else if(d == E)
	{
		shockwave_helper_east(g);
	}
	else if(d == W)
	{
		shockwave_helper_west(g);
	}
	
}

int vertical(game* g, pos p)
{
	int counter = 1;
	int row = p.r;
	cell original = board_get(g->b, p);
	int upperbound = g->b->height - 1;
	pos tempposition;


	//moving NORTH
	while(row != 0)
	{
		row -= 1;
		tempposition = make_pos(row, p.c);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}
	}

	//moving SOUTH
	row = p.r;
	while(row != upperbound)
	{
		row += 1;
		tempposition = make_pos(row, p.c);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}

	}
	return counter;
}

int horizontal(game* g, pos p)
{
	int counter = 1;
	int column = p.c;
	cell original = board_get(g->b, p);
	int upperbound = g->b->width - 1;
	pos tempposition;


	//moving WEST
	while(column != 0)
	{
		column -= 1;
		tempposition = make_pos(p.r, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}
	}

	//moving EAST
	column = p.c;
	while(column != upperbound)
	{
		column += 1;
		tempposition = make_pos(p.r, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}

	}
	return counter;
}

int diagonal_pos(game* g, pos p)
{
	int counter = 1;
	int column = p.c;
	int row = p.r;
	cell original = board_get(g->b, p);
	int rowbound = g->b->height - 1;
	int colbound = g->b->width - 1;
	pos tempposition;


	//moving NORTH EAST
	while(row != 0 && column != colbound)
	{
		column += 1;
		row -= 1;
		tempposition = make_pos(row, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}
	}

	//moving SOUTH WEST
	column = p.c;
	row = p.r;
	
	while(column != 0 && row != rowbound)
	{
		column -= 1;
		row += 1;
		tempposition = make_pos(row, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}

	}
	return counter;
}



int diagonal_neg(game* g, pos p)
{
	int counter = 1;
	int column = p.c;
	int row = p.r;
	cell original = board_get(g->b, p);
	int rowbound = g->b->height - 1;
	int colbound = g->b->width - 1;
	pos tempposition;


	//moving NORTH WEST
	while(row != 0 && column != 0)
	{
		column -= 1;
		row -= 1;
		tempposition = make_pos(row, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}
	}

	//moving SOUTH EAST
	column = p.c;
	row = p.r;
	
	while(column != colbound && row != rowbound)
	{
		column += 1;
		row += 1;
		tempposition = make_pos(row, column);
		if(board_get(g->b, tempposition) == original)
		{
			counter++;
		}
		else
		{
			break;
		}

	}
	return counter;
}


int check_all_directions(game* g, pos p)
{
	unsigned int win = g->run;

	if(vertical(g, p) == win)
	{
		return 1;
	}
	else if(horizontal(g, p) == win)
	{
		return 2;
	}
	else if(diagonal_pos(g, p) == win)
	{
		return 3;
	}
	else if(diagonal_neg(g, p) == win)
	{
		return 4;
	}
	else
	{
		return -1;
	}
}







/* game_outcome : determines the outcome of the game */
outcome game_outcome(game* g)
{

	unsigned int rowbound = g->b->height;
	unsigned int colbound = g->b->width;
	pos p;

	unsigned int emptycounter = 0;

	for(unsigned int r = 0; r < rowbound; r++)
	{
		for(unsigned int c = 0; c < colbound; c++)
		{
			p = make_pos(r, c);
			if(board_get(g->b, p) == EMPTY)
			{
				emptycounter++;
			}
			else if(check_all_directions(g, p) != -1)
			{
				if(board_get(g->b, p) == BLACK)
				{
					return BLACK_WIN;
				}
				else if(board_get(g->b, p) == WHITE)
				{
					return WHITE_WIN;
				}
			}
		}
	}

	if(emptycounter == 0)
	{
		return DRAW;
	}
	else
	{
		return IN_PROGRESS;
	}
}
