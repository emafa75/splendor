
#include "can_buy.h"
#include "builder.h"
#include "set.h"
#include "token_second_header.h"


struct ressources can_buy(struct builder_t *builder_to_buy, struct ressources ressources)
{
	struct ressources out = {};
	struct set_t cost = builder_requires(builder_to_buy);
	struct set_t builder_provide;

	struct set_t set_null = {};
	struct set_t to_pay = cost;  // Copy to track what is still needed to pay

	struct set_t token_set;

	int ressources_builder_index = 0;

	// tmp vars for loops
	struct token_t *token;
	struct builder_t *builder;

	unsigned int n_tokens = 0;  // tokens paid so far

	
	// Use builders to pay the cost
	for (int i = 0 ; i < MAX_BUILDERS ; ++i) 
	{
		if (ressources.builders[i] != NULL)  // tests if the pointer is really a builder
		{
			builder = ressources.builders[i];
			builder_provide = builder_provides(builder);
			if (is_usable(&builder_provide, cost))  // if builder helps buying builder_to_buy
			{
				// reduce to_pay with builder.provides
				for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
				{
					to_pay.c[j] = (to_pay.c[j] - builder_provide.c[j]) < 0 ? 0: to_pay.c[j] - builder_provide.c[j];
				}
			}
		}

		// End the calculation here if can already buy
		if (set_are_equals(&to_pay, &set_null))
			return out;
	}

	int next_index_to_fill = 0;
	// Use tokens to pay the cost
	for (int i = 0 ; i < NUM_TOKENS ; ++i) 
	{

		if (ressources.tokens[i] != NULL)  // Tests if the pointer is really a token
		{
			token = ressources.tokens[i];
			// Tests color
			token_set = token_get_set(token);
			if (is_usable(&token_set, cost))
			{
				// reduce to_pay with token_set
				for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
				{
					to_pay.c[j] = (to_pay.c[j] - token_set.c[j]) < 0 ? 0: to_pay.c[j] - token_set.c[j];
				}
			}
		}

		// End the calculation here if can already buy
		if (set_are_equals(&to_pay, &set_null))
			return out;
	}


	// If can't buy, set all pointers of out to null
	if (!set_are_equals(&to_pay, &set_null))
	{
		for (int i = 0 ; i < NUM_TOKENS ; ++i)
			out.tokens[i] = NULL;

		for (int i = 0 ; i < MAX_BUILDERS ; ++i)
			out.builders[i] = NULL;
	}

	return out;
}


unsigned  int is_usable(struct set_t *set, struct set_t cost)
{
	for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
	{
		if (cost.c[j] != 0 && set->c[j] != 0)  // tests if the builder can helps with paying builder_to_buy
			return 1;
	}

	return 0;
}


struct builder_t * select_affordable_builder(struct player_t *player)
{
	struct builder_t *builder_wanted;

	for (unsigned int index = 0; index < MAX_BUILDERS ; ++index)
	{
		builder_wanted = available_builders_get_builder(index); // get next builder available and check if it's possible to hire it
		if (builder_wanted != NULL && can_buy(builder_wanted, player->ressources).tokens[0] != NULL)  // test if the player can buy it
		{
			return builder_wanted;
		}
	}

	return NULL;
}


