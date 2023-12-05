#include "skills_builders.h"
#include "game.h"


int token_rob(struct turn_t* turn, void* trigger)
{
	//cast trigger to a builder 
	struct builder_t* trigger_builder = trigger;
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
		market_pay_token(&robber_player->ressources.market, robbed_token, identity());
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

int turn_rob(struct turn_t *turn, void *trigger)
{
	UNUSED(trigger);

	next_player(turn);
	
	return 1;
}

int skill_masters_hand(struct turn_t* current_turn, void* trigger)
{
	struct builder_t* builder_bought = trigger;
	struct set_t provides = builder_provides(builder_bought);

	struct player_t* current_player = turn_get_current_player(current_turn);
	struct market_t* current_player_market = &current_player->ressources.market;

	int player_to_steal_index = (current_turn->current_player + 1) % MAX_PLAYERS;
	struct player_t* player_to_steal = &turn_get_players(current_turn)[player_to_steal_index];

	struct market_t* player_to_steal_market = &player_to_steal->ressources.market;

	int num_tokens = market_num_tokens(player_to_steal_market);
	
	struct token_t* filtered_tokens[NUM_TOKENS] = {};
	int filtered_tokens_n = token_filter(player_to_steal_market->tokens, num_tokens, filtered_tokens, provides);

	if (filtered_tokens_n == 0)
		return 0;

	int stolen_token_ind = rand() % filtered_tokens_n;
	struct token_t* token = market_get_token(stolen_token_ind);

	market_pick_token(player_to_steal_market, token);
	market_pay_token(current_player_market, token, identity());

	return 1;
}


