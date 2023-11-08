
#include "market.h"
#include "token.h"


static struct token_t tokens[NUM_TOKENS] = {};
static struct token_t *available_tokens[NUM_TOKENS] = {};


void init_market()
{
	int i = 0;
	for (enum color_t color = 0 ; color < NUM_TOKENS / TOKENS_PER_COLOR ; ++color)
	{
		for (int j = 0 ; j < TOKENS_PER_COLOR ; ++j)
		{
			i = color * TOKENS_PER_COLOR + j;
			tokens[i] = create_simple_token(color);
			available_tokens[i] = &tokens[i];
		}
	}
}


struct token_t * pick_token(enum color_t color)
{
	
	return NULL;
}


void pay_token(struct token_t * token)
{

}



