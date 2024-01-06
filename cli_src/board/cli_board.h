#ifndef __CLI_BOARD_H__
#define __CLI_BOARD_H__

#include "vector2.h"
#include "board_display.h"




/*
 *  Display the token_t at position (i, j) of the screen
 *
 *	To missing token, pass NULL at token arg
 */
void board_display_tile(struct vector2_t position, unsigned int tile_dimension, const struct board_tile_t* board_tile);


/*
 *  Display the board, start at position
 */
struct vector2_t cli_board_display(struct vector2_t position, struct board_t* board);


#endif
