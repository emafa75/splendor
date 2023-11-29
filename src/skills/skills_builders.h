#ifndef __SKILLS_BUILDERS_H__
#define __SKILLS_BUILDERS_H__

#include "game.h"
#include "players.h"
#include "token.h"
#include "permutation.h"
#include "builder.h"
#include "market.h"

/*
    Rob to a random player, a random token
    Returns 0 if impossible, -1 if success
*/
int token_rob(struct turn_t* turn, void* trigger);

#endif