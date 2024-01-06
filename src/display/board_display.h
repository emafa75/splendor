#ifndef __BOARD_DISPLAY_H__
#define __BOARD_DISPLAY_H__

#include "token.h"
#include "market.h"
#include <math.h>
#include "vector2.h"

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
 *  Place tokens from the market into a board
 */
struct board_t market_to_board(struct market_t* market);


/*
	Display the game market board, need to give the list of the token in a matrix
*/
void board_display(const struct board_t* board);

#endif
