#include "cli_market.h"
#include "cli_board.h"
#include "vector2.h"

struct vector2_t cli_market_display(struct vector2_t position, struct market_t* market)
{
	struct board_t market_board = market_to_board(market);
	struct vector2_t last_position = cli_board_display(position, &market_board);
	return last_position;
}