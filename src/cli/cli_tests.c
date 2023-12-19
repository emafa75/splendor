#include "cli_tests.h"
#include "builder.h"
#include "cli_board.h"
#include "cli_guild.h"
#include "cli_turn.h"
#include "cli_utils.h"
#include "game.h"
#include "guild.h"
#include "market.h"
#include "players.h"
#include "players/cli_players.h"
#include "token.h"
#include "token_second_header.h"
#include "vector2.h"

void cli_tests(void)
{
	/**
		Init a default game
	*/
	struct game_parameters game_params = {
		.points_to_win = 10,
		.max_turns = 20,
		.market_seed = 0,
		.builder_seed = 0,
		.random_seed = 0,
		.display = 1,
		.num_player = 2,
	};
	
	struct game_t game = {};
	init_game(&game, game_params);

	struct turn_t* turn = game_get_current_turn(&game);
	/*
		Init market
	*/
	struct market_t market = create_default_market();
	init_tokens(8);
	init_market(&market, 8);

	/*
		Init guild
	*/

	struct guild_t guild = create_default_guild();
	init_builders(0);
	init_guild(&guild);


	/*
		Init the players
	*/
	int num_player = 2;
	struct player_t players[MAX_PLAYERS] = {} ;
	for (int index = 0; index < num_player; ++index)
	{
		players[index] = init_player();
		players[index].id = index;
	}

	/*
		Give a random token to the first player
	*/
	int index_picked_token = market_get_linked_tokens(&market,1);
	struct token_t* picked_token = market.tokens[index_picked_token];
	player_pick_token(&market, &players[0], picked_token);

	int ch = 0;
	while( ch != 'q'){
		clear_terminal();
				
		// struct vector2_t coord = {10, 10};
		
		// /*
		// 	Display global market
		// */
		// printToCoordinates(coord.x, coord.y, "Global Market : ");
		// /* Jump a line */
		// coord = vector2_add(coord,vector2_down());

		// struct board_t market_board = market_to_board(&market);
		// board_display(coord, &market_board);

		// /*
		// 	Display global_guild
		// */

		// coord.x = 10;
		// coord.y = 10;
		// coord.x += market_board.tile_dimension * market_board.n + 10;
		// display_global_guild(coord, &guild);

		// /*
		// 	Display players_inventory
		// */
		
		// coord.x += 80;
		// for (int index = 0; index < num_player; ++index){
		// 	coord = cli_player_display_inventory(coord, &players[index]);
		// }
		cli_turn_display(turn);

		ch = getch();
	}
	
}


