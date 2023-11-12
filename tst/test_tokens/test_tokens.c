
#include "test_tokens.h"


int test_token()
{
	int i = 0;

	if(test_create_simple_token())
	{
		printf("test_create_simple_token passed");
		++i;
	}

	if(test_create_complex_token())
	{
		printf("test_create_complex_token passed");
		++i;
	}

	if(test_token_equals())
	{
		printf("test_token_equals passed");
		++i;
	}

	return i;
}


int test_token_legal(struct token_t token)
{
	int acc = 0;

	for (int i = 0 ; i < NUM_COLORS ; ++i)
	{
		printf("i:%d\n", i);
		acc += token.c[i];
		if (token.c[i] > 1)
		{
			fprintf(stderr, "test_token_legal: illegal color value: value=%d for color=%s\n", token.c[i], color_to_short_string(i));
			return 0;
		}
		printf("i:%d\n", i);
	}

	printf("test");
	if (acc <= 0)
	{
		fprintf(stderr, "test_token_legal: token has less than 1 color: num_color=%d\n", acc);
		return 0;
	}

	return 1;
}


// Tests if init is executable and create all builders
int test_create_simple_token()
{
	struct token_t token = create_simple_token(0);

	if (!test_token_legal(token))
	{
		fprintf(stderr, "test_create_simple_token: ");
		return 0;
	}

	return 1;
}

// Tests if init is executable and create all builders
int test_create_complex_token()
{
	struct token_t token = create_complex_token(0);

	if (!test_token_legal(token))
	{
		fprintf(stderr, "test_create_complex_token: ");
		return 0;
	}

	return 1;
}


int test_token_equals()
{
	struct token_t token1 = create_simple_token(0);
	struct token_t token2 = create_simple_token(1);
	struct token_t token3 = create_simple_token(1);

	if (token_equals(token1, token2))
	{
		fprintf(stderr, "test_token_equals: tokens are detected as equals but shouldn't be\n");
		token_display(token1, "token1=");
		token_display(token2, "token2=");
		return 0;
	}

	if (token_equals(token2, token3))
	{
		fprintf(stderr, "test_token_equals: tokens are detected as different but are the same\n");
		token_display(token2, "token2=");
		token_display(token3, "token3=");
		return 0;
	}


	return 1;
}


