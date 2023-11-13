#include "guild.h"
#include "builder.h"
#include "market.h"
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

int guild_nb_builder()
{
    return guild.n_builders;
}

int guild_is_available(int index)
{
    return guild.available[index];
}

void guild_display()
{
    for (int index = 0 ; index < guild.n_builders ; ++index)
    {
        if(guild_is_available(index))
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
    for (int index = 0 ; index < MAX_BUILDERS ; ++index)
    {
        if (guild_is_available(index))
        {
            available_builders.available[index] = 1;
            ++size;
        }
    }
    available_builders.n_builders_available = size;
    return available_builders;
}

int get_first_available_builder(int i)
{
    struct available_builders available_builders = get_available_builders();
    for (int index = i; index < MAX_BUILDERS; ++index) {
        if (available_builders.available[index])
        {
            return index;
        }
    }
    return -1;
}