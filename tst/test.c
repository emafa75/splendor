/**
 *
 * @filename test.c
 * @date 2023-11-07 16:04
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include "test_can_buy.h"
#include "test_players.h"
#include "token.h"
#include <math.h>
#define SEED 0

#include <stdlib.h>
#include <stdio.h>

#include "test_builders.h"
#include "test_tokens.h"
#include "test_guild.h"
#include "test_market.h"
#include "ansi_color.h"
#include "board_display.h"

#include "market.h"
#define _NB_MIN_PARAMS_ 1


void print_usage(char *argv[]);


int main(int argc, char *argv[])
{
	if (argc < _NB_MIN_PARAMS_)
	{
		print_usage(argv);
		return EXIT_FAILURE;
	}

	test_token();
	test_builders();
	test_market();
	test_guild();
	test_players();
	test_utils();
	
	init_market(0);
	
	market_shuffle();
	market_display();
	int board_size = sqrt(NUM_TOKENS);
	struct token_t* board[board_size][board_size];
	char * tags[board_size][board_size];
	place_token_in_board(get_available_tokens()->available, board, tags);
	display_board(board,tags);



	return EXIT_SUCCESS;
}


void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s ....\n", argv[0]);
	return;
}
