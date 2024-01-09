#include "board_display.h"
#include "ansi_color.h"
#include "token_second_header.h"
#include "vector2.h"
#include "skills.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define PRINT_CARACT(_n, _c)\
	for (int i = 0; i < (_n); ++i)  printf(_c);

#define TILE_LENGTH 14
#define TILE_WIDTH 3

struct board_t market_to_board(struct market_t* market)
{
	unsigned int side_length = (unsigned int)sqrt(NUM_TOKENS);
	unsigned int tile_dimension = TILE_DIMENSION;  // should be declared in a define

	struct board_t board = {{}, side_length, tile_dimension};

	// Used to move in board.matrix in the for loop
	struct vector2_t direction = vector2_right();

	// Used to know the current position in board.matrix during the for loop
	unsigned int i = 0;
	unsigned int j = 0;

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

		if ((i < side_length ) && (j < side_length))
		{
			if (vector2_equals(direction, vector2_right())) // we are going to the rigt
			{
				board.matrix[i][j].next_direction = vector2_right();
			}

			if (vector2_equals(direction, vector2_left())) //we are going to the left
			{
				board.matrix[i][j].next_direction = vector2_left();
			}

			if (vector2_equals(direction, vector2_down())) // we are going down
			{
				board.matrix[i][j].next_direction = vector2_down();
			}

			if (vector2_equals(direction, vector2_up())) // we are going up
			{
				board.matrix[i][j].next_direction = vector2_up();
			}

			if (k == NUM_TOKENS -1 ) // last position
			{
				board.matrix[i][j].next_direction = vector2_zero();
			}
		}

		/*
			Go to the following case in the matrix
		*/
		i += direction.y;
		j += direction.x;
		
	}

	return board;
}


void board_display(const struct board_t* board) 
{
	int size = board->n;
	int i = 0;
	int j = 0;
	int num_color_in_token = 0;
	int free_space = 0;
	char * direction;

	/*
		Print above line
	*/
	for (j = 0 ; j < size ; ++j)
	{
		printf((j != 0 ) ? "┬" : "┌");
		PRINT_CARACT(TILE_LENGTH,"─");
	}
	printf("┐\n");


	// Display the board with borders
	for (i = 0 ; i < size ; i++) {
		for (int line = 0 ; line < TILE_WIDTH ; line++) {
			printf("│");
			for (j = 0 ; j < size ; j++)
			{

				if (line == TILE_WIDTH / 2 )
				{
					if (board->matrix[i][j].token != NULL)
					{
						/*
							Get num_color from the token to adapt the print in the tile
						*/
						num_color_in_token = board->matrix[i][j].token->s.num_colors;
						free_space = TILE_LENGTH - (3 * num_color_in_token + 3);
						if (has_skills(board->matrix[i][j].token))
						{
							free_space -= 2; //because of the *
							PRINT_CARACT(free_space / 2," ");
							printf("*");
							token_short_diplay(*board->matrix[i][j].token);
							printf("*");
							PRINT_CARACT(free_space / 2 + free_space % 2, " ");
							printf("│");
						}
						else
						{
							PRINT_CARACT(free_space / 2 , " ");
							token_short_diplay(*board->matrix[i][j].token);
							PRINT_CARACT(free_space / 2 + free_space % 2 , " ");
							printf("│");
						}
					}
					else
					{
						PRINT_CARACT(TILE_LENGTH, " ");
						printf("│");
					}
				}
				else if (line == 0)
				{
					direction = vector2_char(board->matrix[i][j].next_direction);
					int tag_length = strlen(direction);
					PRINT_CARACT(TILE_LENGTH - tag_length + 1, " ");
					printf(RED "%s" CRESET, direction);
					printf(" │");
				}
				else
				{
					PRINT_CARACT(TILE_LENGTH, " ");
					printf("│");
				}
			}

			printf("\n");
		}

		// Display borders between rows
		for (j = 0; j < size ; ++j)
		{
			printf((i != size-1) ? ((j != 0) ? "┼" : "├") : ((j != 0) ? "┴" : "└"));
			PRINT_CARACT(TILE_LENGTH, "─");
		}

		printf((i != size -1 ) ? "┤\n" : "┘\n");
	}
}

