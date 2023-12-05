
#include "cli_guild.h"
#include "cli_utils.h"
#include "guild.h"
#include <stdio.h>

void display_global_guild(struct vector2_t position, struct guild_t* guild)
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
	printToCoordinates(position.y, position.x, "niv");


}


