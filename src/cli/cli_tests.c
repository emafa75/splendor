#include "cli_tests.h"
#include "cli_board.h"
#include "market.h"
#include "token.h"

void cli_tests(void)
{
	struct market market = create_default_market();
	init_market(&market, 0);

	struct board_t board = market_to_board(&market);

	struct token_t* token;
	for (int i = 0 ; i < board.n ; ++i)
	{
		for (int j = 0 ; j < board.n ; ++j)
		{
			token = board.matrix[i][j].token;

			printf("%d, %d: ", i, j);
			token_short_diplay(*token);
			printf("\n");
		}
	}
	// board_display(VECTOR2_ONES, &board);
}


