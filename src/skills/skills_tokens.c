#include "skills_tokens.h"
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