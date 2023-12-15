#ifndef __BOARD_DISPLAY_H__
#define __BOARD_DISPLAY_H__


#include "token.h"
#include "math.h"


/*
    Display the game market board, need to give the list of the token in a matrix
*/
void display_board(struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], char* tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)]);

/*
    Place tokens in a matrice board[rac(NUM_TOKENS)][rac(NUM_TOKENS)] and fills the tags with the direction
*/
void place_token_in_board(struct token_t* tokens[NUM_TOKENS], struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], char *tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)]);
#endif