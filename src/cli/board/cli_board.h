#ifndef __CLI_BOARD_H__
#define __CLI_BOARD_H__

#include "token.h"
#include "cli_utils.h"
#include <math.h>

#define BOARD_SIZE NUM_TOKENS


/*
 *  board dimension n <= sqrt(NUM_TOKENS)
 */
struct board {
	struct token_t* matrix[BOARD_SIZE][BOARD_SIZE];
	unsigned int n;
	unsigned int tile_dimension;
};


/*
 *  Display the token_t at position (i, j) of the screen
 *
 *	To missing token, pass NULL at token arg
 */
void board_display_tile(unsigned int i, unsigned int j, unsigned int tile_dimension, const struct token_t* token);


void board_display(struct board* board);


#endif
