#ifndef __GAME_H__
#define __GAME_H__

#include "guild.h"
#include "market.h"
#include "players.h"
#include "builder.h"
#include <string.h>
#include <stdio.h>

#define MAX_PLAYERS 2
#define MAX_MAX_TURNS 100

#define TIE -1

struct turn_t
{
    struct market_t market;
    struct guild_t guild;
    struct player_t players[MAX_PLAYERS];
    unsigned int current_player;
    unsigned int points_to_win;
};

struct game_t
{
    struct turn_t turns[MAX_MAX_TURNS + 1]; //+1 because the first state is for the init
    unsigned int num_turns;
    unsigned int current_turn_index;
};

struct game_parameters
{
    int max_turns ;
    int points_to_win;
    int builder_seed;
    int market_seed;
};

/*
    Init game with params
*/
void init_game(struct game_t* game, struct game_parameters params);

/*
    Get the index-th turn of the game
*/
struct turn_t* game_get_turn(struct game_t* game, int index);

/*
    Get the current turn of the game
*/
struct turn_t* game_get_current_turn(struct game_t* game);

/*
    Copy the current state of the game in the next case of turns[] and increment current turn index
*/
void game_save_turn(struct game_t* game);

/*
    Get the market from a turn
*/
struct market_t* turn_get_market(struct turn_t* turn);

/*
    Get the guild from the market
*/
struct guild_t* turn_get_guild(struct turn_t* turn);

/*
    Get players from the game
*/
struct player_t* turn_get_players(struct turn_t* turn);

/*
    Get player who is currently playing
*/
struct player_t* turn_get_current_player(struct turn_t* turn);

/*
    Display the current state of the turn
*/
void turn_display(struct turn_t* turn);

/*
    change current player to next player.
*/
void next_player(struct turn_t* current_turn);

/*
    check if a player has won
*/
int has_won(struct turn_t* current_turn);

/*
	Returns winner's index, TIE if tie
*/
int get_winner(struct turn_t* current_turn);


#endif