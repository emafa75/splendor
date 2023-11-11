#include "players.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include "can_buy.h"
#include <stdio.h>

struct player_t init_player()
{
    struct player_t new_player = {.index_token_list = {}, .index_builder_list = {}, \
     .current_point =0};
    return new_player;
}



void player_take_token(struct player_t* player, unsigned int index){
    player-> index_token_list[index] = 1;
    pick_token(index);
}

void player_hire_builder(struct player_t *player, unsigned int index)
{
    player->index_builder_list[index] = 1 ;
    guild_pick_builder(index);
}

void player_display_inventory(struct player_t *player)
{   
    printf("Token available : \n");
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(player->index_token_list[index]){
            token_display(*get_token(index), " --- ");
        }
    }

    printf("Builders : \n");
    for (unsigned int index = 0; index < MAX_BUILDERS; ++index)
    {
        if(player->index_builder_list[index])
        {
            builder_display(make_builder(index)," --- ");
        }
    }
}

int player_pay_builder(struct player_t* player, int index_builder_to_hire)
{
    struct available_tokens token_list_to_buy = can_buy(make_builder(index_builder_to_hire), player->index_token_list);
    if(token_list_to_buy.available[0] == -1)
    {
        return 0;
    }
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(token_list_to_buy.available[index])
        {
            player_take_token(player,index);
            pay_token(get_token(index));
        }
    }
    return 1;
}

