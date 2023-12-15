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
#include "players.h"
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

	while ((options = getopt(argc,argv, "s:m:c:p:t:v")) != -1)
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

	struct turn_t* init_turn = game_get_current_turn(&game);

	/*
		Display the init set
	*/
	printf("\nGame init : \n");
	turn_display(init_turn);

	/*
		Play the game
	*/
	struct game_statistics game_stats = game_play(&game, game_params.display);

	/*
		End of the game, print results 
	*/
	printf("End of the game !\nResult of the game : ");
	struct turn_t* last_turn = game_get_current_turn(&game);
	int winner = get_winner(last_turn);

	if (winner <= -1)
	{
		printf("TIE\n");
	}
	else{
		printf("Player id.%d won with %d point(s) !\n", winner, player_get_points(&turn_get_players(last_turn)[winner]));
	}

	printf("\n");
	printf(BWHT "══════════════════════════  Game Statistics  ═════════════════════════════\n" CRESET);
	game_stats_display(game_stats);
	printf(BWHT "══════════════════════════════════════════════════════════════════════════\n" CRESET);

	return EXIT_SUCCESS;
}

void display_options()
{
	printf("Random seed : %d\nBuilder seed : %d\nMarket seed : %d\nPoints to win a game : %d\nMax turns : %d\n", 
		game_params.random_seed,
		game_params.builder_seed,
		game_params.market_seed,
		game_params.points_to_win,
		game_params.max_turns
	);
}


void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s [-s random_seed] [-m max_turns] [-c builder_seed] [-t token seed] [-p points_to_win]\n", argv[0]);
	return;
}
