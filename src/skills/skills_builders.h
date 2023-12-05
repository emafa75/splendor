#ifndef __SKILLS_BUILDERS_H__
#define __SKILLS_BUILDERS_H__

#include "game.h"

/*
    Rob to a random player, a random token
    Returns 0 if impossible, -1 if success
*/
int skill_token_rob(struct turn_t* turn, const void* trigger);
/*
    Skip the turn of the next player
*/
int skill_turn_rob(struct turn_t* turn, const void* trigger);



/*
 *  Move the first token that have a color in common with builder_bought.provides
 *  from market to the player
 */
int skill_masters_hand(struct turn_t* current_turn, const void* trigger);


/*
 *
 */
int token_filter(struct token_t* tokens[NUM_TOKENS], int n, struct token_t* filtered_tokens[NUM_TOKENS], struct set_t set_filter);

#endif
