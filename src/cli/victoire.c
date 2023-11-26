
#include "victoire.h"
#include "market.h"

#define BOARD_SIZE (NUM_TOKENS)

struct board {
	char matrix[BOARD_SIZE][BOARD_SIZE];
	int side_length;
};


struct vector2 {
	int x;
	int y;
};

static struct vector2 vector_up = {0, -1};
static struct vector2 vector_down = {0, 1};
static struct vector2 vector_left = {-1, 0};
static struct vector2 vector_right = {1, 0};


int vector2_equals(struct vector2 v1, struct vector2 v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}


struct board available_to_board(struct available_tokens *available_tokens)
{
	int side_length = (int)sqrt(NUM_TOKENS);
	struct board board = {{}, side_length};

	int i = side_length - 1;
	int j = 0;

	struct vector2 direction = vector_right;


	for (int k = 0 ; k < NUM_TOKENS ; ++k)
	{
		if (available_tokens->available[NUM_TOKENS - k] == NULL)
			board.matrix[i][j] = ' ';
		else
			board.matrix[i][j] = 'T';

		i += direction.y;
		j += direction.x;

		if (vector2_equals(direction, vector_right) && (board.matrix[i][j + 1] != 0 || j >= side_length - 1))
			direction = vector_up;
		else if (vector2_equals(direction, vector_up) && (board.matrix[i - 1][j] != 0 || i <= 0))
			direction = vector_left;
		else if (vector2_equals(direction, vector_left) && (board.matrix[i][j - 1] != 0 || j <= 0))
			direction = vector_down;
		else if (vector2_equals(direction, vector_down) && (board.matrix[i + 1][j] != 0 || i >= side_length - 1))
			direction = vector_right;
	}

	return board;
}


void board_display()
{
	int side_length = (int)sqrt(NUM_TOKENS);
	struct available_tokens * available_tokens = get_available_tokens();
	struct board board = available_to_board(available_tokens);

	// Top side
	printf("┌");
	for (int j = 0 ; j < side_length ; ++j)
		printf("─");

	printf("┐\n");


	for (int i = 0 ; i < side_length ; ++i)
	{
		printf("│");
		for (int j = 0 ; j < 2 * side_length - 1 ; ++j)
		{
			printf("%c", board.matrix[i][j]);
		}
		printf("│\n");
	}


	// bottom side
	printf("└");
	for (int j = 0 ; j < side_length ; ++j)
		printf("─");

	printf("┘\n");
}

