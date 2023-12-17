#include "cli_set.h"
#include "ansi_color.h"
#include "color_second_header.h"
#include <stdio.h>
#include <string.h>


void cli_set_display(char *buffer, struct set_t* set)
{
	char tmp_buffer[100] = {};
	for (enum color_t i = 0 ; i < NUM_COLORS ; ++i)
	{
		if (set->c[i] != 0)
		{
			sprintf(tmp_buffer,"%s%s%s=%d (Q:%d),", color_prefix(i), color_to_short_string(i), CRESET, i, set->c[i]);	  
			strcat(buffer, tmp_buffer);
		}
	}
}

void cli_set_short_display(char *buffer, struct set_t *set, char* prefix)
{
	char tmp_buffer[100] = {};
    sprintf(buffer, "%s(", prefix);
	
	for (enum color_t i = 0 ; i < NUM_COLORS ; ++i)
	{
		if(set->c[i] != 0)
		{	
			sprintf(tmp_buffer, "%s%s=%d%s", color_prefix(i), color_to_short_string(i), set->c[i], CRESET);
			strcat(buffer, tmp_buffer);
		}
	}
	sprintf(tmp_buffer, ")");
	strcat(buffer, tmp_buffer);

}