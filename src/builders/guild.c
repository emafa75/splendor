#include "guild.h"
#include <stdio.h>


static struct guild guild;
void init_guild()
{
    guild.n_builders = MAX_BUILDERS;
    for (int index = 0; index < MAX_BUILDERS; ++index)
    {
        guild.builders[index] = make_builder(index);
        guild.available[index] = 1;
    }
    guild_display(guild);
    
}

void guild_display(const struct guild guild)
{
    for (int index = 0 ; index < guild.n_builders ; ++index)
    {
        if(guild.available[index])
        {
            builder_display(guild.builders[index], " --- ");
        }
    }
}

struct builder_t* guild_pick_builder(struct guild *guild, int id)
{
    guild->available[id] = 0;
    return guild->builders[id];
}

void guild_put_builder(struct guild *guild, int id)
{
    guild->available[id] = 1;
}
