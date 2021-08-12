#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


enum direction {
    N, E, S, W
};

typedef enum direction direction;


struct game {
    unsigned int run;
    board* b;
    turn player;
};

typedef struct game game;


game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type);

void game_free(game* g);

int place_piece(game* g, pos p);

void switch_player(game* g);

void shockwave_helper_north(game* g);
void shockwave_helper_south(game* g);
void shockwave_helper_east(game* g);
void shockwave_helper_west(game* g);

cell celltype(game* g);

cell opposite(game* g);

void shockwave(game* g, direction d);

int vertical(game* g, pos p);
int horizontal(game* g, pos p);
int diagonal_pos(game* g, pos p);
int diagonal_neg(game* g, pos p);

outcome game_outcome(game* g);


#endif /* LOGIC_H */