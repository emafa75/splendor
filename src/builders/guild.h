#ifndef __GUILD_H__
#define __GUILD_H__

#include <stdio.h>

#include "builder.h"
#include "queue.h"



struct available_builders {
	struct builder_t *builders[MAX_BUILDERS];
	unsigned int n_builders_available;
};


struct guild_t
{
	struct builder_t *builders[MAX_BUILDERS];
	int n_builders;
	struct queue_t available_queue[NUM_LEVELS];
	struct available_builders available_builders;
};


/*
 *  Create a guild with default parameters
 *  ATM: everything is set to 0
 */
struct guild_t create_default_guild();


/*
 *  Init the guild as the global guild should be
 */
void init_guild(struct guild_t* guild);

/*
    Associate skills for the builders
*/
void init_builder_skills();

/*
 *  Returns a pointer to the guild's queue storing builders of level builder_lvl
 */
struct queue_t* guild_get_queue(struct guild_t* guild, unsigned int builder_lvl);


/*
    Display all available builders in a guild
*/
void guild_display(struct guild_t* guild);


/*
    Returns nb of builders in the guild (available or not)
*/
int guild_nb_builder(struct guild_t* guild);


/*
    Check if pointer of builder is available to hire in the guild
*/
int guild_is_available(struct guild_t* guild, struct builder_t* builder);

/*
    Check if a builder is present in guild
*/
int guild_is_present_in_guild(struct guild_t* guild, struct builder_t* builder);
/*
    Pick builder from a guild and make it unavailable
*/
struct builder_t* guild_pick_builder(struct guild_t* guild, struct builder_t *builder);


/*
    Put builder in the guild
*/
void guild_put_builder(struct guild_t* guild, struct builder_t* builder);


/*
    Get struct available_builders with the number of available builders and list of builder_t pointer
*/
struct available_builders* guild_get_available_builders(struct guild_t* guild);


/*
 *  Get the index-th buidler in guild.available_builders.builders
 */
struct builder_t* available_builders_get_builder(struct guild_t* guild, int index);
#endif
