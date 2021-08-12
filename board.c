#include <stdio.h>
#include <stdlib.h> 
#include "board.h" 

/* board_new : creating a new, empty board */
board* board_new(unsigned int width, unsigned int height, enum type type)
{
	unsigned int c;
	unsigned int r;
	unsigned int area;

	unsigned int index;

	if(type == BITS)
	{
		unsigned int vars = 0;
		area = width * height;
		if((area % 32) == 0)
		{
			vars = area/32;
			index = area/32;
		}
		else
		{
			vars = (area/32) + 1;
			index = (area/32) + 1;
		}

		unsigned int* arr;
		arr = (unsigned int*)malloc(sizeof(unsigned int) * vars);

		while(index >= 0)
		{
			arr[index] = 0;
			index--;
		}

		board* b = (board*)malloc(sizeof(board));
		b->width = width;
		b->height = height;
		b->type = BITS;
		b->u.bits = arr;
		return b;	
	}
	else
	{
		cell** mat = (cell**)malloc(sizeof(cell*) * height);

		if(mat == NULL)
		{
			fprintf(stderr, "matrix not allocated");
			exit(1);
		}

		for(r = 0; r < height; r++)
		{
			mat[r] = (cell*)malloc(sizeof(cell) * width);

			if(mat[r] == NULL)
			{
				fprintf(stderr, "matrix row not allocated");
				exit(1);
			}
			for(c = 0; c < width; c++)
			{
				mat[r][c] = EMPTY;
			}
		}
		board_rep br = {mat};
			board* b = (board*)malloc(sizeof(board));
			
			if(b == NULL)
			{
				fprintf(stderr, "board not allocated");
				exit(1);
			}

			b->width = width;
			b->height = height;
			b->type = MATRIX;
			b->u = br;
			return b;	
	}
	
}

/* board_free : freeing the inputted board */
void board_free(board* b)
{
	for(unsigned int i = 0; i < b->height; i++)
	{
		free((b->u.matrix)[i]);
	}

	free(b->u.matrix);
	free(b);

	return;
}


/* label : creating the labels for the board*/
void label(unsigned int rc)
{
	char letter;
	if(rc < 10)
	{
		printf("%u", rc);
	}
	else if(rc < 36)
	{
		letter = rc + 55;
		printf("%c", letter);
	}
	else if(rc < 62)
	{
		letter = rc + 61;
		printf("%c", letter);
	}
	else
	{
		printf("?");
	}
	return;
}


/* board_show : printing the board as it is*/
void board_show(board* b)
{
	unsigned int r;
	unsigned int c;
	//print the labels for width and height
	//printing label across top
	printf("  ");
	for(c = 0; c < b->width; c++)
	{
		label(c);
	}

	printf("\n");

	for(r = 0; r < b->height; r++)
	{
		label(r);
		printf(" ");
		for(c = 0; c < b->width; c++)
		{
			pos p = make_pos(r, c);
			if(board_get(b, p) == BLACK)
			{
				printf("*");
			}
			else if(board_get(b, p) == WHITE)
			{
				printf("o");
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}	
	return;
}


/* board_get : retrieve cell in the board */
cell board_get(board* b, pos p)
{
	if(b->type == BITS)
	{
		unsigned int bitplacement = (p.r * b->height) + p.c; // bit number

		bitplacement *= 2;

		unsigned int index = bitplacement/32; //index to get from arr

		

		unsigned int tempbit = b->u.bits[index];

		//want to shift to the right according to bitplacement

		tempbit = tempbit >> bitplacement;

		if((tempbit & 1) == 1)
		{
			return BLACK;
		}
		else if ((tempbit & 2) == 2)
		{
			return WHITE;
		}
		else
		{
			return EMPTY;
		}
	}
	else
	{
		cell cl = b->u.matrix[p.r][p.c];
		return cl;
	}
}

/* board_set : set a cell in the board */
void board_set(board* b, pos p, cell c)
{

		if(b->type == MATRIX)
		{
			b->u.matrix[p.r][p.c] = c;
		}
		else
		{	
			unsigned int bitplacement = (p.r * b->height) + p.c; // bit number
			bitplacement *= 2;

			unsigned int index = bitplacement/32; //index to get from arr

			unsigned int originalbit = b->u.bits[index];

			originalbit = originalbit << (bitplacement - 32);
			originalbit = originalbit >> (bitplacement - 32);

			unsigned int tempbit = b->u.bits[index];


			tempbit = tempbit >> bitplacement;
			tempbit = tempbit >> 2;
			tempbit = tempbit << 2;

			if(c == EMPTY)
			{
				tempbit = tempbit & 0;
				tempbit = tempbit << bitplacement;
				tempbit = tempbit | originalbit;
				b->u.bits[index] = tempbit;
			}
			else if(c == BLACK)
			{
				tempbit = tempbit & 1;
				tempbit = tempbit << bitplacement;
				tempbit = tempbit | originalbit;
				b->u.bits[index] = tempbit;
			}
			else
			{
				tempbit = tempbit & 2;
				tempbit = tempbit << bitplacement;
				tempbit = tempbit | originalbit;
				b->u.bits[index] = tempbit;
			}
		}	
}