#ifndef __CAN_BUY_H__
#define __CAN_BUY_H__

#include "builder.h"
#include "set.h"
#include "ressources.h"
#include "guild.h"
#include "players.h"


/*
	Returns 1 if intersection is not null
*/
unsigned int is_usable(struct set_t *set, struct set_t cost);


/*
	Select the first affordable builder in the guild, other return -1
*/
struct builder_t * select_affordable_builder(struct guild_t* guild, struct player_t *player);


/*
	New can_buy functionn is he impossible to buy, then returns a ressources with NULL everywhere
*/
struct ressources_t is_buyable(struct set_t cost, struct ressources_t ressources);
#endif
