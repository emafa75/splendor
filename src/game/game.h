#ifndef __GAME_H__
#define __GAME_H__

#include "guild.h"
#include "market.h"
#include "players.h"


#define MAX_PLAYERS 4
#define MAX_MAX_TURNS 100
#define CONTEXT_SIZE 1000
#define MAX_ACTIONS 10

#define TIE -1

/*
	Used to use a display function only if _x is true
*/
#define DISPLAY(_x, _y)\
	(_x) ? (_y) : UNUSED(_x);


struct game_parameters
{
	unsigned int max_turns;
	unsigned int points_to_win;
	unsigned int builder_seed;
	unsigned int market_seed;
	unsigned int random_seed;
	unsigned int display;
	unsigned int num_player;
};


struct context 
{
	char actions[MAX_ACTIONS][CONTEXT_SIZE]; //Stock the context in a array to separate different actions 
	int num_actions;
};


struct turn_t
{
	struct market_t market;
	struct guild_t guild;
	struct player_t players[MAX_PLAYERS];
	unsigned int current_player;
	unsigned int next_player;
	unsigned int points_to_win;
	unsigned int display; /* Used to display in other functions*/
	unsigned int num_player;
	unsigned int id;
	struct game_parameters params;
	struct context context;
};


struct game_t
{
	struct turn_t turns[MAX_MAX_TURNS + 1 + 1]; //+1 because the first state is for the init +1 for the final state
	unsigned int num_turns;
	unsigned int current_turn_index;
};


enum choice {
	HIRE,
	PICK,
	SKIP,
	NUM_CHOICE,
	FIRST_CHOICE = HIRE
};


struct turn_statistics
{
	enum choice choice;
	int used_favor;
	int used_skill;
	int num_picked_tokens;
	int forced_skip;
};


struct game_statistics
{
	int choices[NUM_CHOICE];
	int used_favor;
	int used_skill;
	int num_picked_tokens;
	int forced_skip;
	int nb_turns;
	int result;
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
	Play a full game, with a display option
*/
struct game_statistics game_play(struct game_t* game);


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
	Get the index from the player who is currently playing
*/
int turn_get_current_player_index(struct turn_t* turn);


/*
	Get number of player in the turn
*/
int turn_get_num_player(struct turn_t* turn);


/*
	Display the current state of the turn
*/
void turn_display(struct turn_t* turn);


/*
	Gets turn id
*/
unsigned int turn_get_id(struct turn_t* turn);


/*
	Get turn params
*/
struct game_parameters* turn_get_params(struct turn_t* turn);

/*
	Get next player id
*/
unsigned int turn_get_next_player_index(struct turn_t* turn);

/*
	Set next player 
*/
void turn_set_next_player(struct turn_t *turn, unsigned int next_player_index);

/*
	Get context from a turn
*/
struct context* turn_get_context(struct turn_t* turn);

/*
	Add action to the turn
*/
void turn_add_context(struct turn_t* turn, char* action);

/*
	Reset the context for a turn 
*/
void turn_reset_context(struct turn_t* turn);

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


/*
	Returns a random index of a player
*/
unsigned int get_random_player(int num_player);


/*
	Play a turn
*/
struct turn_statistics turn_play(struct turn_t* current_turn);


/*
	Display the stats of a game
*/
void game_stats_display(struct game_statistics game_stats);
#endif
