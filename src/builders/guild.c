
#include "guild.h"
#include "builder.h"
#include "stack.h"

struct guild
{
	struct builder_t *builders[MAX_BUILDERS];
	int n_builders;
	struct stack_t available_stack[NUM_LEVELS];
	struct available_builders available_builders;
};


// Guild is only accessible from this file
static struct guild guild;


void init_guild()
{
	struct builder_t * builder;
	int builder_lvl;
	int available_builders_index = 0;
	
	// Init stack
	guild.n_builders = num_builders();
	for (int index = 0; index < guild.n_builders; ++index)
	{
		builder = make_builder(index);
		builder_lvl = builder_level(builder);

		stack_append(&guild.available_stack[builder_lvl - 1], builder);
	}

	// Init available_builders
	for (int level = BUILDER_MIN_LEVEL ; level < BUILDER_MAX_LEVEL ; ++level) {
		for (int i = 0 ; i < MAX_BUILDERS_AVAILABLE_PER_LVL ; ++i)
		{
			guild.available_builders.builders[available_builders_index] = stack_pop(&guild.available_stack[level - 1]);
			++available_builders_index;
		}
	}
}


int guild_nb_builder()
{
  return guild.n_builders;
}

void guild_display()
{
	struct builder_t* builder;
	for (unsigned int index = 0 ; index < MAX_BUILDERS ; ++index)
	{
		builder = guild.available_builders.builders[index];

		if (builder != NULL)
			builder_display(guild.available_builders.builders[index], " --- ");
	}
}


struct builder_t* guild_pick_builder(struct builder_t * builder)
{
	int builder_lvl = builder_level(builder);
	struct builder_t *new_builder;

	int index = 0;
	while (available_builders_get_builder(index) != builder)
		++index;

	new_builder = stack_pop(&guild.available_stack[builder_lvl - 1]);
	guild.available_builders.builders[index] = new_builder;

	return builder;
}


void guild_put_builder(struct builder_t * builder)
{
	int builder_lvl = builder_level(builder);
	stack_append(&guild.available_stack[builder_lvl - 1], builder);
}


struct available_builders get_available_builders()
{
    return guild.available_builders;
}


struct builder_t *available_builders_get_builder(int index)
{
	return guild.available_builders.builders[index];
}

// int get_first_available_builder(int i)
// {
//
//     struct available_builders available_builders = get_available_builders();
//     for (int index = i; index < MAX_BUILDERS; ++index) {
//         if (available_builders.available[index])
//         {
//             return index;
//         }
//     }
//     return -1;
// }

int guild_is_available(struct builder_t* builder){
	for (int index = 0; index < MAX_BUILDERS; ++index)
	{
		if(get_available_builders().builders[index] == builder)
		{
			return 1;
		}
	}
	return 0;
}
