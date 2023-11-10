
#include "market.h"
#include "token.h"


static struct market market = {};
static struct available_tokens available_tokens;  


void init_market(unsigned int seed)
{
	int i = 0;
	for (enum color_t color = 0 ; color < NUM_TOKENS / TOKENS_PER_COLOR ; ++color)
	{
		for (int j = 0 ; j < TOKENS_PER_COLOR ; ++j)
		{
			i = color * TOKENS_PER_COLOR + j;
			market.tokens[color * TOKENS_PER_COLOR + j] = create_simple_token(color);
			available_tokens.available[color * TOKENS_PER_COLOR + j] = 1;
		}
	}
}


struct token_t * pick_token(int index)
{
	struct token_t *tmp = NULL;

	// Recherche d'un el disponible
	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{
		if (available_tokens.available[i] != 0)
		{
			available_tokens.available[i] = 0;
			return &market.tokens[i];
		}
	}
	
	return NULL;
}


void pay_token(struct token_t * token)
{
	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{
		if (&market.tokens[i] == token)
		{
			available_tokens.available[i] = 1;
			return;
		}
	}
}


struct available_tokens *get_available_tokens()
{
	return &available_tokens;
}





