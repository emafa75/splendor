/**
 *
 * @filename main.c
 * @date 2023-11-07 14:14
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>, Martin EYBEN <martin.eyben@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

#include "color.h"
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
 *	Display the stats for evaluator
 */
void print_stats_header(FILE* file);
void display_stats(struct game_statistics stats, struct game_parameters game_parameters, FILE* file);


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

	while ((options = getopt(argc,argv, "s:m:c:p:t:")) != -1)
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
			default: 
				print_usage(argv);
				return EXIT_FAILURE;
		}
	}

	// display_options();
	print_stats_header(stdout);

	int n2 = 10;
	int n = 100;
	int offset = 1;
	int k = 0;

	for (int b_seed = 1 ; b_seed < n2 + 1 ; ++b_seed)
	{
		for (int t_seed = 1 ; t_seed < n2 + 1 ; ++t_seed)
		{
			for (int r_seed = offset ; r_seed < n + offset ; ++r_seed)
			{
				fprintf(stderr, "Current seeds: r: %d, t: %d, b: %d\n", r_seed, t_seed, b_seed);
				k++;
				if (k % 100 == 0)
					fprintf(stderr, "%d\n", k);

				struct game_t game = {};

				game_params.random_seed = r_seed;
				game_params.builder_seed = b_seed;
				game_params.market_seed = t_seed;
				/*
					Init all instances
				*/
				init_game(&game, game_params);

				/*
					Play the game
				*/
				struct game_statistics game_stats = game_play(&game, PRINT);

				/*
					End of the game, print results 
				*/
				display_stats(game_stats, game_params, stdout);
			}
		}
	}
	return EXIT_SUCCESS;
}


void print_stats_header(FILE* file)
{
	fprintf(file, "random_seed;seed_builders;seed_token;choices;used_favor;used_skill;num_picked_tokens;forced_skip;nb_turns\n");
}


void display_stats(struct game_statistics stats, struct game_parameters game_parameters, FILE* file)
{
	fprintf(file, "%d;%d;%d;",
			game_parameters.random_seed,
			game_parameters.builder_seed,
			game_parameters.market_seed);


	for (int i = 0 ; i < NUM_CHOICE - 1 ; ++i)
		fprintf(file, "%d,", stats.choices[i]);

	fprintf(file, "%d;", stats.choices[NUM_CHOICE - 1]);

	fprintf(file, "%d;%d;%d;%d;%d\n",
			stats.used_favor,
			stats.used_skill,
			stats.num_picked_tokens,
			stats.forced_skip,
			stats.nb_turns
			);

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
