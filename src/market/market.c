
#include "market.h"
#include "token.h"
#include <stdio.h>

static struct market market = {};
static struct available_tokens available_tokens = {};  


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
			available_tokens.available[i]	= &market.tokens[i];
		}
		else
		{
			market.tokens[i] = create_simple_token(color);
			available_tokens.available[i]	= &market.tokens[i];
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


struct token_t * pick_token()
{
	for (int index  = 0; index < NUM_TOKENS; ++index)
	{
		if(available_tokens.available[index])
		{
			struct token_t* picked_token = available_tokens.available[index];
			available_tokens.available[index] = NULL;
			return picked_token;
		}
	}
	return NULL;
}


struct token_t* get_token(int index)
{
	return &market.tokens[index];
}


void pay_token(struct token_t * token)
{
	for (int index = 0; index < NUM_TOKENS; ++index)
	{	
		/*
			If the place is available for a new token, put the new token
		*/
		if(!available_tokens.available[index])
		{
			available_tokens.available[index]= token;
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
			token_display(*available_tokens.available[index]," ---- ");
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


void market_shuffle()
{
	srand(time(NULL));

  	for (int index = 0; index< NUM_TOKENS;++index)
    {
      struct token_t * t_tmp = available_tokens.available[index];
      int rand_index = index + rand() %  (NUM_TOKENS-index) ;
      available_tokens.available[index] = available_tokens.available[rand_index] ;
      available_tokens.available[rand_index] = t_tmp;
    }
}