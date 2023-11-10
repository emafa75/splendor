
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

int select_affordable_builder()
{
	struct available_builders available_builders = get_available_builders();
	for (int index = 0; index < available_builders.n_builders_available ; ++index)
	{
		struct available_tokens token_to_buy;
		token_to_buy = *make_builder(available_builders.available[index]).t
		if ()
	}
}


