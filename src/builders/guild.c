#include "guild.h"


struct guild_t create_default_guild()
{
	struct guild_t out = {};
	return out;
}


void init_guild(struct guild_t* guild)
{
	// Vars used in loops
	struct builder_t* builder;
	struct stack_t* stack;
	int builder_lvl;

	struct available_builders* available_builders;

	int available_builders_index = 0;

	//reset stacks
	for (int index = 0 ; index < NUM_LEVELS ; ++index)
	{
		guild->available_stack[index] = create_default_stack();
	}

	// Init stacks
	guild->n_builders = num_builders();
	for (int index = 0 ; index < guild->n_builders ; ++index)
	{
		builder = make_builder(index);
		builder_lvl = builder_level(builder);
		stack = guild_get_stack(guild, builder_lvl);
		fprintf(stderr, "builder_lvl: %d, stack: %p\n", builder_lvl, stack);
		guild->builders[index] = builder;
		// stack_append(stack, builder);
	}

	// Init available_builders
	for (int level = BUILDER_MIN_LEVEL ; level < BUILDER_MAX_LEVEL ; ++level) {
		for (int i = 0 ; i < MAX_BUILDERS_AVAILABLE_PER_LVL ; ++i)
		{
			stack = guild_get_stack(guild, level);
			builder = stack_pop(stack);
			available_builders = guild_get_available_builders(guild);

			// Not really clean but this is init function, and
			available_builders->builders[available_builders_index] = builder;
			++available_builders_index;
		}
	}
}


struct stack_t* guild_get_stack(struct guild_t* guild, unsigned int builder_lvl)
{
	return &guild->available_stack[builder_lvl - 1];  // -1 because lvls starts at 1
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
			builder_display(builder, " --- ");
	}
}


struct builder_t* guild_pick_builder(struct guild_t* guild, struct builder_t* builder)
{
	int builder_lvl = builder_level(builder);

	struct builder_t* new_builder;

	struct stack_t* builder_stack = guild_get_stack(guild, builder_lvl);

	// Finds builder's index to replace it with the new builder
	int index = 0;
	while (available_builders_get_builder(guild, index) != builder)
		++index;

	new_builder = stack_pop(builder_stack);
	guild->available_builders.builders[index] = new_builder;  // place it on builder's index

	return builder;
}


void guild_put_builder(struct guild_t* guild, struct builder_t* builder)
{
	int builder_lvl = builder_level(builder);

	// builder_lvl - 1 because levels start at 1
	struct stack_t* stack = guild_get_stack(guild, builder_lvl);
	stack_append(stack, builder);
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
