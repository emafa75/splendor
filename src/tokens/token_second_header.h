#ifndef __TOKEN_SECOND_HEADER_H__
#define __TOKEN_SECOND_HEADER_H__

#include "set.h"
#include "token.h"
#define MAX_COLORS_PER_TOKENS 2


/*
    Print very short display for token
*/
void token_short_diplay(struct token_t t);

/*
    Get the set from a token
*/
struct set_t token_get_set(struct token_t *token);

/*
    Init tokens with a specific seed
*/
void init_tokens(unsigned int seed);


/*
    Returns the `index`-th token, and NULL if it does not exist.
*/
struct token_t* make_token(unsigned int index);

#endif
