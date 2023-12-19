#ifndef __PLAYERS_H__
#define __PLAYERS_H__


#include "token.h"
#include "guild.h"
#include "market.h"

#define PLAYER_MAX_TOKENS 10


struct player_t
{
	struct ressources ressources;
    int current_point;
	unsigned int favor;
	unsigned int id;
};

/*
    return a empty player (no token, no builder)
*/
struct player_t init_player();


/*
    take a specific token from a player and replace it into the market.
*/
void player_take_token(struct market_t* market, struct player_t* player, struct token_t* token);

/*
    Take token from the specified market, if the token is not in the marketn do nothing and if the player has already the max of token, do nothing
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
    Put tokens into the market 
*/
int player_pay_builder(struct market_t* market, struct player_t* player, struct builder_t* builder_to_hire);

/*
    Get player points
*/
int player_get_points(struct player_t* player);

/*
    Get player ressources
*/
struct ressources* player_get_ressources(struct player_t* player);

/*
	Get favor from a player
*/
unsigned int player_get_favor(struct player_t* player);

/*
	Set number of favor for a player
*/

void player_set_favor(struct player_t* player, unsigned int favor);

/*
	Get unique id from the player
*/
unsigned int player_get_id(struct player_t* player);
#endif
