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


/*
 *  Takes a favor from a random player, return 1 if successfully robs a favor
 *  Returns 0 otherwise
 */
int skill_favor_rob(struct turn_t* turn, const void* trigger);

#endif
