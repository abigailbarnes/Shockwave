#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pos.h"
#include "board.h"
#include "logic.h"


/* POS TESTS */
/* evidence_pos : test pos function */
void evidence_pos()
{
    printf("*** testing pos\n");
    pos p1 = make_pos(1, 3);
    printf("- expecting 1: %u\n", p1.r);
    printf("- expecting 3: %u\n", p1.c);
    pos p2 = make_pos(4, 10);
    printf("- expecting 4: %u\n", p2.r);
    printf("- expecting 10: %u\n", p2.c);
    pos p3 = make_pos(4, 4);
    printf("- expecting 4: %u\n", p3.r);
    printf("- expecting 4: %u\n", p3.c);

    return;
}

/* evidence_label : test label function */
void evidence_label()
{
    printf("*** testing pos\n");
    printf("- expecting 2: ");
    label(1);
    printf("\n");
    printf("- expecting A: \n");
    label(11);
    printf("\n");
    printf("- expecting a: \n");
    label(36);
    printf("\n");
    printf("- expecting ?: \n");
    label(66);
    printf("\n");
    return;
}

/* evidence_board_show : test board_show function */
void evidence_board_show()
{
    printf("*** testing board_show\n");
    printf("- expecting board with 5 columns and 5 rows: \n");
    board* board1 = board_new(5, 5, MATRIX);
    board_show(board1);
    board_free(board1);
    printf("\n");

    printf("- expecting board with 10 columns and 10 rows: ");
    board* board2 = board_new(10, 10, MATRIX);
    board_show(board2);
    board_free(board2);

    printf("\n");

    printf("- expecting board with 5 columns and 6 rows: ");
    board* board3 = board_new(10, 40, MATRIX);
    board_show(board3);
    board_free(board3);
    printf("\n");
}


/* evidence_board_get_set : testing board_get and board_set functions */
void evidence_board_get_set()
{
    board* board1 = board_new(6, 6, MATRIX);

    pos p1 = make_pos(1, 1);
    pos p2 = make_pos(1, 3);
    pos p3 = make_pos(5, 5);

    board_set(board1, p2, BLACK);
    board_set(board1, p3, WHITE);

    board_show(board1);

    printf("*** testing board_get and board_set\n");
    printf("- expecting 0: %d\n", board_get(board1, p1));
    printf("- expecting 1 : %d\n", board_get(board1, p2));
    printf("- expecting 2 : %d\n", board_get(board1, p3));

    printf("\n\n\n");

    board_free(board1);
}


/* LOGIC TESTS */
/* evidence_play_piece : testing play_piece function */
void evidence_place_piece()
{
    printf("*** testing place_piece\n");
    game* g1 = new_game(3, 5, 5, MATRIX); 

    pos p1 = make_pos(1, 1);
    pos p2 = make_pos(2,2);
    pos p3 = make_pos(3,3);
    place_piece(g1, p1);
    place_piece(g1, p2);
    place_piece(g1, p3);

    board_show(g1->b);

    game_free(g1);

}

/* evidence_shockwave : testing shockwave function */
void evidence_shockwave()
{
    printf("*** testing shockwave\n");
    //game* g = new_game(3, 5, 5, MATRIX);
    pos p; 

    /*p = make_pos(2, 1);
    board_set(g->b, p, BLACK);

    p = make_pos(2, 2);
    board_set(g->b, p, BLACK);

    p = make_pos(2, 3);
    board_set(g->b, p, BLACK);

    printf("board before shockwave : \n");

    board_show(g->b);

    shockwave(g, N);

    printf("\nboard after shockwave : \n");
    board_show(g->b);
    game_free(g);*/

    game* g2 = new_game(3, 5, 5, MATRIX);
    p = make_pos(0, 0);
    board_set(g2->b, p, WHITE);
    p = make_pos(2, 0);
    board_set(g2->b, p, BLACK);

    printf("board before shockwave N : \n");

    board_show(g2->b);

    shockwave(g2, N);

    printf("board after shockwave N : \n");

    board_show(g2->b);

    game_free(g2);

    game* g3 = new_game(3, 5, 5, MATRIX);
    p = make_pos(0, 0);
    board_set(g3->b, p, WHITE);
    p = make_pos(2, 0);
    board_set(g3->b, p, BLACK);
    p = make_pos(4, 0);
    board_set(g3->b, p, WHITE);

    printf("board before shockwave S : \n");

    board_show(g3->b);

    shockwave(g3, S);

    printf("board after shockwave S : \n");

    board_show(g3->b);

    game_free(g3);

    game* g4 = new_game(3, 5, 5, MATRIX);
    p = make_pos(0, 0);
    board_set(g4->b, p, WHITE);
    p = make_pos(2, 0);
    board_set(g4->b, p, BLACK);
    p = make_pos(2, 4);
    board_set(g4->b, p, WHITE);

    printf("board before shockwave E : \n");

    board_show(g4->b);

    shockwave(g4, E);

    printf("board after shockwave E : \n");

    board_show(g4->b);

    game_free(g4);

    game* g5 = new_game(3, 5, 5, MATRIX);
    p = make_pos(0, 3);
    board_set(g5->b, p, BLACK);
    p = make_pos(2, 3);
    board_set(g5->b, p, BLACK);
    p = make_pos(2, 1);
    board_set(g5->b, p, WHITE);


    printf("board before shockwave W : \n");

    board_show(g5->b);

    shockwave(g5, W);

    printf("board after shockwave W : \n");

    board_show(g5->b);

    game_free(g5);

}

