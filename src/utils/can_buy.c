#include "can_buy.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "ressources.h"
#include "players.h"
#include "set.h"
#include "token.h"

#include <stdio.h>


/*
	Test every combinaison of num_desired_token to pay "to_pay"
	Replace best_market with the best combinaison of market to pay "to_pay"
	"test_market" stock the best of the tested market 
*/
void every_combinaison_test(
	int num_tokens,
	int num_desired_token,
	int last_index,
	struct market_t* clean_market,
	struct market_t* best_market,
	struct market_t* test_market,
	struct set_t to_pay
);


unsigned int is_usable(struct set_t *set, struct set_t cost)
{
	for (enum color_t j = 0 ; j < NUM_COLORS ; ++j)
	{
		if (cost.c[j] != 0 && set->c[j] != 0)  // tests if the builder can helps with paying builder_to_buy
			return 1;
	}

	return 0;
}


/*
	Returns 1 if he can buy for a specific ressources generated by can_buy
*/
int can_buy(struct ressources_t* can_buy_out)
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
			struct ressources_t can_buy_ressources = is_buyable(builder_wanted, *player_get_ressources(player));	

			if (can_buy(&can_buy_ressources))
				return builder_wanted;
		}
	}

	return NULL;
}


/*
	Returns 1 if we can pay the set with the provided tokens (stock in the market)
*/
int can_use_market(struct set_t to_pay, struct market_t* market)
{
	struct token_t* token = NULL;
	struct set_t zero = set_zero();

	for (int index = 0 ; index < NUM_TOKENS ; ++index)
	{
		token = market->tokens[index];

		if (token != NULL)
		{
			// reduce to_pay with the token
			for (enum color_t color = 0 ; color < NUM_COLORS ; ++color)
			{
				if (to_pay.c[color] > token->s.c[color])
					to_pay.c[color] = to_pay.c[color] - token->s.c[color];

				else
					to_pay.c[color] = 0;
			}

			/*
				Check if we can already buy it
			*/
			if (set_are_equals(&to_pay, &zero))
				return 1;
		}
	}

	return 0;
}


/*
 *  Returns the sum of the efficiency of every tokens of market to pay to_pay
 *
 *  Efficiency of a token: sum of ressources of the intersection of to_pay with the token
 *		then divided by the num of ressources of the token
 *
 *	Ex: eff of {1, 1, 2, 0, 0} to buy {1, 0, 1, 0, 0}
 *	 	-> returns (1 + 0 + 1 + 0 + 0) / 4 = 1/2
 *	   We only use hald of the token to buy the set
 */
float eff(struct market_t market, struct set_t to_pay)
{
	float out = 0;  // efficiency of market to buy to_pay
	struct set_t* tmp_set;  // Used to store current set in for
	struct set_t tmp_inter;  // Used to compute inter of tmp_set with to_pay

	for (int i = 0 ; i < NUM_TOKENS ; ++i)
	{
		if (market.tokens[i])
		{
			tmp_set = &market.tokens[i]->s;

			tmp_inter = set_inter(tmp_set, &to_pay);
			out += (float)(set_num_ressources(&tmp_inter)) / (float)(set_num_ressources(tmp_set));
		}
	}

	return out;
}


/*
 *  Returns 1 if eff(first_market) < eff(second_market)
 *
 *		 -1 if eff(second_market) < eff(first_market)
 *
 *		  0 if eff(first_market) = eff(second_market)
 */
int market_cmp(struct market_t first_market, struct market_t second_market, struct set_t to_pay)
{
	float first_eff = eff(first_market, to_pay);
	float second_eff = eff(second_market, to_pay);

	if (first_eff < second_eff)
		return 1;

	else if (first_eff > second_eff)
		return -1;

	return 0;
}


/*
 *  Returns first_market if it has better or equal efficiency to buy to_pay than second_market
 */
struct market_t get_best_market(struct market_t first_market, struct market_t second_market, struct set_t to_pay)
{
	if (market_cmp(first_market, second_market, to_pay) == 1)
		return second_market;

	return first_market;
}


struct ressources_t is_buyable(struct builder_t *builder_to_buy, struct ressources_t ressources)
{
	struct set_t cost = builder_requires(builder_to_buy);

	struct ressources_t needed_ressources = {};

	struct guild_t* guild = &ressources.guild;
	struct market_t* market = &ressources.market;


	/*
		Use builders to pay first 
	*/

	//tmp variables
	struct set_t builder_provide;
	struct builder_t* builder;

	for (int index = 0 ; index < MAX_BUILDERS ; ++index)
	{
		builder = guild->builders[index];
		if (builder != NULL)
		{
			/*
				Reduce the cost with the ressources provided by the builder
			*/
			builder_provide = builder_provides(builder);
			for (enum color_t color = 0 ; color < NUM_COLORS ; ++color)
			{
				if (cost.c[color] > builder_provide.c[color])
				{
					cost.c[color] -= builder_provide.c[color];
				}
				else
				{
					cost.c[color] = 0;
				}
			}
		}
	}

	struct set_t to_pay = cost;

	/*
		Create a clean market (all the tokens at the start)
	*/
	struct market_t clean_market = create_default_market();
	
	for (int index = 0 ; index < NUM_TOKENS ; ++index)
	{
		if (market->tokens[index] != NULL)
		{
			market_pay_token(&clean_market, market->tokens[index]);
		}
	}

	/*
		Test every combinaison of token to pay the exact price
	*/
	int num_ressources = set_num_ressources(&to_pay);	

	struct market_t test_market = create_default_market();

	//stock the best tokens to pay
	struct market_t best_market = create_default_market();

	for (int num_desired_token = 1 ; num_desired_token <= num_ressources ; ++num_desired_token)
		every_combinaison_test(market_num_tokens(&clean_market), num_desired_token, 0, &clean_market, &best_market, &test_market, to_pay);

	if (market_num_tokens(&best_market) ==  0)  // Impossible to pay
	{
		/*
			Returns a struct ressources with nothing inside
		*/
		struct ressources_t null_ressources = {};
		
		return null_ressources;
	}

	needed_ressources.market = best_market;

	return needed_ressources;
}


void every_combinaison_test(int num_tokens, int num_desired_token, int last_index, struct market_t* clean_market, struct market_t* best_market, struct market_t* test_market, struct set_t to_pay)
{
	int num_tokens_in_test_market = market_num_tokens(test_market);

	if (num_tokens_in_test_market == num_desired_token)
	{
		if (can_use_market(to_pay, test_market))
		{
			*best_market = get_best_market(*test_market, *best_market, to_pay); 
		}
	}

	else
	{
		for (int index = last_index ; index < num_tokens ; ++index)
		{
			market_pay_token(test_market, clean_market->tokens[index]);
			every_combinaison_test(num_tokens, num_desired_token, index+1, clean_market, best_market, test_market, to_pay);
			market_pick_token(test_market, clean_market->tokens[index]);
		}
	}
}
