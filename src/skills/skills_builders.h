#ifndef __SKILLS_BUILDERS_H__
#define __SKILLS_BUILDERS_H__

#include "players.h"
#include "market.h"
#include "builder.h"
#include "game.h"
#include "permutation.h"
#include "players.h"
#include "set.h"



/*
 *  Move the first token that have a color in common with builder_bought.provides
 *  from market to the player
 */
int skill_masters_hand(struct turn_t* current_turn, void* trigger);


/*
 *
 */


#endif
