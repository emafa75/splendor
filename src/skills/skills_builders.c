#include "skills_builders.h"
#include "game.h"
#include "market.h"
#include "players.h"
#include "token.h"


int skill_token_rob(struct turn_t* turn, const void* trigger)
{
	//cast trigger to a builder 
	const struct builder_t* trigger_builder = trigger;
	UNUSED(trigger_builder);

	struct player_t* robber_player = turn_get_current_player(turn);
	/*
		Choose random player 
	*/
	int rand_index = rand() % MAX_PLAYERS;
	struct player_t* stolen_player = &turn_get_players(turn)[rand_index];

	while (robber_player == stolen_player) {
		int rand_index = rand() % MAX_PLAYERS;
		stolen_player = &turn_get_players(turn)[rand_index];
	}

	/*
		Choose a random token in target player
	*/

	struct market_t* stolen_player_market = &stolen_player->ressources.market;
	if(market_num_tokens(stolen_player_market) == 0) //no token to steal
	{
		return 0;
	}

	/*
		Choose the first token in stolen player inventory
	*/
	struct token_t* robbed_token = NULL;
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		robbed_token = stolen_player_market->tokens[index];
		if(robbed_token != NULL)
		{
			break;
		}
	}

	//check if the stollen_player has the desired token
	if (market_is_in_market(&stolen_player->ressources.market, robbed_token))
	{
		//Move the robbed token in new inventory and remove it from the stolen player
		market_pick_token(&stolen_player->ressources.market, robbed_token);
		market_pay_token(&robber_player->ressources.market, robbed_token);
		return 1;
	}

	return 0;
}


int token_filter(struct token_t* tokens[NUM_TOKENS], int n, struct token_t* filtered_tokens[NUM_TOKENS], struct set_t set_filter)
{
	int filtered_n = 0;

	for (int i = 0 ; i < n ; ++i)
	{
		struct token_t* token = tokens[i];
		if (token != NULL)
		{
			struct set_t token_set = token_get_set(token);
			struct set_t inter = set_inter(&set_filter, &token_set);
			struct set_t zero = set_zero();
			if (!set_are_equals(&inter, &zero))
				filtered_tokens[filtered_n++] = token;
		}
	}

	return filtered_n;
}

int skill_turn_rob(struct turn_t *turn, const void *trigger)
{
	UNUSED(trigger);

	next_player(turn);
	
	return 1;
}

int skill_masters_hand(struct turn_t* current_turn, const void* trigger)
{
	const struct builder_t* builder_bought = trigger;
	struct set_t provides = builder_provides(builder_bought);

	struct player_t* current_player = turn_get_current_player(current_turn);
	struct market_t* current_player_market = &player_get_ressources(current_player)->market;

	struct market_t* general_market = turn_get_market(current_turn);
	//int num_tokens = market_num_tokens(general_market);
	
	struct token_t* filtered_tokens[NUM_TOKENS] = {};
	int filtered_tokens_n = token_filter(general_market->tokens, NUM_TOKENS, filtered_tokens, provides);

	if (filtered_tokens_n == 0)
		return 0;

	int stolen_token_ind = rand() % filtered_tokens_n;
	struct token_t* token = filtered_tokens[stolen_token_ind];

	market_pick_token(general_market, token);
	market_pay_token(current_player_market, token);

	return 1;
}


