#include "cli_turn.h"
#include "ansi_color.h"
#include "cli_board.h"
#include "cli_guild.h"
#include "cli_market.h"
#include "cli_utils.h"
#include "game.h"
#include <stdio.h>
#include <math.h>
#include "builder.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "token.h"
#include "vector2.h"
#include "builder_constants.h"
#include "cli_players.h"

#define MAX_ROWS_FOR_PLAYERS ((7 * MAX_PLAYERS) + MAX_BUILDERS + NUM_TOKENS) 

void cli_turn_display(struct turn_t *turn)
{
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
	unsigned int num_player = turn_get_num_player(turn);
	struct player_t* current_player = turn_get_current_player(turn);

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
	struct vector2_t end_market = cli_market_display(coord, market);
	cli_jump_line(&end_market);
	printToCoordinates(end_market.x - (TILE_DIMENSION * ((int) sqrt(NUM_TOKENS) + 1)), end_market.y , BOLD "Global Market" CRESET);

	/*
		Display global guild
	*/
	coord.x += end_market.x + 2;
	struct vector2_t start_guild = coord;
	struct vector2_t end_guild = display_global_guild(start_guild, guild);
	cli_jump_line(&end_guild);

	/*
		Display current player inventory
	*/
	struct vector2_t start_player_inventory = {start_guild.x, start_guild.y + (1+ MAX_BUILDERS_AVAILABLE_PER_LVL * NUM_LEVELS) + 1};
	
	cli_player_display_inventory(start_player_inventory, current_player);

	/*
		Display short display for all the players
	*/
	struct vector2_t start_short_inventory_display = {winsize.ws_col - 22 , start_guild.y};

	/* Title of the section */
	printToCoordinates(start_short_inventory_display.x, start_short_inventory_display.y, BOLD "Players" CRESET);
	cli_jump_line(&start_short_inventory_display);
	cli_jump_line(&start_short_inventory_display);
	start_short_inventory_display = vector2_add(start_short_inventory_display,vector2_right()); //tabulation

	struct vector2_t end_short_inventory_display = start_short_inventory_display;

	for (unsigned int index = 0; index < num_player; ++index)
	{
		end_short_inventory_display = cli_player_short_display(end_short_inventory_display, &players[index]);
	}

	/*
		Draw box around players
	*/

	struct vector2_t start_players_box = start_short_inventory_display;
	start_players_box = vector2_add(start_players_box , vector2_opposite(vector2_ones()));
	start_players_box.x -= 1 ;//manual adjustement 
	struct vector2_t end_players_box = {winsize.ws_col - 1, end_short_inventory_display.y};

	cli_wrap_box(start_players_box, end_players_box);

	/*
		Display game options
	*/

	struct vector2_t start_option_display = {end_short_inventory_display.x, num_player * 6 + 3};
	cli_jump_line(&start_option_display);

	/* Title of the section */
	printToCoordinates(start_option_display.x, start_option_display.y, BOLD "Game parameters " CRESET);
	cli_jump_line(&start_option_display);
	cli_jump_line(&start_option_display);
	start_option_display = vector2_add(start_option_display,vector2_right()); //tabulation


	struct vector2_t end_option_display = cli_display_options(start_option_display, *turn_get_params(turn));


	/*
		Context box
	*/

	struct vector2_t start_context_box = {0, end_market.y};
	start_context_box = vector2_add(start_context_box, margin);

	struct vector2_t end_context_box = {end_option_display.x - 2 , winsize.ws_row};
	end_context_box = vector2_add( end_context_box,vector2_opposite(margin));
	/*
		Remove the margin from the bottom, not perfect
	*/
	cli_jump_line(&end_context_box);
	cli_jump_line(&end_context_box);
	cli_wrap_box(start_context_box, end_context_box);

	/* Context legend */
	start_context_box = vector2_add(start_context_box, vector2_right());
	start_context_box = vector2_add(start_context_box, vector2_right());
	start_context_box = vector2_add(start_context_box, vector2_down());

	printToCoordinates(start_context_box.x, start_context_box.y,URED BOLD  "Context :" CRESET);
}