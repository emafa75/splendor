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
#include <time.h>
#include <getopt.h>

#include "permutation.h"
#include "players.h"
#include "guild.h"
#include "market.h"
#include "builder.h"
#include "skills.h"
#include "token.h"
#include "can_buy.h"
#include "game.h"


#define _NB_MIN_PARAMS_ 1

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

	while ((options = getopt(argc,argv, "s:m:c:p:")) != -1)
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
			default: 
				print_usage(argv);
				return EXIT_FAILURE;
		}
	}
	game_params.market_seed = game_params.random_seed;

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
	turn_display(init_turn);

	/*
		Play the game
	*/
	game_play(&game, 1);

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
	fprintf(stderr, "Usage: %s [-s random_seed] [-m max_turns] [-c builder_seed] [-p points_to_win]\n", argv[0]);
	return;
}
