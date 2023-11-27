#ifndef __SKILLS_BUILDERS_H__
#define __SKILLS_BUILDERS_H__

#include "players.h"
#include "token.h"
#include "permutation.h"

/*
    Rob a specific token to a player
    Returns 0 if impossible, -1 if success
*/
int token_rob(struct player_t* robber_player, struct player_t* stolen_player, struct token_t* robbed_token);

#endif