/* evidence_celltype : testing celltype */
void evidence_celltype()
{
    game* g = new_game(3, 5, 5, MATRIX);
    printf("*** testing celltype\n");

    printf("- expecting 1 : %d\n", celltype(g));

    switch_player(g);

    printf("- expecting 2 : %d\n", celltype(g));

    game_free(g);

}

/* evidence_vertical : testing vertical */
void evidence_vertical()
{
    game* g = new_game(3, 5, 5, MATRIX);
    
    pos p = make_pos(1, 3);
    board_set(g->b, p, BLACK);
    p = make_pos(2, 3);
    board_set(g->b, p, BLACK);
    p = make_pos(0, 3);
    board_set(g->b, p, BLACK);
    

    board_show(g->b);

    int vert = vertical(g, p);

    printf("%u", vert);

    game_free(g);
    
}

/* evidence_diagonal_pos : testing diagonal_pos */
void evidence_diagonal_pos()
{
    game* g = new_game(3, 5, 5, MATRIX);
    
    pos p = make_pos(0, 3);
    board_set(g->b, p, BLACK);
    p = make_pos(1, 2);
    board_set(g->b, p, BLACK);
    p = make_pos(2, 1);
    board_set(g->b, p, BLACK);
    p = make_pos(3, 0);
    board_set(g->b, p, BLACK);
    

    board_show(g->b);

    int dp = diagonal_pos(g, p);

    printf("%u", dp);

    game_free(g);
}


/* evidence_horizontal : testing horizontal */

void evidence_horizontal()
{
    game* g = new_game(3, 5, 5, MATRIX);
    
    pos p = make_pos(0, 3);
    board_set(g->b, p, BLACK);
    p = make_pos(0, 1);
    board_set(g->b, p, BLACK);
    p = make_pos(0, 2);
    board_set(g->b, p, BLACK);
    
    

    board_show(g->b);

    int horiz = horizontal(g, p);

    printf("%u", horiz);

    game_free(g);
}

/* evidence_diagonal_neg : testing diagonal_pos */
void evidence_diagonal_neg()
{
    game* g = new_game(3, 5, 5, MATRIX);
    
    pos p = make_pos(1, 0);
    board_set(g->b, p, BLACK);
    p = make_pos(2, 1);
    board_set(g->b, p, BLACK);
    p = make_pos(3, 2);
    board_set(g->b, p, BLACK);
    p = make_pos(3, 2);
    board_set(g->b, p, BLACK);
    
    

    board_show(g->b);

    int dn = diagonal_neg(g, p);

    printf("%u", dn);

    game_free(g);
}


/* evidence_outcome : testing diagonal_outcome */
void evidence_game_outcome()
{
    game* g = new_game(3, 5, 5, MATRIX);
    
    pos p = make_pos(1, 0);
    board_set(g->b, p, WHITE);
    p = make_pos(2, 1);
    board_set(g->b, p, BLACK);
    p = make_pos(3, 2);
    board_set(g->b, p, WHITE);
    p = make_pos(3, 2);
    board_set(g->b, p, WHITE);
    
    

    board_show(g->b);

    outcome oc = game_outcome(g);

    if(oc == WHITE || oc == BLACK)
    {
        printf("%u", 0);
    }
    else
    {
        printf("%u", 1);
    }

    game_free(g);
}


/* main : run the evidence functions above */
int main(int argc, char *argv[])
{
    /*printf("testing POS function(s)\n");
    evidence_pos();
    printf("\n\n\n");

    printf("testing BOARD function(s)\n");
    evidence_label();
    printf("\n\n\n");

    evidence_board_show();
    printf("\n\n\n");

    evidence_board_get_set();
    printf("\n\n\n");

    printf("testing GAME function(s)\n");
    evidence_place_piece();
    printf("\n\n\n");

    evidence_shockwave();
    printf("\n\n\n");

    evidence_celltype();
    printf("\n\n\n");*/

    //evidence_vertical();
    //evidence_horizontal();
    //evidence_diagonal_neg();
    //evidence_diagonal_pos();

    //evidence_game_outcome();

    return 0;
}