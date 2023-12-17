#ifndef __CLI_GUILD_H__
#define __CLI_GUILD_H__

#include "guild.h"
#include "vector2.h"

struct vector2_t display_global_guild(struct vector2_t position, struct guild_t* guild);


void display_global_guild_stacks(struct vector2_t position, struct guild_t* guild, struct vector2_t dimension);


#endif
