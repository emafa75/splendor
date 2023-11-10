#include "test_players.h"
#include "players.h"
#include "token.h"
#include <stdio.h>

int test_players()
{
    int i = 0 ;
    if(test_init_players())
    {
        printf("Test init_players passed");
        ++i;
    }
    return i;

}

int test_init_players()
{
    struct player_t new_player = init_player();
    if(new_player.current_point == 0)
    {
        fprintf(stderr,"test_init_players : Wrong initial point for player\n");
        return 0;
    }

    for (int index = 0 ; index < MAX_BUILDERS ; ++index)
    {
        if ( !new_player.index_builder_list[index]) 
        {
            fprintf(stderr,"test_init_players : Player has initial builders in his inventory\n");
            return 0;
        }
    }

    for (int index = 0 ; index < NUM_TOKENS ; ++index)
    {
        if (!new_player.index_token_list[index]) 
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

