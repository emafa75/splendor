
#include "cli_board.h"
#include "ansi_color.h"
#include "cli_utils.h"
#include "color.h"
#include "market.h"
#include "set.h"
#include "skills.h"
#include "token.h"
#include "token_second_header.h"
#include "vector2.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color_second_header.h"

void board_display_tile(struct vector2_t position, unsigned int tile_dimension, const struct board_tile_t* board_tile)
{
	struct token_t* token = board_tile->token;

	if (token == NULL)
	{
		for (unsigned int x = 0 ; x < tile_dimension ; ++x)
		{
			for (unsigned int y = 0 ; y < tile_dimension ; ++y)
			{
					printToCoordinates(position.x + x, position.y + y, " ");
			}
		}
		return;
	}

	double double_tile_dimension = (double)(tile_dimension);
	double radius = double_tile_dimension / 2;

	struct vector2_t center = {};

	center.x = floor(double_tile_dimension );
	center.y = floor(double_tile_dimension / 2);

	// Used to store the tile position in loop
	struct vector2_t current_position = {};
	// Used to store the distance between current_position and center
	double dist_to_center = 0;

	struct set_t token_set = token_get_set(token);
	enum color_t* colors = set_get_colors(&token_set);

	unsigned int num_colors = set_get_num_els(token_set);
	unsigned int pixel_per_color = (tile_dimension * tile_dimension * 2 )/ num_colors;
	enum color_t non_null_colors[num_colors];

	int last_index = 0;
	for (enum color_t color = 0; color < NUM_COLORS; ++color)
	{
		if(colors[color] != 0) //add it to the new array
		{
			non_null_colors[last_index] = color;
			++last_index;
		}
	}
	char colored_pixel[100];

	unsigned int num_colored_pixels = 0;
	unsigned int index_non_null_color = 0;

	for (unsigned int x = 0 ; x < tile_dimension * 2 ; ++x)
	{
		for (unsigned int y = 0 ; y < tile_dimension ; ++y)
		{	
			++num_colored_pixels;

			/*
				Change color if enought colored pixel for a color
			*/
			if( num_colored_pixels > pixel_per_color)
			{
				num_colored_pixels = 0;
				++index_non_null_color;
			}

			current_position.x = x;
			current_position.y = y;
		
			// = |center - current_position|
			dist_to_center = vector2_norm2(vector2_add(vector2_opposite(current_position), center));

			if (dist_to_center < radius)
			{
				const char* prefix_color = color_prefix(non_null_colors[index_non_null_color]);
				/*
					If the token has skill, print gold circle
				*/
				if (radius - dist_to_center < 1  && has_skills(token))
				{
					sprintf(colored_pixel, "%s" BLINK "█" BLINK_RESET "%s", YEL , CRESET);
				}
				else {
					sprintf(colored_pixel, "%s█%s", prefix_color, CRESET);
					
				}
				printToCoordinates(position.x + x, position.y + y, colored_pixel);
			}
			else
			{
				printToCoordinates(position.x + x, position.y + y, " ");
			}
		}
	}
}



struct vector2_t board_display(struct vector2_t position, struct board_t* board)
{
	struct vector2_t board_tile_start_pos = {};
	
	unsigned int tile_dimension = board->tile_dimension;
	unsigned int board_dimension = board->n;
	unsigned int end_offset = board_dimension * (tile_dimension + 1);
	unsigned int abs_offset = board_dimension * (tile_dimension * 2 +1);

	// draw corners
	printToCoordinates(position.x, position.y + end_offset, "└");  //bottom left
	printToCoordinates(position.x, position.y, "┌");  // top left
	printToCoordinates(position.x + abs_offset, position.y, "┐");  // top right┘└┐
	printToCoordinates(position.x + abs_offset, position.y + end_offset, "┘");  // bottom right

	// draw top side
	for (unsigned int j = 1 ; j < abs_offset ; ++j)
	{
		if (j % (tile_dimension * 2 + 1) == 0)
			printToCoordinates(position.x + j, position.y, "┬");
		else
			printToCoordinates(position.x + j, position.y, "─");
	}

	// draw bottom side
	for (unsigned int j = 1 ; j < abs_offset ; ++j)
	{
		if (j % (tile_dimension * 2 + 1) == 0)
			printToCoordinates(position.x + j , position.y + end_offset, "┴");
		else
			printToCoordinates(position.x + j , position.y + end_offset, "─");
	}

