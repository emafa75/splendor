#ifndef __GAME_H__
#define __GAME_H__

#include "guild.h"
#include "market.h"
#include "players.h"

#define MAX_PLAYERS 2
#define MAX_MAX_TURNS 100


struct turn_t
{
    struct market_t market;
    struct guild_t guild;
    struct player_t players[MAX_PLAYERS];
    unsigned int current_player;
};

struct game_t
{
    struct turn_t turns[MAX_MAX_TURNS];
    unsigned int num_turns;
};


#endif