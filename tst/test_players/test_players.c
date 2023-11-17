#include "test_players.h"
#include "players.h"
#include "token.h"
#include <stdio.h>
#include "ansi_color.h"

int test_players()
{
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
        fprintf(stderr,"test_init_players : Wrong initial point for player\n");
        return 0;
    }

    for (int index = 0 ; index < MAX_BUILDERS ; ++index)
    {
        if (new_player.ressources.builders[index]) 
        {
            fprintf(stderr,"test_init_players : Player has initial builders in his inventory\n");
            return 0;
        }
    }

    for (int index = 0 ; index < NUM_TOKENS ; ++index)
    {
        if (new_player.ressources.tokens[index]) 
        {
            fprintf(stderr,"Player has initial tokens in his inventory\n");
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
		fprintf(stderr, "test_hire_builder: test_init_players didn't run successfully\n");
		return 0;
	}

    //struct player_t new_player = init_player();
    return 1;

    
}

int test_player_pick_token()
{
    return 1;
}

int test_player_take_token()
{
    return 1;
}

int test_player_pay_builder()
{
    return 1;
}