	// draw left side
	for (unsigned int i = 1 ; i < end_offset ; ++i)
	{
		if (i % (tile_dimension + 1) == 0)
			printToCoordinates(position.x , position.y + i, "├");
		else
			printToCoordinates(position.x, position.y + i , "│");
	}


	// draw right side
	for (unsigned int i = 1 ; i < end_offset ; ++i)
	{
		if (i % (tile_dimension + 1) == 0)
			printToCoordinates(position.x + abs_offset, position.y + i, "┤");
		else
			printToCoordinates(position.x + abs_offset ,position.y + i, "│");
	}

	// draw carrefour
	for (unsigned int i = 0 ; i < board_dimension - 1 ; ++i)
	{
		for (unsigned int j = 0 ; j < board_dimension - 1 ; ++j)
		{
			board_tile_start_pos.x = j * (tile_dimension * 2 + 1) + position.x + 1;
			board_tile_start_pos.y = i * (tile_dimension + 1) + position.y + 1;

			printToCoordinates(board_tile_start_pos.x + tile_dimension * 2, board_tile_start_pos.y + tile_dimension, "┼");
		}
	}

	// draw tiles
	for (unsigned int i = 0 ; i < board_dimension ; ++i)
	{
		for (unsigned int j = 0 ; j < board_dimension ; ++j)
		{
			board_tile_start_pos.x = j * (tile_dimension * 2 + 1) + position.x + 1;
			board_tile_start_pos.y = i * (tile_dimension + 1) + position.y + 1;

			for (unsigned int k = 0 ; k < tile_dimension * 2 ; ++k)
			{
				//draw horizontal
				printToCoordinates(board_tile_start_pos.x + k, board_tile_start_pos.y + tile_dimension, "─");
			}

			for (unsigned int k = 0 ; k < tile_dimension ; ++k)
			{
				//draw vertical
				printToCoordinates(board_tile_start_pos.x + tile_dimension * 2, board_tile_start_pos.y + k, "│");
			}
		}
	}


	// Draw interior
	for (unsigned int i = 0 ; i < board_dimension ; ++i)
	{
		for (unsigned int j = 0 ; j < board_dimension ; ++j)
		{
			// Draw tile
			board_tile_start_pos.x = i * (tile_dimension * 2 + 1) + position.x + 1;
			board_tile_start_pos.y = j * (tile_dimension + 1) + position.y + 1;

			board_display_tile(board_tile_start_pos, tile_dimension, &board->matrix[i][j]);
		}
	}

	struct vector2_t last_position = {board_dimension * (tile_dimension * 2 + 1) + position.x , board_dimension * (tile_dimension + 1) + position.y};
	return last_position;
}


struct board_t market_to_board(struct market_t* market)
{
	unsigned int side_length = (unsigned int)sqrt(NUM_TOKENS);
	unsigned int tile_dimension = TILE_DIMENSION;  // should be declared in a define

	struct board_t board = {{}, side_length, tile_dimension};

	// Used to move in board.matrix in the for loop
	struct vector2_t direction = vector2_right();

	// Used to know the current position in board.matrix during the for loop
	int i = 0;
	int j = 0;

	// Store the number of tiles on the line (makes no sense but idc)
	unsigned int steps = 0;
	unsigned int step_limit = side_length;

	// Decrement n each turns_per_decrement, use num_turns as accumulator
	unsigned int num_turns = 0;
	unsigned int turns_per_decrement = 2;


	for (int k = 0 ; k < NUM_TOKENS ; ++k)
	{
		board.matrix[i][j].token = market->tokens[k];

		++steps;


		if (steps == step_limit )
		{
			steps = 1;

			if (num_turns == turns_per_decrement)
			{
				--step_limit;
				num_turns = 0;
			}

			++num_turns;

			/*
				Change direction for next replacement
			*/
			if (vector2_equals(direction, vector2_right()))
				direction = vector2_down();

			else if (vector2_equals(direction, vector2_up()))
				direction = vector2_right();

			else if (vector2_equals(direction, vector2_left()))
				direction = vector2_up();

			else if (vector2_equals(direction, vector2_down()))
				direction = vector2_left();
		}

		/*
			Go to the following case in the matrix
		*/
		i += direction.y;
		j += direction.x;
		
	}

	return board;
}

