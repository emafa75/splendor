#include "players.h"
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "token.h"
#include "can_buy.h"
#include <stdio.h>

struct player_t init_player()
{
    struct player_t new_player = {.ressources={}, .current_point=0};
    return new_player;
}



void player_pick_token(struct player_t* player, struct token_t* picked_token){
    pick_token(picked_token);
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        /*
            Find a place to stock the token
        */
        if(!player->ressources.tokens[index])
        {
            player->ressources.tokens[index] = picked_token;
            return;
        }
    }
}

void player_take_token(struct player_t* player, struct token_t * token){
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if (player->ressources.tokens[index] == token)
        {
            pay_token(token);
            player->ressources.tokens[index] = NULL;
            return;
        }
    } 
 
}

void player_hire_builder(struct player_t *player,struct builder_t* builder_to_hire)
{
    for (int index = 0; index < MAX_BUILDERS; ++index)
    {
        /*
            Look for place in player inventory
        */
        if(player->ressources.builders[index] == NULL)
        {
            player->ressources.builders[index] = builder_to_hire;
            player->current_point += builder_points(builder_to_hire);
            guild_pick_builder(builder_to_hire);
            return;
        }
    }
   
}

void player_display_inventory(struct player_t *player)
{   
    printf("Token available : \n");
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(player->ressources.tokens[index]){
            token_display(*player->ressources.tokens[index], " --- ");
        }
    }

    printf("Builders : \n");
    for (unsigned int index = 0; index < MAX_BUILDERS; ++index)
    {
        if(player->ressources.builders[index])
        {
            builder_display(player->ressources.builders[index]," --- ");
        }
    }
}

int player_pay_builder(struct player_t* player, struct builder_t* builder_to_hire)
{
    struct ressources ressources = can_buy(builder_to_hire, player->ressources);
    if (ressources.tokens[0] == NULL)
    {
        return 0;
    }

	// Pays the tokens he has to in order to buy the builder
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        if(ressources.tokens[index])
        {
            player_take_token(player,ressources.tokens[index]);
        }
    }
    return 1;
}

