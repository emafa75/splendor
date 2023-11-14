#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "builder.h"
#include "token.h"
#include "market.h"



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
void player_take_token(struct player_t* player, struct token_t* token);

/*
    take first available token from the market
*/
void player_pick_token(struct player_t* player);


/*
    add builder to player deck /!\ Do not check if he has enought token to hire it
*/
void player_hire_builder(struct player_t* player, unsigned int index );

/*
    display player inventory's
*/
void player_display_inventory(struct player_t* player);
/*
    check if a player is able to hire a specific builder (identify by his id) and take necessary token from inventory
    return 0 is impossible, 1 otherwise
*/
int player_pay_builder(struct player_t* player, int index_builder_to_hire);




#endif
