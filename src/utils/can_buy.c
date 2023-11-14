
#include "can_buy.h"
#include "builder.h"
#include "guild.h"
#include "market.h"


struct ressources can_buy(struct builder_t *builder_to_buy, struct ressources ressources)
{
	struct ressources out = {};
	struct buildcost_t cost = builder_requires(builder_to_buy);

	// tmp vars for loops
	struct token_t *token;
	struct builder_t *builder;

	unsigned int n_tokens = 0;  // tokens paid so far

	
	// Use builders to pay the cost
	for (int i = 0 ; i < MAX_BUILDERS ; ++i) 
	{
		if (ressources.builders[i] != 0)
		{
			builder = make_builder(i);
			// Tests color
			if (builder_provides(builder).c == cost.c)
			{
				n_tokens++;
				out.builders[i] = 1;
			}
		}

		// End the calculation here if can already buy
		if (n_tokens >= cost.n)
			return out;
	}
	int next_index_to_fill = 0;
	// Use tokens to pay the cost
	for (int i = 0 ; i < NUM_TOKENS ; ++i) 
	{

		if (ressources.tokens[i] != NULL)
		{
			token = ressources.tokens[i];
			// Tests color
			if (token->c[cost.c] != 0)
			{
				n_tokens++;
				out.tokens[next_index_to_fill] = token;
				++next_index_to_fill;
			}
		}

		// End the calculation here if can already buy
		if (n_tokens >= cost.n)
			return out;
	}


	if (n_tokens < cost.n)
	{
		for (int i = 0 ; i < NUM_TOKENS ; ++i)
			out.tokens[i] = NULL;

		for (int i = 0 ; i < MAX_BUILDERS ; ++i)
			out.builders[i] = -1;
	}


	return out;
}

int select_affordable_builder(struct player_t *player)
{
	struct available_builders available_builders = get_available_builders();
	for (int index = 0; index < MAX_BUILDERS ; ++index)
	{
		//get next builder available and check if it's possible to hire it
		if (available_builders.available[index])
		{
			struct builder_t *builder_wanted = make_builder(index);
			if (!(can_buy( builder_wanted, player->ressources).tokens[0] == NULL)) // test if the player can buy it
			{
				return index;
			}
		}
	}
	return -1;
}


