
#include "market.h"
#include "token.h"

static struct market market = {};
static struct available_tokens available_tokens;  


void init_market(unsigned int seed)
{
	printf("Seed market : %d\n", seed);
	for (enum color_t color = 0 ; color < NUM_TOKENS / TOKENS_PER_COLOR ; ++color)
	{
		for (int j = 0 ; j < TOKENS_PER_COLOR ; ++j)
		{
			market.tokens[color * TOKENS_PER_COLOR + j] = create_simple_token(color);
			available_tokens.available[color * TOKENS_PER_COLOR + j] = 1;
		}
	}
}


struct token_t * pick_token(int index)
{
	if (available_tokens.available[index] == 0)
		return NULL;
	available_tokens.available[index] = 0;	
	return &market.tokens[index];
}


struct token_t* get_token(int index)
{
	return &market.tokens[index];
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


void market_display()
{
	for (int index = 0; index < NUM_TOKENS ; ++index)
	{
		if(available_tokens.available[index]) 
		{
			token_display(market.tokens[index]," ---- ");
		}
		
	} 
}



int num_tokens()
{
	int res = 0;
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (available_tokens.available[index])
		{
			++res;
		}
	}
	return res;
}

int get_first_available_token()
{
	if (!num_tokens())
	{
		return -1;
	}
	for (int index = 0;  index < NUM_TOKENS; ++index)
	{
		if(available_tokens.available[index])
		{
			return index;
		}
		
	}
	return -1;
}