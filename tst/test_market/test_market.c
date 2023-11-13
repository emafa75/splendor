
#include "test_market.h"


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
	if(test_get_available_tokens(seed))
	{
		printf(GRN "test_get_available_tokens passed\n" CRESET);
		++test_passed;
	}


	return test_passed;
}


int test_init_market(int seed)
{
	init_market(seed);

	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{


	}

	return 1;
}

int test_pick_token(int seed)
{
	init_market(seed);
	return 1;
}

int test_pay_token(int seed)
{
	init_market(seed);
	return 1;
}

int test_get_token(int seed)
{
	init_market(seed);
	return 1;
}

int test_get_available_tokens(int seed)
{
	init_market(seed);
	return 1;
}
