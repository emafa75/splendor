#include "guild.h"
#include "builder.h"
#include <stdio.h>


static struct guild guild;
void init_guild()
{
    guild.n_builders = num_builders();
    for (int index = 0; index < guild.n_builders; ++index)
    {
        guild.builders[index] = make_builder(index);
        guild.available[index] = 1;
    }
    
}

void guild_display()
{
    for (int index = 0 ; index < guild.n_builders ; ++index)
    {
        if(guild.available[index])
        {
            builder_display(guild.builders[index], " --- ");
        }
    }
}

struct builder_t* guild_pick_builder(int id)
{
    guild.available[id] = 0;
    return guild.builders[id];
}

void guild_put_builder(int id)
{
    guild.available[id] = 1;
}

struct available_builders get_available_builders()
{
    int size = 0;
    struct available_builders available_builders ={0};
    for (unsigned int index = 0 ; index < MAX_BUILDERS ; ++index)
    {
        if (guild.available[index])
        {
            available_builders.available[index] = 1;
            ++size;
        }
    }
    available_builders.n_builders_available = size;
    return available_builders;
}