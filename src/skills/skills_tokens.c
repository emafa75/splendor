#include "game.h"
#include "skills_tokens.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "token.h"
#include "builder_constants.h"
#include "ansi_color.h"

#include <stdlib.h>
#include <stdio.h>

int skill_market_panic(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct market_t* market = turn_get_market(turn);

	/*
		Add to context
	*/
	turn_add_context(turn, GRN "Skill market panic execute" CRESET);
	
	if( market_num_tokens(market) == 0) // no tokens to move
	{	
		turn_add_context(turn, RED "No token to move in the market" CRESET);
		return 0;
	}

	/*
		Choose a random token in the market
	*/	
	int rand_index = market_get_linked_tokens(market,1);
	struct token_t* token_to_move = market->tokens[rand_index];

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

	turn_add_context(turn, GRN "Token was moved to a new place in the market" CRESET);
	return 1;
}


int skill_guild_panic(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct guild_t* guild = turn_get_guild(turn);

	/*
		Add to context
	*/
	turn_add_context(turn, GRN "Skill guild panic execute" CRESET);

	if (guild->available_builders.n_builders_available == 0)
	{
		turn_add_context(turn,RED "Impossible to execute skill because no builder are available in global guild" CRESET);
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
	/* Replace it in the queue of available builders */
	guild_put_builder(guild, removed_builder);

	turn_add_context(turn,GRN "A builder was replace from the global guild" CRESET);

	return 1;
}



int skill_favor_rob(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	struct player_t* robber_player = turn_get_current_player(turn);
	struct player_t* stolen_player;
	int rand_index;
	char buffer[CONTEXT_SIZE] = {};

	/*
		Add to context
	*/
	turn_add_context(turn,GRN "Skill favor rob execute" CRESET);

	/*
		Choose random player 
	*/
	int num_player = turn_get_num_player(turn);
	rand_index = rand() % num_player;
	stolen_player = &turn_get_players(turn)[rand_index];

	while (robber_player == stolen_player)
	{
		rand_index = rand() % num_player;
		stolen_player = &turn_get_players(turn)[rand_index];
	}

	if (stolen_player->favor)
	{
		stolen_player->favor--;
		robber_player->favor++;

		sprintf(buffer, GRN "Player took a favor from player id.%d" CRESET, player_get_id(stolen_player));
		turn_add_context(turn,buffer);

		return 1;
	}

	turn_add_context(turn,RED "Targeted player had no favor" CRESET);

	return 0;
}

