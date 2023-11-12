
#include "market.h"
#include "token.h"
#include <stdio.h>

static struct market market = {};
static struct available_tokens available_tokens;  


void init_market(unsigned int seed)
{
	srand(seed);

	int i = 0;
	enum color_t color = 0;
	enum color_t complex_token_colors[NUM_COLORS] = {};


	while (i < NUM_TOKENS)
	{
		// Create first the complex tokens
		if (i < NUM_COLORS)
		{
			complex_token_colors[(color - 1) % NUM_COLORS] = 0;
			complex_token_colors[color] = 2;

			market.tokens[i] = create_complex_token(complex_token_colors);
			available_tokens.available[i]	= 1;
		}
		else
		{
			market.tokens[i] = create_simple_token(color);
			available_tokens.available[i]	= 1;
		}

		color = (color + 1) % NUM_COLORS;
		++i;
	}

	// for (enum color_t color = 0 ; color < NUM_TOKENS / TOKENS_PER_COLOR ; ++color)
	// {
	// 	for (int j = 0 ; j < TOKENS_PER_COLOR ; ++j)
	// 	{
	// 		market.tokens[color * TOKENS_PER_COLOR + j] = create_simple_token(color);
	// 		available_tokens.available[color * TOKENS_PER_COLOR + j] = 1;
	// 	}
	// }
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
