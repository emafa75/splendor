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

#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "can_buy.h"
#include <unistd.h>
#include <getopt.h>
#define MIN(__x, __y) \
  ((__x) < (__y) ? (__x) : (__y))

#define DEFAULT_SEED 2

#define _NB_MIN_PARAMS_ 1

#define MAX_PLAYERS 2


enum choice{
	HIRE,
	PICK,
	NUM_CHOICE,
	FIRST_CHOICE = HIRE
};

enum parameters{
	MAX_TURNS = 20,
	POINTS_TO_WIN = 10,
	RANDOM_SEED = 0,
	BUILDER_SEEED = 0,
	MARKET_SEED = 0,
};
struct player_t player_list[MAX_PLAYERS];

void print_usage(char *argv[]);
/*
	Returns next player index
*/
int next_player(int index);
/*
	Gets a random player index
*/
int get_random_player(int seed);
/*
	Check if if someone won the game, return 1 if true
*/
int has_won(int size, struct player_t players[]);
/*
	Returns winner's index, -1 if tie
*/
int get_winner(int size, struct player_t[]);
/*
	Display options for the game
*/
void display_options();


/*
		Init all options 
*/
int max_turns = MAX_TURNS ;
enum  parameters points_to_win = POINTS_TO_WIN;
enum  parameters random_seed = RANDOM_SEED;
enum  parameters builder_seed = BUILDER_SEEED;
enum  parameters market_seed = MARKET_SEED;


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
				random_seed = atoi(optarg);
				break;
			case 'm':
				max_turns = atoi(optarg);
				break;
			case 'c':
				builder_seed = atoi(optarg);
				break;
			case 'p':
				points_to_win = atoi(optarg);
				break;
			default: 
				print_usage(argv);
				return EXIT_FAILURE;

		}
	}
	display_options();
	srand(random_seed);
	/*
		Init all instances
	*/
	init_builders(builder_seed);
	init_market(market_seed); //init token
	init_guild();
	guild_display();
	market_display();

	/*
		Init first player and current turn
	*/
	int current_player = get_random_player(random_seed);
	int current_turn = 0;

	/*
		Init list of players with MAX_PLAYERS in game
	*/
	for (int index = 0; index < MAX_PLAYERS ; ++index)
	{
		player_list[index] = init_player();
	}

	/*
		Game loop
	*/
	while (!has_won(MAX_PLAYERS, player_list) && current_turn <= max_turns)
	{
		printf("=============================================================\n");
		printf("Turn n°%d\n", current_turn);

		/*
			Take a random decision and check if it's possible to hire a builder
		*/
		enum choice random_choice = rand() % NUM_CHOICE; 
		int first_affordable_builder_id = select_affordable_builder(&player_list[current_player]);


		if((random_choice == HIRE) && (first_affordable_builder_id != -1)) 
		{
			/*
				The player choosed to hire a builder and is able to do so
			*/
			printf("Player id.%d choosed to hire\n",current_player);
			player_pay_builder(&player_list[current_player],first_affordable_builder_id);
			player_hire_builder(&player_list[current_player], first_affordable_builder_id);
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
			num_token_to_pick = MIN(num_token_to_pick, num_tokens());
			printf("Player id.%d choosed to pick %d token(s)\n" , current_player, num_token_to_pick);

			/*
				Pick the number of token he wants from the market (no choice, pick one per one in order)
			*/
			for (int index = 0; index < num_token_to_pick ; ++index)
			{
				player_pick_token(&player_list[current_player], get_first_available_token());
			}
		}

		/*
			End of the turn, display player inventory to follow the game
		*/

		printf("Current inventory for player id.%d : \n", current_player);
		player_display_inventory(&player_list[current_player]);

		/*
			Give turn to the next player
		*/
		current_player = next_player(current_player);
		++current_turn;
		printf("=============================================================\n");

	}
	/*
		End of the game, print results 
	*/
	printf("End of the game !\nResult of the game : ");
	int winner = get_winner(MAX_PLAYERS, player_list);

	if (winner < -1)
	{
		printf("TIE\n");
	}
	else{
		printf("Player id.%d won with %d point(s) !\n", winner, player_list[winner].current_point);
	}


	return EXIT_SUCCESS;
}

int next_player(int index)
{
	 return (index + 1) % MAX_PLAYERS;
}

int get_random_player(int seed)
{
	srand(seed);
	return rand() % MAX_PLAYERS;
}

/*
	Return a boolean to see if a player has won
*/
int has_won(int size, struct player_t players[])
{
	for (int index = 0; index < size ; ++index)
	{
		if ( players[index].current_point >= points_to_win )
		{
			return 1;
		}
	}
	return 0;
}

/*
	Return winner id, -1 if tie
*/
int get_winner(int size, struct player_t players[])
{
	int id_max_points = 0;
	
	for (int index = 0; index < size; ++index)
	{
		int player_point = players[index].current_point;
		if (player_point >= points_to_win)
		{
			return index;
		}
		if (player_point > players[id_max_points].current_point) 
		{
			id_max_points = index;
		}
	}

	int max_points = players[id_max_points].current_point;
	for (int index = 0; index < size; ++index)
	{
		if((index != id_max_points) && (max_points == players[index].current_point))
		{
			return -1;
		}
	}
	return id_max_points;

}

void display_options()
{
	printf("Random seed : %d\nBuilder seed : %d\nMarket seed : %d\nPoints to win a game : %d\nMax turns : %d\n", 
	random_seed,
	builder_seed,
	market_seed,
	points_to_win,
	max_turns
	);
}

void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s [-s random_seed] [-m max_turns] [-c builder_seed] [-p points_to_win]\n", argv[0]);
	return;
}
