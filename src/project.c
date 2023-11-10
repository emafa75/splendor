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

#define SEED 0

#define _NB_MIN_PARAMS_ 1

#define MAX_PLAYERS 2
#define POINTS_TO_WIN 12

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
	int current_player = get_random_player(SEED);

	while (has_won(MAX_PLAYERS, player_list))
	{
		int random_choice = rand() % 2; // 0 for hire 1 to take tokens
		if(!random_choice)
		{
			struct available_builders available_builders = get_available_builders();
			
		}
		else 
		{

		}
		
	}

	return EXIT_SUCCESS;
}

int next_player(int index)
{
	 return (index + 1) % MAX_PLAYERS;
}

int get_random_player(int seed)
{
	srandom(seed);
	return rand() % MAX_PLAYERS;
}

int has_won(int size, struct player_t players[])
{
	for (int index = 0; index < size ; ++i)
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
