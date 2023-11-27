#include "players.h"
#include "can_buy.h"


struct player_t init_player()
{
	struct player_t new_player = {.ressources={}, .current_point=0};
	return new_player;
}


void player_pick_token(struct market_t* market, struct player_t* player, struct token_t* picked_token){
	market_pick_token(market, picked_token);
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
			player->current_point += builder_points(builder_to_hire);
			guild_pick_builder(guild, builder_to_hire);
			return;
		}
	}
   
}


void player_display_inventory(struct player_t *player)
{   
	printf("Token available : \n");
	for (int index = 0; index < NUM_TOKENS; ++index)
	{
		if(player->ressources.market.tokens[index]){
			token_display(*player->ressources.market.tokens[index], " --- ");
		}
	}

	printf("Builders : \n");
	for (unsigned int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(player->ressources.guild.builders[index]) {
			builder_display(player->ressources.guild.builders[index]," --- ");
		}
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

