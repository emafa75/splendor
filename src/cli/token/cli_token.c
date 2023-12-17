#include "cli_token.h"
#include "cli_set.h"
#include "cli_utils.h"
#include "set.h"
#include "token_second_header.h"
#include <stdio.h>

void cli_token_display(struct vector2_t position, struct token_t* token, char* prefix)
{
	char buffer[BUFFER_SIZE]= {};
	struct set_t token_set = token_get_set(token);
	cli_set_display(buffer, &token_set);
	
	char tmp_buffer[BUFFER_SIZE + 100] = {};
	sprintf(tmp_buffer, "%sToken(%s)", prefix, buffer);
	printToCoordinates(position.x, position.y, tmp_buffer);
}