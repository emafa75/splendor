
#include "cli_board.h"
#include "cli_utils.h"


void board_display_tile(unsigned int i, unsigned int j, unsigned int tile_dimension, const struct token_t* token)
{
	unsigned int radius = floor(sqrt(tile_dimension));
	unsigned int center_i = i / 2;
	unsigned int center_j = j / 2;


	for (int x = 0 ; x < tile_dimension ; ++x)
	{
		for (int y = 0 ; y < tile_dimension ; ++y)
		{
			if (sqrt((y - center_i) * (y - center_i) - (x - center_j) * (x - center_j)) <= radius)
			{
				printToCoordinates(i + y, j + x, '@');
			}
		}
	}
}



void board_display(struct board* board)
{
	for (int i = 0 ; i < board->n ; ++i)
	{
		for (int j = 0 ; j < board->n ; ++j)
		{
			board_display_tile(i * board->tile_dimension, j * board->tile_dimension, board->tile_dimension, board->matrix[i][j]);
		}
	}
}



