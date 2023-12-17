#ifndef __CLI_SET_H__
#define __CLI_SET_H__

#include "set.h"

/*
	Print set display into a char* 
*/
void cli_set_display(char* buffer, struct set_t* set );

/*
	Print set short display into a char* 
*/
void cli_set_short_display(char* buffer, struct set_t* set, char* prefix );

#endif