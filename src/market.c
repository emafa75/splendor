
#include "market.h"
#include "color.h"
#include "token.h"


static struct market market = {};


static struct color_tokens available_tokens[NUM_COLORS];


void init_market()
{
	int i = 0;
	for (enum color_t color = 0 ; color < NUM_TOKENS / TOKENS_PER_COLOR ; ++color)
	{
		for (int j = 0 ; j < TOKENS_PER_COLOR ; ++j)
		{
			i = color * TOKENS_PER_COLOR + j;
			market.tokens[color][j] = create_simple_token(color);
			available_tokens[color].tokens[i] = &market.tokens[color][j];
		}
	}
}


// int find_available_token(enum color_t color)
// {
// 	return NULL;
// }


struct token_t * pick_token(enum color_t color)
{
	struct token_t *tmp = NULL;

	// Recherche d'un el disponible'
	for (int i = 0 ; i < TOKENS_PER_COLOR ; ++i)
	{
		if (available_tokens[color].tokens[i] != NULL)
		{
			tmp = available_tokens[color].tokens[i];
			available_tokens[color].tokens[i] = NULL;

			return tmp;
		}
	}
	
	return NULL;
}


static int add_token(struct color_tokens * color_tokens, struct token_t *token)
{
	for (int i = 0 ; i < TOKENS_PER_COLOR ; ++i)
	{
		if (color_tokens->tokens[i] == NULL)
		{
			color_tokens->tokens[i] = token;
			return 1;
		}
	}

	return 0;
}


void pay_token(struct token_t * token)
{
	for (int i = 0 ; i < NUM_COLORS ; ++i)
	{
		if (token->c[i] != 0)
		{
			add_token(&available_tokens[i], token);
		}
	}

}



