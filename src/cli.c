/**
 *
 * @filename project.c
 * @date 2023-11-07 14:14
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>, Martin EYBEN <martin.eyben@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "cli_tests.h"
#include "cli_turn.h"
#include "cli_utils.h"
#include "game.h"
#include "ansi_color.h"

#define _NB_MIN_PARAMS_ 1

#ifndef PRINT	
	#define PRINT 1
#endif

enum parameters {
	MAX_TURNS = 10,
	POINTS_TO_WIN = 10,
	RANDOM_SEED = 0,
	BUILDER_SEEED = 0,
	MARKET_SEED = 0,
};

void print_usage(char *argv[]);

/*
	Display options for the game
*/
void display_options();

/*
	Init all parameters 
*/

struct game_parameters game_params = {
	.points_to_win = POINTS_TO_WIN,
	.max_turns = MAX_TURNS,
	.market_seed = MARKET_SEED,
	.builder_seed = BUILDER_SEEED,
	.random_seed = RANDOM_SEED,
	.display = PRINT,
	.num_player = 2,
};

int main(int argc, char *argv[])
{
	
	if (argc < _NB_MIN_PARAMS_)
	{
		print_usage(argv);
		return EXIT_FAILURE;
	}
	
	/*
		Get optionnal parameters 
	*/
	int options;

	while ((options = getopt(argc,argv, "s:m:c:p:t:vn:")) != -1)
	{
		switch (options) {
			case 's':
				game_params.random_seed = atoi(optarg);
				break;
			case 'm':
				game_params.max_turns = MIN(atoi(optarg), MAX_MAX_TURNS);
				break;
			case 'c':
				game_params.builder_seed = atoi(optarg);
				break;
			case 'p':
				game_params.points_to_win = atoi(optarg);
				break;
			case 't':
				game_params.market_seed = atoi(optarg);
				break;
			case 'v':
				game_params.display = 1;
				break;
			case 'n':
				game_params.num_player = atoi(optarg);
				break;
			default: 
				print_usage(argv);
				return EXIT_FAILURE;
		}
	}

	display_options();
	
	/*
		Init all instances
	*/
	struct game_t game = {};
	init_game(&game, game_params);

	/*
		Play the game
	*/
	struct game_statistics game_stats = game_play(&game, game_params.display);

	/*
		Get the first turn
	*/
	struct turn_t* turn = game_get_turn(&game, 0);
	int turn_index = turn_get_id(turn);

	//disable the cursor
	terminal_cursor(0);
	clear_terminal();

	/*
		Loop to display the turns	
	*/
	int ch = 0;
	int print = 1;
	while( ch != 'q'){
		switch (ch) {
			case 'n':
				if(turn_index < game_stats.nb_turns)
				{
					turn = game_get_turn(&game, ++turn_index);
					clear_terminal();
					print = 1;
				}
				else {
					cli_popup(RED "No turn left" CRESET);
					print = 0;
				}
				break;
			case 'p':
				if(turn_index > 0) 
				{
					turn = game_get_turn(&game, --turn_index);
					clear_terminal();
					print = 1;
				}
				else {
					cli_popup(RED "It's already the init turn" CRESET);
					print = 0;
				}
				break;
			case 0:
				break;
			default:
				cli_popup(RED "Unknown Command" CRESET);
				print = 0;
		} 

		if (print)
			cli_turn_display(turn);

		ch = getch();
	}

	/*
		Reenable the cursor
	*/
	terminal_cursor(1);
	

	return EXIT_SUCCESS;
}

void display_options()
{
	printf("Random seed : %d\nBuilder seed : %d\nMarket seed : %d\nPoints to win a game : %d\nMax turns : %d\nNumber of player : %d\n", 
		game_params.random_seed,
		game_params.builder_seed,
		game_params.market_seed,
		game_params.points_to_win,
		game_params.max_turns,
		game_params.num_player
	);
}


void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s [-s random_seed] [-m max_turns] [-c builder_seed] [-t token seed] [-p points_to_win] [-n number of player]\n", argv[0]);
	return;
}

