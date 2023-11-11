/**
 *
 * @filename project.c
 * @date 2023-11-07 14:14
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */


#include <stdlib.h>
#include <stdio.h>

#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "can_buy.h"

#define MIN(__x, __y) \
  ((__x) < (__y) ? (__x) : (__y))

#define SEED 0

#define _NB_MIN_PARAMS_ 1

#define MAX_PLAYERS 2
#define POINTS_TO_WIN 12

#define MAX_TURNS 20

void print_usage(char *argv[]);

int next_player(int index);
int get_random_player(int seed);
struct player_t player_list[MAX_PLAYERS];
int has_won(int size, struct player_t players[]);

int main(int argc, char *argv[])
{
	
	srand(SEED);
	if (argc < _NB_MIN_PARAMS_)
	{
		print_usage(argv);
		return EXIT_FAILURE;
	}

	//init player list
	for (int index = 0; index < MAX_PLAYERS ; ++index)
	{
		player_list[index] = init_player();
	}
	
	init_builders(SEED);
	init_market(SEED); //init token
	init_guild();
	guild_display();
	market_display();

	int current_player = get_random_player(SEED);
	int current_turn = 0;

	while (!has_won(MAX_PLAYERS, player_list) && current_turn <= MAX_TURNS)
	{
		int random_choice = rand() % 2; // 0 for hire 1 to take tokens
		int first_affordable_builder_id = select_affordable_builder(&player_list[current_player]);
		if(!random_choice && (first_affordable_builder_id != -1)) //pick hire choice and is able to hire a builder
		{
			printf("Player id.%d choosed to hire\n",current_player);
			player_pay_builder(&player_list[current_player],first_affordable_builder_id);
			player_hire_builder(&player_list[current_player], first_affordable_builder_id);
		}
		else 
		{
			printf("Player id.%d choosed to pick token\n",current_player);
			int num_token_to_pick = rand() % 4; //choose to pick 0 to 3 token
			num_token_to_pick = MIN(num_token_to_pick, num_tokens()); // to be sure to not take more than available token
			printf("Player id.%d choosed to pick %d token(s)" , current_player, num_token_to_pick);
			for (int index = 0; index < num_token_to_pick ; ++index)
			{
				player_take_token(&player_list[current_player], get_first_available_token());
			}
		}
		printf("Current inventory for player id.%d\n", current_player);
		player_display_inventory(&player_list[current_player]);
		current_player = next_player(current_player);
		++current_turn;
		
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

int has_won(int size, struct player_t players[])
{
	for (int index = 0; index < size ; ++index)
	{
		if ( players[index].current_point >= POINTS_TO_WIN )
		{
			return 1;
		}
	}
	return 0;
}
void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s ....\n", argv[0]);
	return;
}
