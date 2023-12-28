#include "test_players.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "ressources.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"
#include "token_second_header.h"


int test_players()
{
	/*
		Init all needed instances
	*/
	init_builders(rand());
	

	int test_passed = 0 ;
	if(test_init_players())
	{
		printf(GRN "Test init_players passed\n" CRESET);
		++test_passed;
	}
	if(test_hire_builder())
	{
		printf(GRN "Test hire_builder passed\n" CRESET);
		++test_passed;
	}
	if(test_player_take_token())
	{
		printf( GRN "Test player_take_token passed\n" CRESET);
		++test_passed;
	}
	if(test_player_pick_token())
	{
		printf(GRN "Test player_pick_token passed\n" CRESET);
		++test_passed;
	}

	if(test_player_pay_builder())
	{
		printf(GRN "Test player_pay_builder passed\n" CRESET);
		++test_passed;
	}

	return test_passed;

}

int test_init_players()
{
	struct player_t new_player = init_player();

	if(player_get_points(&new_player) != 0)
	{
		fprintf(stderr,RED"test_init_players : Wrong initial point for player\n" CRESET);
		return 0;
	}

	struct ressources_t* player_ressources = player_get_ressources(&new_player);
	
	for (int index = 0 ; index < MAX_BUILDERS ; ++index)
	{
		if (player_ressources->guild.builders[index]) 
		{
			fprintf(stderr,RED "test_init_players : Player has initial builders in his inventory\n" CRESET);
			return 0;
		}
	}

	for (int index = 0 ; index < NUM_TOKENS ; ++index)
	{
		if (player_ressources->market.tokens[index]) 
		{
			fprintf(stderr,RED "Player has initial tokens in his inventory\n" CRESET);
			return 0;
		}
	}
	return 1;
}

int test_hire_builder()
{
	// make sure the players are init and does it well

	if (!test_init_players())
	{
		fprintf(stderr, RED "test_hire_builder: test_init_players didn't run successfully\n" CRESET);
		return 0;
	}
	struct player_t new_player = init_player();
	int index_hired_builder = 0;

	struct market_t market = create_default_market();
	init_market(&market);

	struct guild_t guild = create_default_guild();
	init_guild(&guild);

	struct builder_t* hired_builder = guild_get_available_builders(&guild)->builders[index_hired_builder];
	player_hire_builder(&guild, &new_player, hired_builder);

	if (guild_is_available(&guild, hired_builder))
	{
		fprintf(stderr, RED "test_hire_builder: hired builder is still available in guild\n" CRESET);
		return 0;
	}

	if(! guild_is_present_in_guild(&guild, hired_builder))
	{
		fprintf(stderr, RED "test_hire_builder: hired builder don't belong to the player\n" CRESET);
		builder_display(hired_builder, "Hired Builder : ");
		player_display_inventory(&new_player);
		return 0;
	}
	return 1;

	
}

int test_player_pick_token()
{
	if (!test_init_players())
	{
		fprintf(stderr, RED "test_player_pick_token: test_init_players didn't run successfully\n" CRESET);
		return 0;
	}

	struct market_t market = create_default_market();
	init_market(&market);

	struct player_t new_player = init_player();
	struct token_t* picked_token = make_token(0); //the picked token need to be the first available

	player_pick_token(&market, &new_player, picked_token);
	
	/*
		Check if there is a new token in player inventory and no longer in the market
	*/


	if(market_is_in_market(&new_player.ressources.market, picked_token)) // if a token is in player inventory
	{
		return 1;
	}
	
	fprintf(stderr, RED "test_player_pick_token: no token available in player inventory\n" CRESET);
	return 0;
}

int test_player_take_token()
{
	if (!test_init_players())
	{
		fprintf(stderr, RED "test_player_take_token: test_init_players didn't run successfully\n" CRESET);
		return 0;
	}
	if (!test_player_pick_token())
	{
		fprintf(stderr, RED "test_player_take_token: test_player_pick_token didn't run successfully\n" CRESET);
		return 0;
	}

	struct market_t market = create_default_market();
	init_market(&market);

	struct player_t new_player = init_player();
	struct token_t* picked_token = make_token(0); //the picked token need to be the first 
	struct token_t* second_picked_token = make_token(1);
	player_pick_token(&market, &new_player, picked_token);
	player_pick_token(&market, &new_player, second_picked_token);

	player_take_token(&market, &new_player, picked_token);

	//check if the token is  no longer in player's inventory
	if(market_is_in_market(&new_player.ressources.market, picked_token))
	{
		fprintf(stderr, RED "test_player_take_token: paid token is still in player's inventory\n" CRESET);
		return 0;
	}
	//check if the token is back into market
	if(!market_is_in_market(&market, picked_token))
	{
		fprintf(stderr, RED "test_player_take_token: paid token is not back into the market\n" CRESET);
		return 0;
	}

	

	return 1;
}

int test_player_pay_builder()
{
	if (!test_init_players())
	{
		fprintf(stderr, RED "test_player_pay_builder: test_init_players didn't run successfully\n" CRESET);
		return 0;
	}
	return 1;
}

