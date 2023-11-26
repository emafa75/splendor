#ifndef __CLI_UTILS_H__
#define __CLI_UTILS_H__


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>


/*
 *  Returns char input from user
 *
 *  Notes: doesn't display the char in stdout and doesn't need the user to press return
 *		It only uses std libs
 */
int getch(void);


/*
 *  Prints the character c at pos i, j of the screen
 */
void printToCoordinates(unsigned int i, unsigned int j, char *str);


/*
 *  Returns the terminal dimensions
 *
 *  Notes: out has ws_row and ws_col attributes
 *
 */
struct winsize get_terminal_dimensions(void);
#endif
