
#include "cli_utils.h"
#include "vector2.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ansi_color.h"

int getch(void)
{
	int ch;
	struct termios oldt;
	struct termios newt;

	tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
	newt = oldt; /* copy old settings to new settings */
	newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */

	tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */

	ch = getchar(); /* standard getchar call */

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */

	return ch; /*return received char */
}
   

void printToCoordinates(unsigned int x, unsigned int y, char *str)
{
    printf("\033[%d;%dH%s", y, x, str);
}


struct winsize get_terminal_dimensions(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w;
}

void clear_terminal()
{
	// /printf("\e[1;1H\e[2J");
	system("clear");
}

void cli_jump_line(struct vector2_t* position)
{
	struct vector2_t new_position = vector2_add(*position,vector2_down());

	position->x = new_position.x;
	position->y = new_position.y;
}

void terminal_cursor(int toggle)
{
	if (toggle)
	{
		printf("\e[?25h"); //enable the cursor
	}
	else {
		printf("\e[?25l");
	}
	
}

void cli_popup(char* str)
{
	struct winsize winsize = get_terminal_dimensions();

	struct vector2_t center = {(int) winsize.ws_col/2,(int) winsize.ws_row/2};
	int offset = 2;
	int popup_lenght = str_len_special(str) + 2 * offset;
	int popup_width = 1 + 2 * offset; 
	center.y -= offset;
	center.x -= str_len_special(str)/2 + offset;

	for (int x = center.x; x < center.x + popup_lenght; ++x)
	{
		for (int y = center.y; y < center.y + popup_width; ++y)
		{
			printToCoordinates(x, y, " ");
		}
	}

	printToCoordinates(center.x + offset  , center.y + offset, str);
	/*
		Print a box around	
	*/
	struct vector2_t end_popup = {center.x + popup_lenght - 1, center.y + popup_width - 1};
	//center = vector2_add(center, vector2_opposite(vector2_ones()));

	
	cli_wrap_box(center, end_popup);
}

void cli_wrap_box(struct vector2_t begin, struct vector2_t end)
{
	/*
		Print corners
	*/
	printToCoordinates(begin.x, end.y, "└");  //bottom left
	printToCoordinates(begin.x, begin.y, "┌");  // top left
	printToCoordinates(end.x, begin.y ,"┐");  // top right┘└┐
	printToCoordinates(end.x, end.y,  "┘");  // bottom right

	/*
		Draw top and bottom
	*/

	for (int x = begin.x + 1; x < end.x; ++x)
	{
		printToCoordinates(x, begin.y, "─");
		printToCoordinates(x, end.y, "─");
	}

	/*
		Draw left and right side
	*/

	for (int y = begin.y + 1; y < end.y; ++y)
	{
		printToCoordinates(begin.x, y , "│");	
		printToCoordinates(end.x, y, "│");	
	}

}

struct vector2_t cli_display_options(struct vector2_t position, struct game_parameters params)
{
	char buffer[BUFFER_SIZE] = {};

	/*
		Points to win
	*/
	sprintf(buffer, "Points to win : " HYEL "%d" CRESET, params.points_to_win);
	printToCoordinates(position.x, position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	/*
		Max turns
	*/
	sprintf(buffer, "Max turns : " HYEL "%d" CRESET, params.max_turns);
	printToCoordinates(position.x, position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	/*
		Builder seed
	*/
	sprintf(buffer, "Builder seed : " HYEL "%d" CRESET, params.builder_seed);
	printToCoordinates(position.x, position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	/*
		Token seed
	*/
	sprintf(buffer, "Token seed : " HYEL "%d" CRESET, params.market_seed);
	printToCoordinates(position.x, position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	/*
		Random seed
	*/
	sprintf(buffer, "Random seed : " HYEL "%d" CRESET, params.random_seed);
	printToCoordinates(position.x, position.y, buffer);

	/* Jump line*/
	cli_jump_line(&position);

	return position;

}