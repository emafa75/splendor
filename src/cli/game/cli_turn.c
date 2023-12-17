#include "cli_turn.h"
#include "ansi_color.h"
#include "cli_board.h"
#include "cli_market.h"
#include "cli_utils.h"
#include "game.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "token.h"
#include "vector2.h"

#define MAX_ROWS_FOR_PLAYERS ((7 * MAX_PLAYERS) + MAX_BUILDERS + NUM_TOKENS) 

void cli_turn_display(struct turn_t *turn)
{
	clear_terminal();

	char buffer[BUFFER_SIZE];
	struct winsize winsize = get_terminal_dimensions();
	struct vector2_t coord = vector2_zero();
	struct vector2_t margin = { 2,  2};

	/*
		Get instances 
	*/
	struct market_t* market = turn_get_market(turn);
	struct guild_t* guild = turn_get_guild(turn);
	struct player_t* players = turn_get_players(turn);
	int nb_players = turn_get_num_player(turn);

	//printf("Dimensions : %d lines, %d columns\n", winsize.ws_row, winsize.ws_col );


	/*
		Find the minium size required to display the turn
	*/

	// int min_rows = MAX(TILE_DIMENSION * ((int) sqrt(BOARD_SIZE)), MAX_ROWS_FOR_PLAYERS);

	// if (min_rows > winsize.ws_row)
	// {
	// 	printf("Window size too small\nNeed %d rows", min_rows);
	// }

	/*
		Display the title of the turn
	*/
	unsigned int turn_id = turn_get_id(turn);
	sprintf(buffer,BBLU "════════════════════════" BRED " TURN %d " BLU "════════════════════════" CRESET, turn_id);
	printToCoordinates(winsize.ws_col/2 - 28, 0 , buffer); //28 to center

	/*
		Display market
	*/
	coord = vector2_add(coord,margin);
	coord = cli_market_display(coord, market);
	cli_jump_line(&coord);
	printToCoordinates(coord.x - (TILE_DIMENSION * ((int) sqrt(NUM_TOKENS) + 1)), coord.y , BOLD "Global Market" CRESET);

	/*
		Display global guild
	*/


	
}