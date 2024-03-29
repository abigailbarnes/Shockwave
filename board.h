#ifndef BOARD_H
#define BOARD_H

#include "pos.h"


enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;

enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;


board* board_new(unsigned int width, unsigned int height, enum type type);

void board_free(board* b);

void label(unsigned int rc);

void board_show(board* b);

cell board_get(board* b, pos p);

void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */