#include "skills_builders.h"

typedef int (*skill_f)(struct turn_t*, void*);

int skill_masters_hand(struct turn_t* current_turn, void* trigger)
{
	struct builder_t* builder_bought = trigger;
	struct set_t provides = builder_provides(builder_bought);
	unsigned int* colors_provides = set_get_colors(&provides);

	struct player_t* player = &current_turn->players[current_turn->current_player];

	struct player_t* player_to_steal = &current_turn->players[(current_turn->current_player + 1) % MAX_PLAYERS];
	struct market_t* player_to_steal_market = &player_to_steal->ressources.market;
	struct market_t* current_player_market = &player->ressources.market;
	
	int num_tokens = market_num_tokens(player_to_steal_market);

	if (num_tokens == 0)
		return 0;

	int stolen_token_ind = rand() % num_tokens;
	struct token_t* token = market_get_token(stolen_token_ind);

	market_pick_token(player_to_steal_market, token);
	market_pay_token(current_player_market, token, identity());

	return 1;
}





