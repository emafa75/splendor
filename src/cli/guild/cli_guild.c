
#include "cli_guild.h"
#include "builder.h"
#include "cli_builders.h"
#include "cli_utils.h"
#include "guild.h"
#include "vector2.h"
#include <stdio.h>
#include "ansi_color.h"

struct vector2_t display_global_guild(struct vector2_t position, struct guild_t* guild)
{
	char text[100] = {};

	// Nb dispo
	
	/*
		Print available builders
	*/
	struct available_builders* available_builders = guild_get_available_builders(guild);
	struct builder_t* builder;

	sprintf(text, BOLD "Game guild (%d) : " CRESET, available_builders->n_builders_available);
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

	return position;
	
}


