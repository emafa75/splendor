#ifndef __MARKET_H__
#define __MARKET_H__

#include "permutation.h"
#include "token.h"


#define TOKENS_PER_COLOR 5


// Used to store all the tokens of the game
struct market_t {
	struct token_t* tokens[NUM_TOKENS];
	struct permutation_t permutation;
};

/*
	Init the initial market for the game.
*/
void init_market(struct market_t* market);


/*
	Associate skill to every token present in array tokens
*/
void init_tokens_skills();


/*
 * Pick a specific token from the market
 *
 * Returns  a pointer to an available token if one exists
 *					return NULL otherwise
 *
 * Remove it from the market
 */
struct token_t* market_pick_token(struct market_t* market, struct token_t* token);


/*
 * Move a token to the market, apply a permutation to the order of priority to place token
 *
 */
void market_pay_token(struct market_t* market, struct token_t * token);


/*
	Display all available token in the market
*/
void market_display(struct market_t* market);


/*
	Returns number of token avalable in market
*/
int market_num_tokens(struct market_t* market);


/*
	Return position from the first available token, -1 if impossible
*/
int market_get_first_available_token(struct market_t* market);


/*
	Shuffle the market, decide the path of the board
*/
void market_shuffle(struct market_t* market);


/*
	Get the index from a available token of a group of nb-linked tokens, -1 if impossible
*/
int market_get_linked_tokens(struct market_t* market, int nb);


/*
	Returns market permutation
*/
struct permutation_t* market_get_permutation(struct market_t* market);


/*
	Returns a default market
*/
struct market_t create_default_market();


/*
	Check if a specific token is in market (1 if true else 0)
*/
int market_is_in_market(struct market_t* market, struct token_t* token);


/*
 *  Returns int n, the size of filtered_tokens
 *  The first n elements of token_t* filtered_tokens are pointers to tokens that
 *  are available and have a color in common with set_filter
 *
 */
int market_get_tokens_filtered(struct market_t* market, struct token_t* filtered_tokens[NUM_TOKENS], struct set_t set_filter);

/*
	Returns the list of tokens_t* from a market
*/
struct token_t** market_get_tokens(struct market_t* market);
#endif
