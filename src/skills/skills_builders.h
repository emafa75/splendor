#ifndef __SKILLS_BUILDERS_H__
#define __SKILLS_BUILDERS_H__

#include "game.h"
#include "players.h"
#include "market.h"
#include "builder.h"
#include "game.h"
#include "permutation.h"
#include "players.h"
#include "set.h"

/*
    Rob to a random player, a random token
    Returns 0 if impossible, -1 if success
*/
int token_rob(struct turn_t* turn, void* trigger);
/*
    Skip the turn of the next player
*/
int turn_rob(struct turn_t* turn, void* trigger);



/*
 *  Move the first token that have a color in common with builder_bought.provides
 *  from market to the player
 */
int skill_masters_hand(struct turn_t* current_turn, void* trigger);


/*
 *
 */
int token_filter(struct token_t* tokens[NUM_TOKENS], int n, struct token_t* filtered_tokens[NUM_TOKENS], struct set_t set_filter);

#endif
