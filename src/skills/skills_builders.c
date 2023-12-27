#include "skills_builders.h"
#include "game.h"
#include "market.h"
#include "players.h"
#include "skills.h"
#include "token.h"
#include "set.h"
#include "ansi_color.h"

#include <stdio.h>
#include <stdlib.h>

int skill_token_rob(struct turn_t* turn, const void* trigger)
{
	//cast trigger to a builder 
	const struct builder_t* trigger_builder = trigger;
	UNUSED(trigger_builder);

	char buffer[CONTEXT_SIZE] = {};

	/*
		Add skill execution to the context
	*/
	turn_add_context(turn, GRN "Skill token rob execute." CRESET);

	struct player_t* robber_player = turn_get_current_player(turn);

	/*
		If player has already the max of token then stop the execution
	*/

	struct market_t* current_player_market = &player_get_ressources(robber_player)->market;
	
	if (market_num_tokens(current_player_market) >= PLAYER_MAX_TOKENS)
	{
		turn_add_context(turn, RED  "Impossible to execute the skill, player has already the max of token" CRESET);
		return 0;
	}
	/*
		Choose random player 
	*/
	int num_player = turn_get_num_player(turn);
	int rand_index = rand() % num_player;
	struct player_t* stolen_player = &turn_get_players(turn)[rand_index];

	while (robber_player == stolen_player) {
		int rand_index = rand() % num_player;
		stolen_player = &turn_get_players(turn)[rand_index];
	}

	/*
		Choose a random token in target player
	*/

	struct market_t* stolen_player_market = &stolen_player->ressources.market;
	if(market_num_tokens(stolen_player_market) == 0) //no token to steal
	{
		turn_add_context(turn, RED  "No token to steal in stolen player inventory" CRESET);
		return 0;
	}

	/*
		Choose a random token to pick in stolen player inventory
	*/
	int index_robbed_token = market_get_linked_tokens(stolen_player_market, 1);
	struct token_t* robbed_token = stolen_player_market->tokens[index_robbed_token];
	

	//check if the stollen_player has the desired token
	if (market_is_in_market(&stolen_player->ressources.market, robbed_token))
	{
		//Move the robbed token in new inventory and remove it from the stolen player
		market_pick_token(&stolen_player->ressources.market, robbed_token);
		market_pay_token(&robber_player->ressources.market, robbed_token);

		/* Add action to the context */
		sprintf(buffer,GRN "Player robbed a token to player id.%d" CRESET, player_get_id(stolen_player));
		turn_add_context(turn,buffer);

		return 1;
	}

	return 0;
}


int skill_turn_rob(struct turn_t *turn, const void *trigger)
{
	UNUSED(trigger);
	unsigned int num_player = turn_get_num_player(turn);
	unsigned int next_player_index = turn_get_next_player_index(turn);

	turn_set_next_player(turn, (next_player_index + 1) % num_player);

	/* Add to the context */
	turn_add_context(turn,GRN "Skill turn rob execute. Next player will skip his turn." CRESET);
	
	return 1;
}

int skill_masters_hand(struct turn_t* turn, const void* trigger)
{
	const struct builder_t* builder_bought = trigger;
	struct set_t provides = builder_provides(builder_bought);

	struct player_t* current_player = turn_get_current_player(turn);
	struct market_t* current_player_market = &player_get_ressources(current_player)->market;
	
	/*
		Add to the context 
	*/
	turn_add_context(turn,GRN "Skill master hand execute." CRESET);

	/*
		If player has already the max of token then stop the execution
	*/

	if(market_num_tokens(current_player_market) >= PLAYER_MAX_TOKENS)
	{
		turn_add_context(turn,RED "Impossible to execute the skill, player has already the max of token" CRESET);
		return 0;
	}

	struct market_t* global_market = turn_get_market(turn);
	
	struct token_t* filtered_tokens[NUM_TOKENS] = {};
	int filtered_tokens_n = market_get_tokens_filtered(global_market, filtered_tokens, provides);

	if (filtered_tokens_n == 0)
	{
		turn_add_context(turn, RED "Market has no token that are provided by the hired builder" CRESET);
		return 0;
	}
	int stolen_token_ind = rand() % filtered_tokens_n;
	struct token_t* token = filtered_tokens[stolen_token_ind];

	market_pick_token(global_market, token);
	market_pay_token(current_player_market, token);


	/*
		Add to the context
	*/
	turn_add_context(turn, GRN "Player took a token from the market that was provided by the builder" CRESET);

	/*
		Execute skills from the token (if they exist)
	*/
	skill_exec(turn, token);
	DISPLAY(turn->display, trigger_display_skill(token));

	return 1;
}


int skill_gentry_master(struct turn_t* turn, const void* trigger)
{
	UNUSED(trigger);

	/*
		Get instances
	*/

	struct player_t* current_player = turn_get_current_player(turn);

	/*
		Add favor to the player
	*/

	player_set_favor(current_player, player_get_favor(current_player) + 1 );

	/*
		Add to the context 
	*/
	turn_add_context(turn,GRN "Skill gentry master execute. Player won an extra favor" CRESET);

	return 1;
}
