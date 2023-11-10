#ifndef __GUILD_H__
#define __GUILD_H__

#include "builder.h"


struct guild
{
    struct builder_t *builders[MAX_BUILDERS];
    int n_builders;
    int available[MAX_BUILDERS];
};

struct available_builders {
	int available[MAX_BUILDERS];
    int n_builders_available; 
};



void init_guild();

/*
    Display all available builders in a guild
*/
void guild_display();

/*
    Pick builder from a guild and make it unavailable
*/
struct builder_t* guild_pick_builder(int id);

/*
    Put builder with id 'id' available again in the guild
*/
void guild_put_builder(int id);

struct available_builders get_available_builders();

#endif