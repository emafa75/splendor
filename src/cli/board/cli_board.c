
#include "cli_board.h"
#include "cli_utils.h"
#include "color_second_header.h"
#include "market.h"
#include "set.h"
#include "token.h"
#include "token_second_header.h"
#include "vector2.h"


void board_display_tile(struct vector2_t position, unsigned int tile_dimension, const struct board_tile_t* board_tile)
{
	struct token_t* token = board_tile->token;

	if (token == NULL)
	{
		for (unsigned int x = 0 ; x < tile_dimension ; ++x)
		{
			for (unsigned int y = 0 ; y < tile_dimension ; ++y)
			{
					printToCoordinates(position.y + y, position.x + x, " ");
			}
		}
		return;
	}

	unsigned int radius = floor(sqrt(tile_dimension));

	struct vector2_t center = {};

	center.x = tile_dimension / 2;
	center.y = tile_dimension / 2;

	// Used to store the tile position in loop
	struct vector2_t current_position = {};
	// Used to store the distance between current_position and center
	unsigned int dist_to_center = 0;

	struct set_t token_set = token_get_set(token);
	enum color_t* colors = set_get_colors(&token_set);

	unsigned int num_colors = set_get_num_els(token_set);
	unsigned int pixel_per_color = tile_dimension / num_colors;


	for (unsigned int x = 0 ; x < tile_dimension ; ++x)
	{
		for (unsigned int y = 0 ; y < tile_dimension ; ++y)
		{
			current_position.x = x;
			current_position.y = y;
		
			// = |center - current_position|
			dist_to_center = (unsigned int)floor(vector2_norm(vector2_add(vector2_opposite(current_position), center)));

			color_prefix(colors[dist_to_center / pixel_per_color]);

			if (dist_to_center <= radius)
			{
				printToCoordinates(position.y + y, position.x + x, "█");
			}
			else
			{
				printToCoordinates(position.y + y, position.x + x, " ");
			}
		}
	}
}



void board_display(struct vector2_t position, struct board_t* board)
{
	struct vector2_t board_tile_start_pos = {};

	unsigned int end_offset = (board->n + 1) * board->tile_dimension;

	// draw corners
	printToCoordinates(position.y, position.x + end_offset, "┐");  // top right
	printToCoordinates(position.y, position.x, "┌");  // top left
	printToCoordinates(position.y + end_offset, position.x, "└");  // bottom left
	printToCoordinates(position.y + end_offset, position.x + end_offset, "┘");  // bottom right

	// draw top side
	for (unsigned int j = 1 ; j < (board->n + 1) * board->tile_dimension ; ++j)
	{
		if (j % (board->tile_dimension + 1) == 0)
			printToCoordinates(position.y, position.x + j, "┬");
		else
			printToCoordinates(position.y, position.x + j, "─");
	}

	// draw bottom side
	for (unsigned int j = 1 ; j < (board->n + 1) * board->tile_dimension ; ++j)
	{
		if (j % (board->tile_dimension + 1) == 0)
			printToCoordinates(position.y + end_offset, position.x + j, "┴");
		else
			printToCoordinates(position.y + end_offset, position.x + j, "─");
	}

	// draw left side
	for (unsigned int i = 1 ; i < (board->n + 1) * board->tile_dimension ; ++i)
	{
		if (i % (board->tile_dimension + 1) == 0)
			printToCoordinates(position.y + i, position.x, "├");
		else
			printToCoordinates(position.y + i, position.x, "│");
	}


	// draw right side
	for (unsigned int i = 1 ; i < (board->n + 1) * board->tile_dimension ; ++i)
	{
		if (i % (board->tile_dimension + 1) == 0)
			printToCoordinates(position.y + i, position.x + end_offset, "┤");
		else
			printToCoordinates(position.y + i, position.x + end_offset, "│");
	}


	for (unsigned int i = 0 ; i < board->n - 1 ; ++i)
	{
		for (unsigned int j = 0 ; j < board->n - 1 ; ++j)
		{
			board_tile_start_pos.x = j * (board->tile_dimension + 1) + position.x + 1;
			board_tile_start_pos.y = i * (board->tile_dimension + 1) + position.y + 1;

			printToCoordinates(board_tile_start_pos.y + board->tile_dimension, board_tile_start_pos.x + board->tile_dimension, "┼");
		}
	}

	for (unsigned int i = 0 ; i < board->n  ; ++i)
	{
		for (unsigned int j = 0 ; j < board->n ; ++j)
		{
			board_tile_start_pos.x = j * (board->tile_dimension + 1) + position.x + 1;
			board_tile_start_pos.y = i * (board->tile_dimension + 1) + position.y + 1;

			for (unsigned int k = 0 ; k < board->tile_dimension ; ++k)
			{
				printToCoordinates(board_tile_start_pos.y + k, board_tile_start_pos.x + board->tile_dimension, "│");
				printToCoordinates(board_tile_start_pos.y + board->tile_dimension, board_tile_start_pos.x + k, "─");
			}
		}
	}


	// Draw interior
	for (unsigned int i = 0 ; i < board->n ; ++i)
	{
		for (unsigned int j = 0 ; j < board->n ; ++j)
		{
			// Draw tile
			board_tile_start_pos.x = j * (board->tile_dimension + 1) + position.x + 1;
			board_tile_start_pos.y = i * (board->tile_dimension + 1) + position.y + 1;

			board_display_tile(board_tile_start_pos, board->tile_dimension, &board->matrix[i][j]);
		}
	}
}


struct board_t market_to_board(struct market* market)
{
	unsigned int side_length = (unsigned int)sqrt(NUM_TOKENS);
	unsigned int tile_dimension = 5;  // should be declared in a define

	struct board_t board = {{}, side_length, tile_dimension};

	// Used to move in board.matrix in the for loop
	struct vector2_t direction = VECTOR2_RIGHT;

	// Used to know the current position in board.matrix during the for loop
	int i = side_length - 1;
	int j = 0;

	// Store the number of tiles on the line (makes no sense but idc)
	unsigned int a = 0;
	unsigned int n = side_length;

	// Decrement n each turns_per_decrement, use num_turns as accumulator
	unsigned int num_turns = 0;
	unsigned int turns_per_decrement = 3;


	for (int k = 0 ; k < NUM_TOKENS ; ++k)
	{
		board.matrix[i][j].token = market_get_token(k);

		i += direction.y;
		j += direction.x;

		if (vector2_equals(direction, VECTOR2_RIGHT) && a >= n)
		{
			direction = VECTOR2_UP;
			++num_turns;
		}
		else if (vector2_equals(direction, VECTOR2_UP) && a >= n)
		{
			direction = VECTOR2_LEFT;
			++num_turns;
		}
		else if (vector2_equals(direction, VECTOR2_LEFT) && a >= n)
		{
			direction = VECTOR2_DOWN;
			++num_turns;
		}
		else if (vector2_equals(direction, VECTOR2_DOWN) && a >= n)
		{
			direction = VECTOR2_RIGHT;
			++num_turns;
		}
	
		if (num_turns == turns_per_decrement)
		{
			a = 0;
			--n;
			num_turns = 0;
		}
	}

	return board;
}

