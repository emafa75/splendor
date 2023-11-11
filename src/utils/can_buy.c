
#include "can_buy.h"
#include "builder.h"
#include "guild.h"
#include "market.h"


struct available_tokens can_buy(struct builder_t *builder, int available_tokens[NUM_TOKENS])
{
	struct available_tokens out = {};
	struct buildcost_t cost = builder_requires(builder);

	struct token_t *token;
	unsigned int n_tokens = 0;  // tokens paid so far

	for (int i = 0 ; i < NUM_TOKENS ; ++i) 
	{
		if (available_tokens[i] != 0)
		{
			token = get_token(i);
			// Tests color
			if (token->c[cost.c] != 0)
			{
				n_tokens++;
				out.available[i] = 1;
			}
		}
	}


	if (n_tokens < cost.n)
	{
		for (int i = 0 ; i < NUM_TOKENS ; ++i)
			out.available[i] = -1;
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
			if (!(can_buy( builder_wanted, player->index_token_list).available[0] == -1)) // test if the player can buy it
			{
				return index;
			}
		}
	}
	return -1;
}


