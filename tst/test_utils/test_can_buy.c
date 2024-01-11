#include <stdio.h>
#include <stdlib.h>


#include "test_can_buy.h"
#include "color.h"
#include "guild.h"
#include "market.h"
#include "ressources.h"
#include "set.h"
#include "token.h"
#include "can_buy.h"
#include "ansi_color.h"
#include "test_guild.h"
#include "test_market.h"



int test_utils()
{
	int test_passed = 0;

	if (test_is_buyable())
	{
		printf(GRN "Test can_buy passed\n" CRESET);
		++test_passed;
	}
	if (test_select_affordable_builder())
	{	
		printf(GRN "Test select_affordable_builder passed\n" CRESET);
		++test_passed;
	}
	return test_passed;
}

int test_is_buyable()
{
	struct ressources_t buyable;

	if (!test_init_guild())
	{
		fprintf(stderr, RED "test_is_buyable: test_init_guild didn't run successfully\n" CRESET);
		return 0;
	}

	if (!test_init_market())
	{
		fprintf(stderr, RED "test_is_buyable: test_init_market didn't run successfully\n" CRESET);
		return 0;
	}

	struct set_t cost = {{1, 2, 2, 1, 1}, NUM_COLORS};

	/* 
		Get the number of ressources in the cost 
	*/
	unsigned int num_ressources = set_num_ressources(&cost);

	/* 
		Stock tokens
	*/

	struct token_t token_to_pay[2 * num_ressources];
	/*
		Empty ressources
	*/
	struct ressources_t ressources = {};
	ressources.guild = create_default_guild();
	ressources.market = create_default_market();

	int index_next_token = 0;

	/*
		Fill ressources with simple tokens
	*/
	for (enum color_t color = 0; color < NUM_COLORS; ++color)
	{
		for (unsigned int index = 0; index < cost.c[color]; ++index)
		{
			token_to_pay[index_next_token] = create_simple_token(color); 

			market_pay_token(&ressources.market, &token_to_pay[index_next_token]);

			++index_next_token;
		}
	}

	/* Test if we can pay the price with simple tokens */
	buyable = is_buyable(cost, ressources);

	if (!can_buy(&buyable))
	{
		fprintf(stderr, RED "test_can_buy: test returns false when trying to pay with simple tokens\n" CRESET);
		return 0;
	}

	/* Remove a token to test if it returns false */
	int random_token_index = market_get_linked_tokens(&ressources.market, 1);
	struct token_t* random_token = market_get_tokens(&ressources.market)[random_token_index];
	market_pick_token(&ressources.market,random_token);

	buyable = is_buyable(cost, ressources);
	if (can_buy(&buyable))
	{
		fprintf(stderr, RED "test_can_buy: test returns true but is impossible to pay the price\n" CRESET);
		return 0;
	}

	/*
		Test if it works with complex tokens
	*/
	ressources.market = create_default_market(); //reset market

	index_next_token = 0;

	for (enum color_t color = 0; color < NUM_COLORS; ++color)
	{
		for (unsigned int index = 0; index < cost.c[color]; ++index)
		{
			struct set_t tmp = {};

			tmp.c[color] = 1; 
			tmp.c[rand() % NUM_COLORS] += 1;

			token_to_pay[index_next_token] = create_complex_token(tmp); 

			market_pay_token(&ressources.market, &token_to_pay[index_next_token]);

			++index_next_token;
		}
	}


	/* Test if we can pay the price with complex tokens */
	buyable = is_buyable(cost, ressources);

	if (!can_buy(&buyable))
	{
		fprintf(stderr, RED "test_can_buy: test returns false when trying to pay with complex tokens\n" CRESET);
		return 0;
	}


	/*
		Test if it returns the best way to pay 
		To do this, we add a complex token with all the colors to pay.
	*/
	token_to_pay[index_next_token] = create_complex_token(cost);
	market_pay_token(&ressources.market,&token_to_pay[index_next_token]);

	++index_next_token;

	buyable = is_buyable(cost, ressources);

	if (market_num_tokens(&buyable.market) > 1) //more than one token to pay
	{
		fprintf(stderr, RED "test_can_buy: doesn't return the best way to pay\n" CRESET);
		market_display(&buyable.market);
		return 0;
	}
	return 1;
}

int test_select_affordable_builder()
{
	return 1;
}
