#ifndef __TOKEN_SECOND_HEADER_H__
#define __TOKEN_SECOND_HEADER_H__

#include <stdio.h>
#include <string.h>

#include "set.h"
#include "token.h"
#include "ansi_color.h"
#include "color.h"

#include "color_second_header.h"

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
