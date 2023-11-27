#include "skills_builders.h"
#include "market.h"


int token_rob(struct player_t* robber_player, struct player_t* stolen_player, struct token_t* robbed_token)
{
    //check if the stollen_player has the desired token
    if (market_is_in_market(&stolen_player->ressources.market, robbed_token))
    {
        //Move the robbed token in new inventory and remove it from the stolen player
        market_pick_token(&stolen_player->ressources.market, robbed_token);
        market_pay_token(&robber_player->ressources.market, robbed_token, identity());
        return 1;
    }
    return 0;
}