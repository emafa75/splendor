#ifndef __CAN_BUY_H__
#define __CAN_BUY_H__

#include "builder.h"
#include "market.h"
#include "token.h"
#include "players.h"


/*
 *  Returns a set of int representing the tokens to use to buy the builder
 *		out.available[i] = 1 if you need to use the i-th token to pay the builder
 *		out.available[i] = 0 if you don't need to use the i-th token to pay the builder
 *
 *  If it can't be bought, all the values of the array are set to NULL  
 */
struct ressources can_buy(struct builder_t *builder, struct ressources ressources);

/*
    Select the first affordable builder in the guild, other return -1
*/
int select_affordable_builder(struct player_t *player);
#endif
