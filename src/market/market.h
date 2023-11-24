#ifndef __MARKET_H__
#define __MARKET_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "token.h"
#include "builder.h"
#include "board_display.h"
#include "guild.h"

#define TOKENS_PER_COLOR 5


// Used to store all the tokens of the game
struct market {
	struct token_t* tokens[NUM_TOKENS];
};

struct available_tokens {
	struct token_t* available[NUM_TOKENS];
};

struct ressources {
	struct market market;
	struct guild guild;
};

/*
	Init the initial market for the game.
*/
void init_market(unsigned int seed);


/*
 * Pick a specific token from the market
 *
 * Returns  a pointer to an available token if one exists
 *					return NULL otherwise

	Remove it from the market
 */
struct token_t* market_pick_token(struct market* market, struct token_t* token);


/*
 * Move a token to the market
 *
 */
void market_pay_token(struct market* market, struct token_t * token);


/*
 *  Returns the index-th token
 */
struct token_t* market_get_token(int index);


struct available_tokens *get_available_tokens();

/*
	Display all available token in the market
*/
void market_display(struct market* market);

/*
	Returns number of token avalable in market
*/

int market_num_tokens(struct market* market);

/*
	Return position from the first available token, -1 if impossible
*/
int market_get_first_available_token(struct market* market);

/*
	Shuffle the market, decide the path of the board
*/
void market_shuffle(struct market* market);

/*
	Get the index (in available list) from first available token of a group of nb-linked tokens, -1 if impossible
*/
int market_get_linked_tokens(struct market* market, int nb);


/*
	Returns a default market
*/
struct market create_default_market();
#endif
