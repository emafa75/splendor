#ifndef __CLI_UTILS_H__
#define __CLI_UTILS_H__

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "game.h"
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


int getkey_unlocked(void);


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
	Clear stdout
*/
void clear_terminal(void);

/*
	Modify the position vector to make it jump a line 
*/
void cli_jump_line(struct vector2_t* position);


/*
	Enable or disable the terminal cursor

	Hide the cursor if state == 0
	Show it otherwies
*/
void terminal_cursor(int state);

/*
	Display a popup on the center of the screen
*/
void cli_popup(char* str);

/*
	Wrap a box on this position (rectangle)
*/
void cli_wrap_box(struct vector2_t begin, struct vector2_t end);

/*
	Display game options
	Returns the position at the end of the display
*/
struct vector2_t cli_display_options(struct vector2_t position, struct game_parameters);
#endif
