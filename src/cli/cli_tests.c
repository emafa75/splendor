#include "cli_tests.h"
#include "builder.h"
#include "cli_board.h"
#include "cli_guild.h"
#include "cli_utils.h"
#include "guild.h"
#include "market.h"
#include "token_second_header.h"
#include "vector2.h"

void cli_tests(void)
{
	int ch = 0;
	while( ch != 'q'){
		clear_terminal();
		// struct market_t market = create_default_market();
		// init_market(&market, 0);

		// struct board_t board = market_to_board(&market);

		// struct guild_t guild = create_default_guild();
		// init_builders(0);
		// init_guild(&guild);
		struct vector2_t coord = {.x = 10, .y = 10};

		// /*
		// 	Display global_guild
		// */
		// display_global_guild(coord, &guild);


		/*
			Display global market
		*/
		struct market_t market = create_default_market();
		init_tokens(8);
		init_market(&market, 8);

		struct board_t market_board = market_to_board(&market);
		board_display(coord, &market_board);

		ch = getch();
	}
	
}


