#include "players.h"
#include "ansi_color.h"
#include "can_buy.h"
#include "color.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include "skills.h"
#include "permutation.h"


struct player_t init_player()
{
	struct player_t new_player = {
		.ressources={
			.market = create_default_market(),
			.guild = create_default_guild()
		}, 
		.current_point=0,
		.favor =  1,
	};
	return new_player;
}


void player_pick_token(struct market_t* market, struct player_t* player, struct token_t* picked_token){
	/*
		Can't take more token
	*/
	if(market_num_tokens(&player_get_ressources(player)->market) >= PLAYER_MAX_TOKENS)
	{
		return;
	}
	
	struct token_t* token = market_pick_token(market, picked_token);
	if (token == NULL)
	{
		return;
	}
	
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		/*
			Find a place to stock the token
		*/
		if(!player->ressources.market.tokens[index])
		{
			player->ressources.market.tokens[index] = picked_token;
			return;
		}
	}
}


void player_take_token(struct market_t* market, struct player_t* player, struct token_t * token){
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if (player->ressources.market.tokens[index] == token)
		{
			market_pay_token(market, token);
			player->ressources.market.tokens[index] = NULL;
			return;
		}
	} 
 
}

void player_hire_builder(struct guild_t* guild, struct player_t *player,struct builder_t* builder_to_hire)
{
	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		/*
			Look for place in player inventory
		*/
		if(player->ressources.guild.builders[index] == NULL)
		{
			player->ressources.guild.builders[index] = builder_to_hire;
			++player->ressources.guild.n_builders ;
			player->current_point += builder_points(builder_to_hire);
			guild_pick_builder(guild, builder_to_hire);
			return;
		}
	}
   
}


void player_display_inventory(struct player_t *player)
{   
	/*
		Points
	*/
	unsigned int points = player_get_points(player);
	printf(BOLD "Point(s) : " HYEL "%d\n\n" CRESET , points );

	/*
		Favors
	*/
	unsigned int favor = player_get_favor(player);
	printf(BOLD "Favor(s) : " CRESET);
	printf(favor ?  BYEL "%d\n\n"  CRESET:  WHT "No favor\n\n" CRESET , favor );
	struct ressources* player_ressources = player_get_ressources(player);

	/*
		Tokens
	*/
	printf(BOLD "Tokens : \n" CRESET);
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		struct token_t* token = player_ressources->market.tokens[index];
		if(token)
		{
			token_display(*token, " --- ");
			/*
				If the token has skills (impossible to print in token_display because we don't have access to the token pointer)
			*/			
			if (has_skills(token))
			{
				printf(" skill(s)=");
				enum skills_id* skills = skills_get_by_trigger(token);
				for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
				{
					if (skills[index] != NO_SKILL)
					{
						skill_display(skills[index],(index != 0) ? ", " : "");
					}
				}

			}
			printf(")\n");
		}
	}
	if(market_num_tokens(&player_ressources->market) == 0 )
	{
		printf(WHT " --- No token\n" CRESET);
	}
	printf("\n");

	/*
		Builders
	*/
	printf(BOLD "Builders : \n" CRESET );
	for (unsigned int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(player->ressources.guild.builders[index]) {
			builder_display(player_ressources->guild.builders[index]," --- ");
		}
	}
	if (guild_nb_builder(&player_ressources->guild) == 0)
	{
		printf(WHT " --- No builder\n" CRESET);
	}
}


int player_pay_builder(struct market_t* market, struct player_t* player, struct builder_t* builder_to_hire)
{
	struct ressources ressources = can_buy(builder_to_hire, player->ressources);
	if (ressources.market.tokens[0] == NULL)  // All elements are NULL if cannot pay
	{
		return 0;
	}

	// Pays the tokens he has to in order to buy the builder
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if(ressources.market.tokens[index])
		{
			player_take_token(market, player,ressources.market.tokens[index]);
		}
	}
	return 1;
}

int player_get_points(struct player_t* player)
{
	return player->current_point;
}

struct ressources* player_get_ressources(struct player_t* player)
{
	return &player->ressources;
}

unsigned int player_get_favor(struct player_t *player)
{
	return player->favor;
}

void player_set_favor(struct player_t *player, unsigned int favor)
{
	player->favor = favor;
}