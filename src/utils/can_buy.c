
#include "can_buy.h"
#include "builder.h"
#include "market.h"
#include "players.h"
#include "set.h"
#include "token.h"
#include "token_second_header.h"
#include <stdio.h>


struct ressources can_buy(struct builder_t *builder_to_buy, struct ressources ressources)
{
	struct ressources out = {};
	struct set_t cost = builder_requires(builder_to_buy);
	struct set_t builder_provide;

	struct set_t set_null = {};  // Used to compare to null, if all
	struct set_t to_pay = cost;  // Copy to track what is still needed to pay

	struct set_t token_set;

	// tmp vars for loops
	struct token_t *token;
	struct builder_t *builder;


	int out_builder_index = 0;
	int out_tokens_index = 0;

	// Use builders to pay the cost
	for (int i = 0 ; i < MAX_BUILDERS ; ++i) 
	{
		if (ressources.guild.builders[i] != NULL)  // tests if the pointer is really a builder
		{
			builder = ressources.guild.builders[i];
			builder_provide = builder_provides(builder);
			if (is_usable(&builder_provide, to_pay))  // if builder helps buying builder_to_buy
			{
				// reduce to_pay with builder.provides
				for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
				{
					if (to_pay.c[j] > builder_provide.c[j])
						to_pay.c[j] = to_pay.c[j] - builder_provide.c[j];
					else
						to_pay.c[j] = 0;
				}
				out.guild.builders[out_builder_index] = builder;
				out_builder_index++;
			}
		}

		// End the calculation here if can already buy
		if (set_are_equals(&to_pay, &set_null))
			return out;
	}

	// Use tokens to pay the cost
	for (int i = 0 ; i < NUM_TOKENS ; ++i) 
	{

		if (ressources.market.tokens[i] != NULL)  // Tests if the pointer is really a token
		{
			token = ressources.market.tokens[i];
			// Tests color
			token_set = token_get_set(token);
			if (is_usable(&token_set, to_pay))
			{
				// reduce to_pay with token_set
				for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
				{
					if (to_pay.c[j] > token_set.c[j])
						to_pay.c[j] = to_pay.c[j] - token_set.c[j];
					else
						to_pay.c[j] = 0;
				}

				out.market.tokens[out_tokens_index] = token;
				out_tokens_index++;
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
			out.market.tokens[i] = NULL;

		for (int i = 0 ; i < MAX_BUILDERS ; ++i)
			out.guild.builders[i] = NULL;
	}

	return out;
}


unsigned int is_usable(struct set_t *set, struct set_t cost)
{
	for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
	{
		if (cost.c[j] != 0 && set->c[j] != 0)  // tests if the builder can helps with paying builder_to_buy
			return 1;
	}

	return 0;
}


int cant_buy(struct ressources* can_buy_out)
{
	for (int i = 0 ; i < can_buy_out->guild.n_builders ; ++i)
	{
		if (can_buy_out->guild.builders[i] != NULL)
			return 1;
	}

	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{
		if (can_buy_out->market.tokens[i] != NULL)
			return 1;
	}


	return 0;
}


struct builder_t * select_affordable_builder(struct guild_t* guild, struct player_t *player)
{
	struct builder_t *builder_wanted;

	for (unsigned int index = 0; index < MAX_BUILDERS ; ++index)
	{
		builder_wanted = available_builders_get_builder(guild, index); // get next builder available and check if it's possible to hire it
		if (builder_wanted != NULL)  // test if the player can buy it
		{
			struct ressources can_buy_ressources = can_buy(builder_wanted, *player_get_ressources(player));	
			if (cant_buy(&can_buy_ressources))
			{
				return NULL;
			}
			return builder_wanted;
		}
	}

	return NULL;
}


