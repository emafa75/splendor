
#include "cli_guild.h"
#include "builder.h"
#include "cli_builders.h"
#include "cli_utils.h"
#include "guild.h"
#include "vector2.h"
#include <stdio.h>

void display_global_guild(struct vector2_t position, struct guild_t* guild)
{
	char text[100] = {};

	// Nb dispo
	
	/*
		Print available builders
	*/
	struct available_builders* available_builders = guild_get_available_builders(guild);
	struct builder_t* builder;

	sprintf(text, "Game guild (%d) : ", available_builders->n_builders_available);
	printToCoordinates(position.x, position.y, text);
	position = vector2_add(position, vector2_down());

	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		builder = available_builders->builders[index];
		if( builder != NULL)
		{
			cli_builder_display(position, builder, " --- ");
			position = vector2_add(position, vector2_down());
		}
	}
	
}


void display_global_guild_stacks(struct vector2_t position, struct guild_t* guild, struct vector2_t dimension)
{
	printToCoordinates(position.y, position.x, "niv");


}


