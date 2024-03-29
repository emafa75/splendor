
#include "favors.h"
#include "game.h"
#include "market.h"
#include "players.h"
#include "skills.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include "builder_constants.h"
#include "ansi_color.h"


skill_f favors_functions[NUM_FAVOR] = {
	NULL,
	favor_return,
	favor_renewal
};


char *favors_strings[NUM_FAVOR] = {
	"no favors",
	"favor_return",
	"favor_renewal",
};


int favor_return(struct turn_t *turn, const void *trigger)
{
	UNUSED(trigger);

	/*
		Add this favor execution to the context of the turn
	*/
	turn_add_context(turn, GRN "Favor return execute" CRESET);

	struct market_t* global_market = turn_get_market(turn);
	struct player_t* current_player = turn_get_current_player(turn);
	struct token_t* taken_token;

	/*
		If player has already the max of token then stop the execution
	*/
	
	struct market_t* current_player_market = &player_get_ressources(current_player)->market;
	
	if(market_num_tokens(current_player_market) >= PLAYER_MAX_TOKENS)
	{
		turn_add_context(turn, RED "Impossible to initiate the favor, player has already the max of token" CRESET);
		return 0;
	}

	// Get the index of a random token in global_market
	int token_ind = market_get_linked_tokens(global_market, 1);

	if (token_ind == -1)
	{
		turn_add_context(turn, RED "Impossible to initiate the favor, there is no token left in the market" CRESET);
		return 0;
	}

	taken_token = global_market->tokens[token_ind];

	player_pick_token(global_market, current_player, taken_token);
	turn_add_context(turn, GRN "Player pick an extra token from the market" CRESET);

	/*
		Execute skills from the token (if they exist)
	*/
	skill_exec(turn, taken_token);
	DISPLAY(turn->display, trigger_display_skill(taken_token));


	return 1;
}

int favor_renewal(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);
	/*
		Get turn instances
	*/
	struct guild_t* game_guild = turn_get_guild(turn);

	/*
		Choose a random level to renew
	*/
	unsigned int renewed_level = rand() % NUM_LEVELS;

	/*
		Add this favor execution to the context of the turn
	*/
	char buffer[CONTEXT_SIZE] = {};
	sprintf(buffer,GRN "Favor renewal execute. Level %d builders were renewed" CRESET, renewed_level + 1);
	turn_add_context(turn, buffer);

	/*
		Get all the builder with this level wich are available
	*/

	struct available_builders* available_builders = guild_get_available_builders(game_guild);

	struct builder_t* builders[MAX_BUILDERS_AVAILABLE_PER_LVL] = {};
	int index_b = 0;

	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		struct builder_t* builder = available_builders->builders[index];

		if(builder == NULL)
		{
			continue;
		}

		unsigned int builder_lvl = builder_level(builder);
		if (builder_lvl == renewed_level)
		{
			builders[index_b] = builder;
			++index_b;
		}
	}

	/*
		Remove them from the guild and replace it in the queue
	*/

	for (int index = 0; index < MAX_BUILDERS_AVAILABLE_PER_LVL; ++index)
	{
		if( builders[index] == NULL)
		{
			continue;
		}
		guild_pick_builder(game_guild, builders[index]);
		guild_put_builder(game_guild, builders[index]);
	}

	return 1;
}

skill_f favor_by_id(enum favor_id favor_id)
{
	return favors_functions[favor_id];
}

void favor_display(enum favor_id favor_id, char* prefix)
{
	printf("%s%s", prefix,favors_strings[favor_id]);
}