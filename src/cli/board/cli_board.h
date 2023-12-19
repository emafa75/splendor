#ifndef __CLI_BOARD_H__
#define __CLI_BOARD_H__

#include "token.h"
#include "vector2.h"
#include "market.h"

#define BOARD_SIZE NUM_TOKENS

#define TILE_DIMENSION 5
/*
 *
 */
struct board_tile_t {
	struct token_t* token;
	struct vector2_t next_direction;  // Used to display the arrow
};


/*
 *  board dimension n <= sqrt(NUM_TOKENS)
 */
struct board_t {
	struct board_tile_t matrix[BOARD_SIZE][BOARD_SIZE];
	unsigned int n;
	unsigned int tile_dimension;
};


/*
 *  
 */
struct board_t market_to_board(struct market_t* market);





/*
 *  Display the token_t at position (i, j) of the screen
 *
 *	To missing token, pass NULL at token arg
 */
void board_display_tile(struct vector2_t position, unsigned int tile_dimension, const struct board_tile_t* board_tile);


/*
 *  Display the board, start at position
 */
struct vector2_t board_display(struct vector2_t position, struct board_t* board);


#endif
