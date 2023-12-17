
#include "cli_utils.h"
#include "vector2.h"
#include <stdio.h>
#include <stdlib.h>
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