#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "builder.h"
#include "token.h"
#include "market.h"
struct player_t
{
    int index_token_list[NUM_TOKENS];
    int index_builder_list[MAX_BUILDERS];
    int current_point;
};

struct player_t init_player();
void player_take_token(struct player_t* player, unsigned int index);
void player_hire_builder(struct player_t* player, unsigned int index );
void player_display_inventory(struct player_t* player);




#endif