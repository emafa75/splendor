#include "players.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include <stdio.h>

struct players_t players;


struct player_t init_player()
{
    struct player_t new_player = {.index_token_list = {}, .index_builder_list = {}, \
     .current_point =0};
    return new_player;
}

void init_players()
{
    for (int index = 0; index < MAX_PLAYERS; ++index)
    {
        players.player_list[index] = init_player();
    }
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
        token_display(*get_token(index), " --- ");
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

