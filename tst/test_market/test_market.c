
#include "test_market.h"
#include "market.h"
#include "permutation.h"
#include "token.h"
#include "token_second_header.h"
#include "ansi_color.h"

#include <stdlib.h>
#include <stdio.h>

int test_market()
{
	int test_passed = 0;

	if(test_init_market())
	{
		printf(GRN "test_init_market passed\n" CRESET);
		++test_passed;
	}

	if(test_pick_token())
	{
		printf(GRN "test_pick_token passed\n" CRESET);
		++test_passed;
	}
	if(test_market_pay_token())
	{
		printf(GRN "test_market_pay_token passed\n" CRESET);
		++test_passed;
	}
	if(test_market_get_token())
	{
		printf(GRN "test_market_get_token passed\n" CRESET);
		++test_passed;
	}


	return test_passed;
}


int test_init_market()
{
	struct market_t market = create_default_market();
	init_market(&market);

	int n = market_num_tokens(&market);

	// Test if enough tokens have been created

	if (n > NUM_TOKENS)
	{
		fprintf(stderr, RED "test_init_market: too many tokens have been created.\n" CRESET);
		return 0;
	}


	// Tests if all tokens are actually tokens
	for (int i = 0 ; i < n ; ++i)
	{
		struct token_t *token  = make_token(i);
		if (token == NULL)
		{
			fprintf(stderr, RED "test_init_market: init_builders() don't create the right amount of tokens\n" CRESET);
			return 0;
		}
	}

	return 1;
}

int test_pick_token()
{
	

	if (!test_init_market())
	{
		fprintf(stderr, RED "test_pick_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}

	struct market_t market = create_default_market();
	init_market(&market);

	market_shuffle(&market);
	struct token_t *picked_token = market_pick_token(&market, market.tokens[rand() % NUM_TOKENS]);
	if( !picked_token ) //if picked_token is NULL
	{
		fprintf(stderr, RED "test_pick_token: no token picked\n" CRESET);
		return 0;
	}

	if (market_is_in_market(&market, picked_token))
	{
		fprintf(stderr, RED "test_pick_token: token still present in the market\n" CRESET);
		return 0;
	}

	return 1;
}

int test_market_pay_token()
{
	
	if (!test_init_market())
	{
		fprintf(stderr, RED "test_market_pay_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}
	
	if (!test_pick_token())
	{
		fprintf(stderr, RED "test_market_pay_token: test_pick_token didn't run successfully\n" CRESET);
		return 0;
	}
	/*
		Initialize the marker
	*/

	struct market_t market = create_default_market();
	init_market(&market);

	struct token_t* token = market_pick_token(&market, market.tokens[rand() % NUM_TOKENS]); // pick random token
	/*
		Pick new tokens to check if there are replace in the right order (permutation)
	*/
	market_pick_token(&market, market.tokens[rand() % NUM_TOKENS]);
	market_pick_token(&market, market.tokens[rand() % NUM_TOKENS]);

	struct permutation_t* permutation = market_get_permutation(&market);
	market_pay_token(&market, token);
	int null_count = 0;

	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (!market.tokens[permutation->permutation[index]]) //there is a free place
		{
			++null_count;
		}
		if (market.tokens[permutation->permutation[index]] == token)
		{
			if (null_count) 
			{
				fprintf(stderr, RED "test_market_pay_token: token is not place on the first available place. %d NULLs before\n" CRESET, \
				null_count);
				return 0;
			}
			return 1;
		}
	}

	fprintf(stderr, RED "test_market_pay_token: token is not back into the market\n" CRESET);
	return 0;
}

int test_market_get_token()
{
	if (!test_init_market())
	{
		fprintf(stderr, RED "test_market_get_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}
	/*
		Initialize the marker
	*/

	struct market_t market = create_default_market();
	init_market(&market);
	//get random token from the market (available or not) and check if it exist
	struct token_t *token = make_token(rand() % NUM_TOKENS);
	if(!token)
	{
		fprintf(stderr, RED "test_market_get_token: no token_t* return (NULL)\n" CRESET);
		return 0;
	}

	return 1;
}

