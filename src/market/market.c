
#include "market.h"
#include "color.h"
#include "set/set.h"
#include "token.h"

static struct token_t tokens[NUM_TOKENS] = {};


struct market_t create_default_market()
{
	struct market_t new_market = {};
	return new_market;
}

void init_market(struct market_t* market, unsigned int seed)
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
			struct set_t set_for_complex_token = {};

			for (int index = 0; index < NUM_COLORS; ++index)
			{
				set_for_complex_token.c[index] = complex_token_colors[index];
			}

			tokens[i] = create_complex_token(set_for_complex_token);	 
		}
		else
		{
			tokens[i] = create_simple_token(color);
		}

		market->tokens[i] = &tokens[i];

		color = (color + 1) % NUM_COLORS;
		++i;
	}

}

int market_get_linked_tokens(struct market_t* market, int nb)
{
	int count = 0;
	int index_first_linked_token = -1;
	for (int index = 0; index < NUM_TOKENS ; ++index)
	{
		if(market->tokens[index])
		{
			++count;
			if (count == nb)
			{
				
				index_first_linked_token = index - nb + 1;
				return index_first_linked_token;
			}
		}
		else {
			count = 0;
		}
	}
	return index_first_linked_token;
}

struct token_t* market_pick_token(struct market_t* market, struct token_t* token)
{
	for (int index  = 0; index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index] == token)
		{
			market->tokens[index] = NULL;
			return token;
		}
	}
	return NULL;
}


struct token_t* market_get_token(int index)
{
	return &tokens[index];
}


void market_pay_token(struct market_t* market, struct token_t * token)
{
	for (int index = 0; index < NUM_TOKENS; ++index)
	{	
		/*
			If the place is available for a new token, put the new token
		*/
		if(!market->tokens[index])
		{
			market->tokens[index]= token;
			return;
		}
	}
}



void market_display(struct market_t* market)
{
	int board_size = sqrt(NUM_TOKENS);
	struct token_t* board[board_size][board_size];
	char * tags[board_size][board_size];
	
	place_token_in_board(market->tokens, board, tags);
	display_board(board,tags);
}



int market_num_tokens(struct market_t* market)
{
	int res = 0;
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (market->tokens[index])
		{
			++res;
		}
	}
	return res;
}

int market_get_first_available_token(struct market_t* market)
{
	if (!market_num_tokens(market))
	{
		return -1;
	}
	for (int index = 0;  index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index])
		{
			return index;
		}
		
	}
	return -1;
}


void market_shuffle(struct market_t* market)
{
	srand(time(NULL));

  	for (int index = 0; index< NUM_TOKENS;++index)
    {
      struct token_t * t_tmp = market->tokens[index];
      int rand_index = index + rand() %  (NUM_TOKENS-index) ;
      market->tokens[index] = market->tokens[rand_index] ;
      market->tokens[rand_index] = t_tmp;
    }
}

int market_is_in_market(struct market_t* market, struct token_t* token)
{
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index] == token)
		{
			return 1;
		}
	}
	return 0;
}
