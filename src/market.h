#ifndef __MARKET_H__
#define __MARKET_H__


#include <stdlib.h>
#include "token.h"

#define TOKENS_PER_COLOR NUM_TOKENS


// Used to store all the tokens of the game
struct market {
	struct token_t tokens[NUM_COLORS][TOKENS_PER_COLOR];
	int num_tokens[NUM_COLORS];
};


// Used to store tokens of a given color
struct color_tokens {
	struct token_t *tokens[TOKENS_PER_COLOR];
};


void init_market(unsigned int seed);


/*
 * Pick a token from the market
 *
 * Returns  a pointer to an available token if one exists
 *					return NULL otherwise
 */
struct token_t * pick_token(enum color_t color);


/*
 * Move a token to the market
 *
 */
void pay_token(struct token_t * token);

/*
 *
 * Returns	1 if successfully add a token
 *					0 otherwise
 */
static int add_token(struct color_tokens * color_tokens, struct token_t *token);


#endif
