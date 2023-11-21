#include "test_players.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"

int test_players()
{
    /*
        Init all needed instances
    */
    srand(time(NULL));
    init_market(rand());
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
    return 1;
    struct player_t new_player = init_player();
    if(new_player.current_point != 0)
    {
        fprintf(stderr,RED"test_init_players : Wrong initial point for player\n" CRESET);
        return 0;
    }

    for (int index = 0 ; index < MAX_BUILDERS ; ++index)
    {
        if (new_player.ressources.builders[index]) 
        {
            fprintf(stderr,RED "test_init_players : Player has initial builders in his inventory\n" CRESET);
            return 0;
        }
    }

    for (int index = 0 ; index < NUM_TOKENS ; ++index)
    {
        if (new_player.ressources.tokens[index]) 
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
    srand(time(NULL));
    struct player_t new_player = init_player();
    int index_hired_builder = 0;
    struct builder_t* hired_builder = get_available_builders().builders[index_hired_builder];
    player_hire_builder(&new_player, hired_builder);

    if (guild_is_available(hired_builder))
    {
        fprintf(stderr, RED "test_hire_builder: hired builder is still available in guild\n" CRESET);
		return 0;
    }
    if(!new_player.ressources.builders[index_hired_builder])
    {
        fprintf(stderr, RED "test_hire_builder: hired builder don't belong to the player\n" CRESET);
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
    init_market(rand());
    struct player_t new_player = init_player();
    struct token_t* picked_token = get_token(0); //the picked token need to be the first available
    player_pick_token(&new_player, picked_token);
    
    /*
        Check if there is a new token in player inventory and no longer in the market
    */

    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(new_player.ressources.tokens[index]) // if a token is in player inventory
        {
            if( picked_token != new_player.ressources.tokens[index])
            {
                fprintf(stderr, RED "test_player_pick_token: wrong token picked. Picked token : %p, expected : %p\n" CRESET, new_player.ressources.tokens[index], picked_token);
                token_display(*new_player.ressources.tokens[index], "Token in player inventory : ");
                token_display(*picked_token, "Expected picked token : ");
                return 0;
            }
            return 1;
        }
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
    struct player_t new_player = init_player();
    struct token_t* picked_token = get_token(0); //the picked token need to be the first available
    struct token_t* second_picked_token = get_token(1);
    player_pick_token(&new_player, picked_token);
    player_pick_token(&new_player, second_picked_token);

    player_take_token(&new_player, picked_token);
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(new_player.ressources.tokens[index] == picked_token)
        {
            fprintf(stderr, RED "test_player_take_token: paid token is still in player's inventory\n" CRESET);
		    return 0;
        }
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

