
#include "test_market.h"
#include "market.h"

int test_market()
{
	int i = 0;
	int seed = 0;

	if(test_init_market(seed))
	{
		printf("test_init_market passed");
		++i;
	}

	

	return i;
}


int test_init_market(int seed)
{
	init_market(seed);

	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{


	}

	return 1;
}


