#include "skills_builders.h"


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
