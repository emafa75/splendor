
#include "test_market.h"
#include "market.h"
#include "token.h"


int test_market()
{
	int test_passed = 0;
	int seed = 0;

	if(test_init_market(seed))
	{
		printf(GRN "test_init_market passed\n" CRESET);
		++test_passed;
	}

	if(test_pick_token(seed))
	{
		printf(GRN "test_pick_token passed\n" CRESET);
		++test_passed;
	}
	if(test_pay_token(seed))
	{
		printf(GRN "test_pay_token passed\n" CRESET);
		++test_passed;
	}
	if(test_get_token(seed))
	{
		printf(GRN "test_get_token passed\n" CRESET);
		++test_passed;
	}


	return test_passed;
}


int test_init_market(int seed)
{
	init_market(seed);
	int n = num_tokens();

	// Test if enough tokens have been created

	if (n > NUM_TOKENS)
	{
		fprintf(stderr, RED "test_init_market: too many tokens have been created.\n" CRESET);
		return 0;
	}


	// Tests if all tokens are actually tokens
	for (int i = 0 ; i < n ; ++i)
	{
		struct token_t *token  = get_token(i);
		if (token == NULL)
		{
			fprintf(stderr, RED "test_init_market: init_builders() don't create the right amount of tokens\n" CRESET);
			return 0;
		}
	}

	return 1;
}

int test_pick_token(int seed)
{
	

	if (!test_init_market(seed))
	{
		fprintf(stderr, RED "test_pick_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}
	init_market(seed);
	market_shuffle();
	struct token_t *picked_token = pick_token(get_available_tokens()->available[0]);
	if( !picked_token ) //if picked_token is NULL
	{
		fprintf(stderr, RED "test_pick_token: no token picked\n" CRESET);
		return 0;
	}
	struct available_tokens *available_tokens = get_available_tokens();
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (available_tokens->available[index] == picked_token)
		{
			fprintf(stderr, RED "test_pick_token: token still present in the market\n" CRESET);
			return 0;
		}
	}

	return 1;
}

int test_pay_token(int seed)
{
	
	if (!test_init_market(seed))
	{
		fprintf(stderr, RED "test_pay_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}
	
	if (!test_pick_token(seed))
	{
		fprintf(stderr, RED "test_pay_token: test_pick_token didn't run successfully\n" CRESET);
		return 0;
	}
	pick_token(get_available_tokens()->available[0]);
	pick_token(get_available_tokens()->available[1]);
	struct token_t* token = pick_token(get_available_tokens()->available[2]);

	pay_token(token);

	struct available_tokens *available_tokens = get_available_tokens();
	int null_count = 0;
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (!available_tokens->available[index])
		{
			++null_count;
		}
		if (available_tokens->available[index] == token)
		{
			if(!null_count) {
				return 1;
			}
			fprintf(stderr, RED "test_pay_token: token is not place on the first available place. %d NULLs before\n" CRESET, null_count);
			return 0;
		}
	}

	fprintf(stderr, RED "test_pay_token: token is not back into the market\n" CRESET);
	return 0;
}

int test_get_token(int seed)
{
	if (!test_init_market(seed))
	{
		fprintf(stderr, RED "test_get_token: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}
	init_market(seed);
	srand(seed);
	//get random token from the market (available or not) and check if it exist
	struct token_t *token = get_token(rand()%NUM_TOKENS);
	if(!token)
	{
		fprintf(stderr, RED "test_get_token: no token_t* return (NULL)\n" CRESET);
		return 0;
	}

	return 1;
}

