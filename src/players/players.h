#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "builder.h"
#include "token.h"

#include "guild.h"
#include "market.h"

#include <stdio.h>



struct player_t
{
	struct ressources ressources;
    int current_point;
};

/*
    return a empty player (no token, no builder)
*/
struct player_t init_player();


/*
    take a specific token from a player
*/
void player_take_token(struct market_t* market, struct player_t* player, struct token_t* token);

/*
    take first available token from the market
*/
void player_pick_token(struct market_t* market, struct player_t* player, struct token_t* token);


/*
    add builder to player deck /!\ Do not check if he has enought token to hire it
*/
void player_hire_builder(struct guild_t* guild, struct player_t* player, struct builder_t *builder_to_hire );

/*
    display player inventory's
*/
void player_display_inventory(struct player_t* player);
/*
    check if a player is able to hire a specific builder (identify by his id) and take necessary token from inventory
    return 0 is impossible, 1 otherwise
*/
int player_pay_builder(struct market_t* market, struct player_t* player, struct builder_t* builder_to_hire);




#endif
