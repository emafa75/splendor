#ifndef __SKILLS_TOKENS_H__
#define __SKILLS_TOKENS_H__

#include "game.h"


/*
    Move a token from the market to an other place in the market. 
    returns 0 if impossible to execute the action 
*/
int skill_market_panic(struct turn_t* turn, const void* trigger);


/*
    Remove an available builder from the guild, and replace it by a new builder
*/
int skill_guild_panic(struct turn_t* turn, const void* trigger);

#endif