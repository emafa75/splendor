
#include "cli_utils.h"
#include <stdio.h>

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
    printf("\033[%d;%dH%s\n", y, x, str);
}


struct winsize get_terminal_dimensions(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w;
}

void clear_terminal()
{
	printf("\e[1;1H\e[2J");
}