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
	srand(game_params.random_seed);
	/*
		Init all instances
	*/
	struct game_t game = {};
	init_game(&game, game_params);

	struct turn_t* current_turn = game_get_current_turn(&game);
	/*
		Display the init set
	*/
	turn_display(current_turn);

	/*
		Choose a random permutation for the replacement of tokens in the market
	*/
	struct permutation market_permutation = random_permutation(game_params.random_seed);

	/*
		Game loop
	*/
	while (!has_won(current_turn) && game.current_turn_index <= game.num_turns)
	{	
		printf("══════════════════════════════════════════════════════════════════════\n");
		
		current_turn = game_get_current_turn(&game);
		/*
			Get place where to stock the action of the current turn
		*/
		struct market_t* market = turn_get_market(current_turn);
		struct guild_t* guild = turn_get_guild(current_turn); 
		struct player_t* current_player = turn_get_current_player(current_turn);
		int turn_index = game.current_turn_index;
		int player_index = turn_get_current_player_index(current_turn);


		printf("Turn n°%d\n", turn_index);

		/*
			Take a random decision and check if it's possible to hire a builder
		*/
		enum choice random_choice = rand() % NUM_CHOICE; 
		struct builder_t * builder_to_buy = select_affordable_builder(guild, current_player);


		if ((random_choice == HIRE) && (builder_to_buy != NULL)) 
		{
			/*
				The player choosed to hire a builder and is able to do so
			*/
			printf("Player id.%d choosed to hire\n", player_index);
			player_pay_builder(market, current_player, builder_to_buy, market_permutation);
			player_hire_builder(guild, current_player, builder_to_buy);
			/*
				Execute the skill associate to the builder
			*/
			skill_exec(current_turn, builder_to_buy);
		}
		else 
		{
			/*
				The player choosed to pick a token or is unable to hire a builder (default choice)
				If he choose to pick 0 token, he skip his turn
			*/
			/*
				Choose how many token he wants to take (0 to 3), never more than the number of available token.
			*/
			int num_token_to_pick = rand() % 4; 
			num_token_to_pick = MIN(num_token_to_pick, market_num_tokens(market));
			printf("Player id.%d choosed to pick %d token(s)\n" , player_index, num_token_to_pick);

			/*
				Get the index of the first available token to match with the number of token that the player wanted to pick
			*/
			int index_first_token_to_pick = market_get_linked_tokens(market, num_token_to_pick);

			/*
				Pick the number of token he wants from the market (no choice, pick one per one in order)
				If his choice is impossible, he skip his turn;
			*/

			if(index_first_token_to_pick == -1 && num_token_to_pick != 0) // impossible choice 
			{
				printf("Player id.%d choosed to pick too much tokens, not enough linked token available. Turn skipped.\n" , player_index);
			}else{
				
				struct token_t* picked_tokens[num_token_to_pick]; //stock picked token to execute skills after the turn

				for (int index = 0; index < num_token_to_pick ; ++index)
				{
					struct token_t* picked_token = market->tokens[index_first_token_to_pick+index] ;
					picked_tokens[index] = picked_token;
					player_pick_token(market, current_player, picked_token);
				}

				/*
					Execute associated skills
				*/
				for (int index = 0; index < num_token_to_pick ; ++index)
				{
					skill_exec(current_turn, picked_tokens[index]);
				}
			}
		}

		/*
			End of the turn, display player inventory, game market and game guild to follow the game
		*/

		printf("Current inventory for player id.%d : \n", player_index);
		player_display_inventory(current_player);
		
		printf("══════════════════════════════════════════════════════════════════════\n");
		printf("Market after turn n°%d :\n", turn_index);
		market_display(market);
		printf("Game Guild  : \n");
		guild_display(guild);

		/*
			Give turn to the next player and save the state of the turn
		*/
		next_player(current_turn);
		game_save_turn(&game);

	}
	/*
		End of the game, print results 
	*/
	printf("End of the game !\nResult of the game : ");
	int winner = get_winner(current_turn);

	if (winner <= -1)
	{
		printf("TIE\n");
	}
	else{
		printf("Player id.%d won with %d point(s) !\n", winner, player_get_points(&turn_get_players(current_turn)[winner]));
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
