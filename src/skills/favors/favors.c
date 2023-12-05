#include "favors.h"
#include "builder.h"
#include "builder_constants.h"
#include "game.h"
#include "guild.h"
#include "market.h"
#include "queue.h"
#include <stdlib.h>

int favor_renewal(struct turn_t* turn, const void* trigger)
{
	/*
		Get turn instances
	*/
	struct guild_t* game_guild = turn_get_guild(turn);

	/*
		Choose a random level to renew
	*/
	int renewed_level = rand() % NUM_LEVELS;

	/*
		Get all the builder with this level wich are available
	*/

	struct available_builders* available_builders = guild_get_available_builders(game_guild);

	struct builder_t* builders[MAX_BUILDERS_AVAILABLE_PER_LVL] = {};
	int index_b = 0;

	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		struct builder_t* builder = available_builders->builders[index];
		unsigned int builder_lvl = builder_level(builder);
		if( builder_lvl == renewed_level )
		{
			builders[index_b] = builder;
			++index_b;
		}
	}

	/*
		Remove them from the guild and replace it in the queue
	*/

	for (int index = 0; index < MAX_BUILDERS_AVAILABLE_PER_LVL; ++index)
	{
		guild_pick_builder(game_guild, builders[index]);
		guild_put_builder(game_guild, builders[index]);
	}

	return 1;
}