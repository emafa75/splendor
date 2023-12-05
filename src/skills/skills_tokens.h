#ifndef __SKILLS_TOKENS_H__
#define __SKILLS_TOKENS_H__

#include "builder.h"
#include "game.h"
#include "market.h"
#include "token.h"
#include "guild.h"
#include "permutation.h"
#include "builder.h"
#include <stdlib.h>


/*
    Move a token from the market to an other place in the market. 
    returns 0 if impossible to execute the action 
*/
int market_panic(struct turn_t* turn, void* trigger);


/*
    Remove an available builder from the guild, and replace it by a new builder
*/
int guild_panic(struct turn_t* turn, void* trigger);

#endif