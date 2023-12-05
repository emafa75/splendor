
#include "market.h"
#include "game.h"
#include "permutation.h"
#include "players.h"
#include "skills.h"
#include "token.h"
#include "token_second_header.h"
#include "board_display.h"
#include <time.h>
#include <stdlib.h>

struct market_t create_default_market()
{
	struct market_t new_market = {
		.permutation = identity()
	};
	return new_market;
}

void init_market(struct market_t* market, unsigned int seed)
{
	int i = 0;

	/*
		Choose a random permutation for the replacement of tokens in the market
	*/
	struct permutation_t market_permutation = random_permutation(seed);
	
	market->permutation = market_permutation;

	while (i < NUM_TOKENS)
	{
		market->tokens[i] = make_token(i);
		++i;
	}

}

void init_tokens_skills()
{
	int nb_tokens = NUM_TOKENS;
	struct token_t* token = NULL;
	/*
		For every tokens
	*/
	for (int index = 0; index < nb_tokens; ++index)
	{
		token = make_token(index);
		enum skills_id skills[MAX_SKILLS_PER_TRIGGER] = {};
		int index_skill_to_add = 0;

		for (enum skills_id skill_id = TOKEN_FIRST_SKILL ; skill_id <= TOKEN_LAST_SKILL ; ++ skill_id)
		{
			if (index_skill_to_add < MAX_SKILLS_PER_TRIGGER) //if we can still add a skill to the current builder
			{
				int random_int = rand() % NUM_TOKENS;
				if(random_int < 1 ) // 1/NUM_TOKEN chance to have the skill
				{
					skills[index_skill_to_add] = skill_id;
					++index_skill_to_add;
					/* printf("Skill %d added on token :\n", skill_id);
					token_display(*token, "This one");
					skill_display(skill_id, " SKILL :");
					printf("\n"); */
				}
			}
		}

		add_skill_instance(token, skills);
	}
}

int market_get_linked_tokens(struct market_t* market, int nb)
{
	int count = 0;
	int index_available[NUM_TOKENS] = {};
	int nb_available = 0;
	for (int index = 0; index < NUM_TOKENS ; ++index)
	{
		if(market->tokens[index])
		{
			++count;
			if (count >= nb)
			{
				
				index_available[nb_available] = index - nb + 1;
				++nb_available;
			}
		}
		else {
			count = 0;
		}
	}


	if (nb_available == 0)
	{
		return -1;
	}
	
	int rand_index = rand() % nb_available;
	return index_available[rand_index];
}

struct token_t* market_pick_token(struct market_t* market, struct token_t* token)
{
	for (int index  = 0; index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index] == token)
		{
			market->tokens[index] = NULL;
			return token;
		}
	}
	return NULL;
}


void market_pay_token(struct market_t* market, struct token_t * token)
{
	struct permutation_t permutation = *market_get_permutation(market);

	for (int index = 0; index < NUM_TOKENS; ++index)
	{	
		/*
			If the place is available for a new token, put the new token
		*/
		if(!market->tokens[permutation.permutation[index]])
		{
			market->tokens[permutation.permutation[index]]= token;
			return;
		}
	}
}



void market_display(struct market_t* market)
{
	int board_size = sqrt(NUM_TOKENS);
	struct token_t* board[board_size][board_size];
	char * tags[board_size][board_size];
	
	place_token_in_board(market->tokens, board, tags);
	display_board(board,tags);
}



int market_num_tokens(struct market_t* market)
{
	int res = 0;
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (market->tokens[index])
		{
			++res;
		}
	}
	return res;
}

int market_get_first_available_token(struct market_t* market)
{
	if (!market_num_tokens(market))
	{
		return -1;
	}
	for (int index = 0;  index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index])
		{
			return index;
		}
		
	}
	return -1;
}


void market_shuffle(struct market_t* market)
{
	srand(time(NULL));

  	for (int index = 0; index< NUM_TOKENS;++index)
    {
      struct token_t * t_tmp = market->tokens[index];
      int rand_index = index + rand() %  (NUM_TOKENS-index) ;
      market->tokens[index] = market->tokens[rand_index] ;
      market->tokens[rand_index] = t_tmp;
    }
}

int market_is_in_market(struct market_t* market, struct token_t* token)
{
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if(market->tokens[index] == token)
		{
			return 1;
		}
	}
	return 0;
}

struct permutation_t* market_get_permutation(struct market_t* market)
{
	return &market->permutation;
}