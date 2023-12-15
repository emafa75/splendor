#include "board_display.h"
#include "skills.h"
#include <stdio.h>
#include <string.h>
#include "ansi_color.h"
#include "token_second_header.h"

#define PRINT_CARACT(_n, _c)\
	for (int i = 0; i < (_n); ++i)  printf(_c);

#define TILE_LENGTH 14
#define TILE_WIDTH 3

void place_token_in_board(struct token_t *tokens[NUM_TOKENS], \
struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], \
char* tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)])
{
	int dx = 1;
	int dy = 0;
	int i = 0;
	int j = 0;
	int board_size = sqrt(NUM_TOKENS);

	int steps = 0;
	int step_limit = board_size ;
	int direction_changes = 0;
	
	for (int index = 0; index < NUM_TOKENS ; ++index )
	{
		if((i < board_size ) && (i  >= 0) && (j < board_size) && (j >= 0))
		{
			
			board[i][j] = tokens[index];
			
		}

		++steps;

		if(steps == step_limit)
		{
			steps = 1;
			

			if (direction_changes == 2)
			{
				direction_changes = 0;
				--step_limit;
			}
			++direction_changes;

			int tmp = dx;
			dx = -dy;
			dy = tmp;
		}

		if((i < board_size ) && (i  >= 0) && (j < board_size) && (j >= 0))
		{
			
			if (dx == 1) // we are going to the rigt
			{
				tags[i][j] = "→";
			}
			if (dx == -1 ) //we are going to the left
			{
				tags[i][j] = "←";
			}
			if (dy == 1) // we are going down
			{
				tags[i][j] = "↓";
			}
			if (dy == -1 ) // we are going up
			{
				tags[i][j] = "↑";
			}
			if (index == NUM_TOKENS -1 ) // last position
			{
				tags[i][j] = "•";
			}
		}
		i += dy;
		j += dx;
	}


}

void display_board(struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], char* tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)]) {
	int size = sqrt(NUM_TOKENS);
	int i = 0;
	int j = 0;
	int num_color_in_token = 0;
	int free_space = 0;

	for (j = 0; j < size ; ++j) {
		printf((j != 0 ) ? "┬" : "┌");
		PRINT_CARACT(TILE_LENGTH,"─");
	}
	printf("┐\n");

	

	// Display the board with borders
	for (i = 0; i < size; i++) {
		for (int line = 0; line < TILE_WIDTH; line++) {
			printf("│");
			for (j = 0; j < size; j++) {

				if (line == TILE_WIDTH / 2 )
				{
					if( board[i][j] != NULL) {
						/*
							Get num_color from the token to adapt the print in the tile
						*/
						num_color_in_token = board[i][j]->s.num_colors;
						free_space = TILE_LENGTH - (3 * num_color_in_token + 3);
						if (has_skills(board[i][j]))
						{
							free_space -= 2; //because of the *
							PRINT_CARACT(free_space / 2," ");
							printf("*");
							token_short_diplay(*board[i][j]);
							printf("*");
							PRINT_CARACT(free_space / 2 + free_space % 2, " ");
							printf("│");

						}
						else{							
							PRINT_CARACT(free_space / 2 , " ");
							token_short_diplay(*board[i][j]);
							PRINT_CARACT(free_space / 2 + free_space % 2 , " ");
							printf("│");
						}
						
					}
					else {
						PRINT_CARACT(TILE_LENGTH, " ");
						printf("│");
					}
				}
				else if(line == 0)
				{
					int tag_length = strlen(tags[i][j]);
					PRINT_CARACT(TILE_LENGTH - tag_length + 1, " ");
					printf(RED "%s" CRESET, tags[i][j]);
					printf(" │");
				}
				else {
					PRINT_CARACT(TILE_LENGTH, " ");
					printf("│");
				}
			}
			printf("\n");
		}

		// Display borders between rows
		for (j = 0; j < size ; ++j) {
			printf((i != size-1) ? ((j != 0) ? "┼" : "├") : ((j != 0) ? "┴" : "└"));
			PRINT_CARACT(TILE_LENGTH, "─");
		}
		printf((i != size -1 ) ? "┤\n" : "┘\n");
	}
}

