#ifndef __GUILD_H__
#define __GUILD_H__

#include "builder.h"
#include "stack/stack.h"
#include "builder_constants.h"


struct guild
{
    struct builder_t *builders[MAX_BUILDERS];
    int n_builders;
		struct stack_t available_stack;
		struct builder_t *available[MAX_BUILDERS_AVAILABLE_PER_LVL];
};


struct available_builders {
	struct builder_t *available[MAX_BUILDERS];
	unsigned int n_builders_available; 
};



void init_guild();

/*
    Display all available builders in a guild
*/
void guild_display();


/*
    Returns nb of builders in the guild (available or not)
*/
int guild_nb_builder();


/*
    Returns a booleen if the i-th builder is available
*/
int guild_is_available(int index);


/*
    Pick builder from a guild and make it unavailable
*/
struct builder_t* guild_pick_builder();


/*
    Put builder with id 'id' available again in the guild
*/
void guild_put_builder(struct builder_t *builder);


/*
    Get list of boolean for available builders
*/
struct available_builders get_available_builders();


/*
    Get index for the first available builder after the i-th element, -1 if impossible
*/
// int get_first_available_builder(int i);

#endif
