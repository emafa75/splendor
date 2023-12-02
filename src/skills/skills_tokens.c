#include "skills_tokens.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include <stdio.h>


int market_panic(struct turn_t* turn, const void* trigger)
{
    UNUSED(trigger);
    struct market_t* market = turn_get_market(turn);


    if( market_num_tokens(market) == 0) // no tokens to move
    {
        return 0;
    }

    /*
        Choose a random token in the market
    */    
    struct token_t* token_to_move = NULL;
    int rand_index = 0;

    while (token_to_move == NULL) 
    {
        rand_index = rand() % NUM_TOKENS ; 
        token_to_move = market->tokens[rand_index];
    }
    /*
        Remove token in case if it is the only available and we need to replace it at the same place
    */
    market_pick_token(market, token_to_move);
    
    /*
        Find a place to replace it
    */

    rand_index = rand() % NUM_TOKENS;
    while (market->tokens[rand_index] != NULL)
    {
        rand_index = rand() % NUM_TOKENS;
    }

    /*
        Make the change
    */
    
    market->tokens[rand_index] = token_to_move;

    return 1;
}

int guild_panic(struct turn_t* turn, const void* trigger)
{
    UNUSED(trigger);
    struct guild_t* guild = turn_get_guild(turn);

    if (guild->available_builders.n_builders_available == 0)
    {
        return 0;
    }

    /*
        Choose a builder to replace
    */

    int rand_index = 0; 
    struct builder_t* removed_builder = NULL;
    while(removed_builder == NULL)
    {
        rand_index = rand() % (MAX_BUILDERS_AVAILABLE_PER_LVL * NUM_LEVELS) ;
        removed_builder = guild->available_builders.builders[rand_index] ;
    }

    guild_pick_builder(guild, removed_builder);

    return 1;
}