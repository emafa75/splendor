#include "guild.h"
#include "ansi_color.h"
#include "builder.h"
#include "queue.h"
#include "skills.h"
#include <stdio.h>
#include "builder_constants.h"
#include <stdlib.h>


struct guild_t create_default_guild()
{
	struct guild_t out = {};
	return out;
}


void init_guild(struct guild_t* guild)
{
	// Vars used in loops
	struct builder_t* builder;
	struct queue_t* queue;
	int builder_lvl;
	//reset stacks
	for (int index = 0 ; index < NUM_LEVELS ; ++index)
	{
		guild->available_queue[index] = create_default_queue();
	}

	// Init stacks
	guild->n_builders = num_builders();
	for (int index = 0 ; index < guild->n_builders ; ++index)
	{
		builder = make_builder(index);
		builder_lvl = builder_level(builder);
		queue = guild_get_queue(guild, builder_lvl);
		guild->builders[index] = builder;
		queue_append(queue, builder);
	}

	// Init available_builders
	for (int level = BUILDER_MIN_LEVEL ; level < BUILDER_MAX_LEVEL ; ++level) {
		for (int i = 0 ; i < MAX_BUILDERS_AVAILABLE_PER_LVL ; ++i)
		{
			queue = guild_get_queue(guild, level);
			builder = queue_dequeue(queue);

			guild_make_builder_available(guild, builder);
		}
	}
}

void init_builder_skills()
{
	int nb_builders = num_builders();
	struct builder_t* builder = NULL;
	int builder_lvl = 0;

	for (int index = 0; index < nb_builders; ++index)
	{
		builder = make_builder(index);
		builder_lvl = builder_level(builder);
		enum skills_id skills[MAX_SKILLS_PER_TRIGGER] = {};
		int index_skill_to_add = 0;

		for (enum skills_id skill_id = BUILDER_FIRST_SKILL ; skill_id <= BUILDER_LAST_SKILL ; ++ skill_id)
		{
			if (index_skill_to_add < MAX_SKILLS_PER_TRIGGER) //if we can still add a skill to the current builder
			{
				int random_int = rand() % MAX_BUILDERS;
				if(random_int < 1 + builder_lvl) // lvl+1/MAX_BUILDERS chance to have the skill
				{
					skills[index_skill_to_add] = skill_id;
					++index_skill_to_add;
				}
				
			}
		}

		add_skill_instance(builder, skills);
	}
}

struct queue_t* guild_get_queue(struct guild_t* guild, unsigned int builder_lvl)
{
	return &guild->available_queue[builder_lvl]; 
}


int guild_nb_builder(struct guild_t* guild)
{
  return guild->n_builders;
}


void guild_display(struct guild_t* guild)
{
	struct builder_t* builder;  // Used in the loop
	struct available_builders* available_builders = guild_get_available_builders(guild);

	for (unsigned int index = 0 ; index < MAX_BUILDERS ; ++index)
	{
		builder = available_builders->builders[index];

		if (builder != NULL)
		{
			builder_display(builder, " --- ");						
		}
	}
	if (guild_nb_builder(guild) == 0)
	{
		printf(WHT " --- No builder in guild\n" CRESET);
	}
}


struct builder_t* guild_pick_builder(struct guild_t* guild, struct builder_t* builder)
{
	int builder_lvl = builder_level(builder);
	struct builder_t* new_builder;

	struct queue_t* builder_queue = guild_get_queue(guild, builder_lvl);

	// Finds builder's index to replace it with the new builder
	int index = 0;
	while (available_builders_get_builder(guild, index) != builder)
		++index;
	
	guild->available_builders.builders[index] = NULL; 
	--guild_get_available_builders(guild)->n_builders_available;
	new_builder = queue_dequeue(builder_queue);	
	guild_make_builder_available(guild, new_builder);

	// place it on builder's index
	-- guild->n_builders;
	return builder;
}


void guild_put_builder(struct guild_t* guild, struct builder_t* builder)
{
	int builder_lvl = builder_level(builder);
	struct queue_t* queue = guild_get_queue(guild, builder_lvl);
	queue_append(queue, builder);
	++guild->n_builders;

	/*
		If not enough builder available for hiring
	*/
	if (guild_nb_builder_per_level(guild, builder_lvl) < MAX_BUILDERS_AVAILABLE_PER_LVL)
	{
		builder = queue_dequeue(queue);
		guild_make_builder_available(guild, builder);
	}

}


struct builder_t* available_builders_get_builder(struct guild_t* guild, int index)
{
	return guild->available_builders.builders[index];
}


struct available_builders* guild_get_available_builders(struct guild_t* guild)
{
    return &guild->available_builders;
}


int guild_is_available(struct guild_t* guild, struct builder_t* builder){
	struct available_builders* available_builders = guild_get_available_builders(guild);

	// Search for a pointer equal to builder in available_builders
	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(available_builders->builders[index] == builder)
		{
			return 1;
		}
	}

	return 0;
}

int guild_is_present_in_guild(struct guild_t* guild, struct builder_t* builder)
{
	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(guild->builders[index] == builder)
		{
			return 1;
		}
	}

	return 0;
}

void guild_make_builder_available(struct guild_t *guild, struct builder_t* builder)
{
	if (builder == NULL)
	{
		return;
	}
	struct available_builders* available_builders = guild_get_available_builders(guild);
	int index = 0;
	while (available_builders_get_builder(guild, index) != NULL)
	{
		++index;
	}
	available_builders->builders[index] = builder;
	++available_builders->n_builders_available;
}

int guild_nb_builder_per_level(struct guild_t* guild, unsigned int level)
{
	struct available_builders* available_builders = guild_get_available_builders(guild);
	int count = 0;
	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		struct builder_t* builder = available_builders->builders[index];
		if (builder && builder_level(builder) == level)
		{
			++count;
		}
	}
	return count;
}