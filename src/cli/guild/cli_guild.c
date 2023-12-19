
#include "cli_guild.h"
#include "builder.h"
#include "cli_utils.h"
#include "guild.h"
#include "vector2.h"
#include <stdio.h>
#include "ansi_color.h"

struct vector2_t display_global_guild(struct vector2_t position, struct guild_t* guild)
{
	char text[100] = {};

	// Nb dispo
	sprintf(text, "builders disponibles: %d", guild_nb_builder(guild));
	printToCoordinates(position.y, position.x, text);


	// Nb dispo par stack
	sprintf(text, "builders disponibles: %d", guild_nb_builder(guild));
	printToCoordinates(position.y, position.x, text);
}


void display_global_guild_stacks(struct vector2_t position, struct guild_t* guild, struct vector2_t dimension)
{
	char text[100] = {};
	
	for (int i = 0 ; i < NUM_LEVELS ; ++i)
	{
		
		sprintf(text, "niv - %d: %d dispo", i + 1, guild_get_stack(guild, i));
		printToCoordinates(position.y, position.x, "niv");
	}
}


