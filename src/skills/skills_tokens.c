#include "skills_tokens.h"
#include "guild.h"
#include "market.h"

int market_panic(struct market* market, struct token_t* token_to_move, int index_in_market)
{
    if(!market_is_in_market(market, token_to_move))
    {
        return 0;
    }

    if(!(market->tokens[index_in_market])) //if the place in the market is available
    {
        market->tokens[index_in_market] = token_to_move;
        return 1;
    }

    return 0;
}

int guild_panic(struct guild* guild, struct builder_t* builder_to_pop)
{
    if (guild_is_available(guild,builder_to_pop)){
        guild_pick_builder(guild, builder_to_pop);
        return 1;
    }
    return 0;
}