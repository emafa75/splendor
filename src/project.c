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
#include "token.h"
#include "can_buy.h"
#include "game.h"

#include "cli_tests.h"

#define MIN(__x, __y) \
  ((__x) < (__y) ? (__x) : (__y))

#define _NB_MIN_PARAMS_ 1




enum choice {
	HIRE,
	PICK,
	NUM_CHOICE,
	FIRST_CHOICE = HIRE
};

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

int random_seed = RANDOM_SEED;


int main(int argc, char *argv[])
{
	cli_tests();
	
	// if (argc < _NB_MIN_PARAMS_)
	// {
	// 	print_usage(argv);
	// 	return EXIT_FAILURE;
	// }
	// 
	// /*
	// 	Get optionnal parameters 
	// */
	// int options;
	//
	// while ((options = getopt(argc,argv, "s:m:c:p:")) != -1)
	// {
	// 	switch (options) {
	// 		case 's':
	// 			random_seed = atoi(optarg);
	// 			break;
	// 		case 'm':
	// 			max_turns = atoi(optarg);
	// 			break;
	// 		case 'c':
	// 			builder_seed = atoi(optarg);
	// 			break;
	// 		case 'p':
	// 			points_to_win = atoi(optarg);
	// 			break;
	// 		default: 
	// 			print_usage(argv);
	// 			return EXIT_FAILURE;
	// 	}
	// }
	//
	// display_options();
	// srand(random_seed);
	//
	// /*
	// 	Init all instances
	// */
	// init_builders(builder_seed);
	//
	// struct market market = create_default_market();
	// init_market(&market, market_seed);  //init tokens
	//
	// struct guild guild = create_default_guild();
	// init_guild(&guild);
	//
	// guild_display(&guild);
	// market_display(&market);
	//
	// /*
	// 	Init first player and current turn
	// */
	// int current_player = get_random_player(random_seed);
	// int current_turn = 0;
	//
	// /*
	// 	Init list of players with MAX_PLAYERS in game
	// */
	// for (int index = 0 ; index < MAX_PLAYERS ; ++index)
	// {
	// 	player_list[index] = init_player();
	// }
	//
	// /*
	// 	Game loop
	// */
	// while (!has_won(MAX_PLAYERS, player_list) && current_turn <= max_turns)
	// {	
	// 	printf("=============================================================\n");
	// 	printf("Turn n°%d\n", current_turn);
	//
	// 	/*
	// 		Take a random decision and check if it's possible to hire a builder
	// 	*/
	// 	enum choice random_choice = rand() % NUM_CHOICE; 
	// 	struct builder_t* builder_to_buy = select_affordable_builder(&guild, &player_list[current_player]);
	//
	//
	// 	if ((random_choice == HIRE) && (builder_to_buy != NULL)) 
	// 	{
	// 		/*
	// 			The player choosed to hire a builder and is able to do so
	// 		*/
	// 		printf("Player id.%d choosed to hire\n", current_player);
	// 		player_pay_builder(&market, &player_list[current_player], builder_to_buy);
	// 		player_hire_builder(&guild, &player_list[current_player], builder_to_buy);
	// 	}
	// 	else 
	// 	{
	// 		/*
	// 			The player choosed to pick a token or is unable to hire a builder (default choice)
	// 			If he choose to pick 0 token, he skip his turn
	// 		*/
	// 		/*
	// 			Choose how many token he wants to take (0 to 3), never more than the number of available token.
	// 		*/
	// 		int num_token_to_pick = rand() % 4; 
	// 		num_token_to_pick = MIN(num_token_to_pick, market_num_tokens(&market));
	// 		printf("Player id.%d choosed to pick %d token(s)\n", current_player, num_token_to_pick);
	//
	// 		/*
	// 			Get the index of the first available token to match with the number of token that the player wanted to take
	// 		*/
	// 		int index_first_token_to_pick = market_get_linked_tokens(&market, num_token_to_pick);
	//
	// 		/*
	// 			Pick the number of token he wants from the market (no choice, pick one per one in order)
	// 			If his choice is impossible, he skip his turn;
	// 		*/
	//
	// 		if(index_first_token_to_pick == -1 && num_token_to_pick != 0) // impossible choice 
	// 		{
	// 			printf("Player id.%d choosed to pick too much tokens, not enough linked token available. Turn skipped.\n" , current_player);
	// 		}
	// 		else
	// 		{
	// 			for (int index = 0 ; index < num_token_to_pick ; ++index)
	// 			{
	// 				player_pick_token(&market, &player_list[current_player], market.tokens[index_first_token_to_pick+index]);
	// 			}
	// 		}
	// 	}
	//
	// 	/*
	// 		End of the turn, display player inventory to follow the game
	// 	*/
	//
	// 	printf("Current inventory for player id.%d : \n", current_player);
	// 	player_display_inventory(&player_list[current_player]);
	//
	// 	/*
	// 		Give turn to the next player
	// 	*/
	// 	
	// 	printf("=============================================================\n");
	// 	printf("Market after turn n°%d :\n", current_turn);
	// 	market_display(&market);
	// 	current_player = next_player(current_player);
	// 	++current_turn;
	// }
	// /*
	// 	End of the game, print results 
	// */
	// printf("End of the game !\nResult of the game : ");
	// int winner = get_winner(MAX_PLAYERS, player_list);
	//
	// if (winner <= -1)
	// {
	// 	printf("TIE\n");
	// }
	// else
	// {
	// 	printf("Player id.%d won with %d point(s) !\n", winner, player_list[winner].current_point);
	// }

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
