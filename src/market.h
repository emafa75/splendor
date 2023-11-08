
#ifndef __MARKET_H__
#define __MARKET_H__
#define TOKENS_PER_COLOR 5

#include "token.h"
#include "color.h"

#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdlib.h>
#endif

#endif


struct market {
	struct token_t tokens[NUM_COLORS][TOKENS_PER_COLOR];
	int num_tokens[NUM_COLORS];
};


void init_market();


struct token_t * pick_token(enum color_t color);


void pay_token(struct token_t * token);





