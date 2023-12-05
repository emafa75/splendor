
#include "favors.h"
#include "game.h"
#include "market.h"
#include "players.h"
#include "skills.h"
#include "token.h"

struct skill_instance_t associated_skills[NB_SKILLS_IN_GAME] = {}; 

skill_f skills_functions[NUM_SKILLS] = {
	NULL,
	favor_return,
	favor_renewal
};


char *skills_strings[NUM_SKILLS] = {
	"no skill",
	"favor_return",
	"favor_renewal",
};


int favor_return(struct turn_t *turn, const void *trigger)
{
	UNUSED(trigger);

	struct market_t* global_market = turn_get_market(turn);
	struct player_t* current_player = turn_get_current_player(turn);
	struct token_t* taken_token;

	// Get the index of a random token in global_market
	int token_ind = market_get_linked_tokens(global_market, 1);

	if (token_ind == -1)
		return 0;

	taken_token = global_market->tokens[token_ind];

	player_pick_token(global_market, current_player, taken_token);
	return 1;
}






