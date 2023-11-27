#ifndef __SKILLS_TOKENS_H__
#define __SKILLS_TOKENS_H__

#include "builder.h"
#include "market.h"
#include "token.h"


/*
    Move a token from the market to an other place in the market. 
    returns -1 if impossible to execute the action 
*/
int market_panic(struct market_t* market, struct token_t* token_to_move, int index_in_market);


/*
    Remove an available builder from the guild, and replace it by a new builder
*/
int guild_panic(struct guild_t* guild, struct builder_t* builder_to_pop);

#endif