#ifndef __MARKET_H__
#define __MARKET_H__

#include <stdlib.h>
#include <stdio.h>
#include "token.h"


#define TOKENS_PER_COLOR NUM_TOKENS


// Used to store all the tokens of the game
struct market {
	struct token_t tokens[NUM_TOKENS];
};

struct available_tokens {
	int available[NUM_TOKENS];
};


void init_market(unsigned int seed);


/*
 * Pick a token from the market
 *
 * Returns  a pointer to an available token if one exists
 *					return NULL otherwise
 */
struct token_t * pick_token(int index);


/*
 * Move a token to the market
 *
 */
void pay_token(struct token_t * token);


struct available_tokens *get_available_tokens();


#endif
