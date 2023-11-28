#include "cli_tests.h"
#include "cli_board.h"
#include "cli_utils.h"
#include "market.h"
#include "token.h"

void cli_tests(void)
{
	struct market market = create_default_market();
	init_market(&market, 0);

	struct board_t board = market_to_board(&market);

	while (1)
	{
		board_display(VECTOR2_ONES, &board);
		getch();
	}
}


