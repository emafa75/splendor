#ifndef __CLI_PLAYERS_H__
#define __CLI_PLAYERS_H__

#include "players.h"
#include "vector2.h"

/*
	Display player inventory at the desired position.
	Returns the position at the end of the display
*/
struct vector2_t cli_player_display_inventory(struct vector2_t position, struct player_t* player);

/*
	Display a short display for the player (points, favor, nb tokens, nb_builders)
	Returns the position at the end of the display
*/
struct vector2_t cli_player_short_display(struct vector2_t position, struct player_t* player);
#endif
