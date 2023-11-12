#ifndef __MARKET_H__
#define __MARKET_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "token.h"
#include "builder.h"


#define TOKENS_PER_COLOR 5


// Used to store all the tokens of the game
struct market {
	struct token_t tokens[NUM_TOKENS];
};

struct available_tokens {
	int available[NUM_TOKENS];
};

struct ressources {
	int tokens[NUM_TOKENS];
	int builders[MAX_BUILDERS];
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


/*
 *  Returns the index-th token
 */
struct token_t* get_token(int index);


struct available_tokens *get_available_tokens();

/*
	Display all available token in the market
*/
void market_display();

/*
	Returns number of token avalable in market
*/

int num_tokens();

/*
	Return position from the first available token, -1 if impossible
*/
int get_first_available_token();

#endif
