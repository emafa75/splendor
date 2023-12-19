#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "skills_tokens.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include "builder_constants.h"


int skill_market_panic(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct market_t* market = turn_get_market(turn);


	if( market_num_tokens(market) == 0) // no tokens to move
	{
		return 0;
	}

	/*
		Choose a random token in the market
	*/	
	struct token_t* token_to_move = NULL;
	int rand_index = 0;

	while (token_to_move == NULL) 
	{
		rand_index = rand() % NUM_TOKENS ; 
		token_to_move = market->tokens[rand_index];
	}

	/*
		Find a place to replace it
	*/
	rand_index = rand() % NUM_TOKENS;
	while (market->tokens[rand_index] != NULL)
	{
		rand_index = rand() % NUM_TOKENS;
	}

	/*
		Make the change
	*/
	market_pick_token(market, token_to_move);
	market->tokens[rand_index] = token_to_move;

	return 1;
}


int skill_guild_panic(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct guild_t* guild = turn_get_guild(turn);

	if (guild->available_builders.n_builders_available == 0)
	{
		return 0;
	}

	/*
		Choose a builder to replace
	*/

	int rand_index = 0; 
	struct builder_t* removed_builder = NULL;
	while(removed_builder == NULL)
	{
		rand_index = rand() % (MAX_BUILDERS_AVAILABLE_PER_LVL * NUM_LEVELS) ;
		removed_builder = guild->available_builders.builders[rand_index] ;
	}

	guild_pick_builder(guild, removed_builder);

	return 1;
}



int skill_favor_rob(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct player_t* robber_player = turn_get_current_player(turn);
	struct player_t* stolen_player;
	int rand_index;
	/*
		Choose random player 
	*/
	int num_player = turn_get_num_player(turn);
	rand_index = rand() % num_player;
	stolen_player = &turn_get_players(turn)[rand_index];

	while (robber_player == stolen_player) {
		rand_index = rand() % num_player;
		stolen_player = &turn_get_players(turn)[rand_index];
	}

	if (stolen_player->favor)
	{
		stolen_player->favor--;
		robber_player->favor++;
		return 1;
	}

	return 0;
}

