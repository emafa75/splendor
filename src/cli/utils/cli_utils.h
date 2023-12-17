#ifndef __CLI_UTILS_H__
#define __CLI_UTILS_H__



#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "vector2.h"

#define LINE_SIZE 1
#define BUFFER_SIZE 300

/*
 *  Returns char input from user
 *
 *  Notes: doesn't display the char in stdout and doesn't need the user to press return
 *		It only uses std libs
 */
int getch(void);


/*
 *  Prints the character c at pos x, y of the screen
 */
void printToCoordinates(unsigned int x, unsigned int y, char *str);


/*
 *  Returns the terminal dimensions
 *
 *  Notes: out has ws_row and ws_col attributes
 *
 */
struct winsize get_terminal_dimensions(void);

/*
	Clear the terminal output
*/
void clear_terminal(void);

/*
	Modify the position vector to make it jump a line 
*/
void cli_jump_line(struct vector2_t* position);

#endif
