#include "test_guild.h"
#include "builder.h"
#include "guild.h"
#include "test_builders.h"
#include <stdio.h>
#include <stdlib.h>
#include "ansi_color.h"

int test_guild()
{
    int test_passed = 0;

    if (test_init_guild())
    {
        printf(GRN "test_init_guild passed\n" CRESET);
        ++test_passed;
    }
    
    if(test_guild_pick_builder())
    {
        printf(GRN "test_guild_pick_builder passed\n" CRESET);
        ++test_passed;
    }
    
    if(test_guild_put_builder())
    {
        printf(GRN "test_guild_put_builder passed\n" CRESET);
        ++test_passed;
    }

    if(test_get_available_builders())
    {
        printf(GRN "test_get_available_builders passed\n" CRESET);
        ++test_passed;
    }

    // if(test_get_first_available_builder())
    // {
    //     printf(GRN "test_get_first_available_builder passed\n" CRESET);
    //     ++test_passed;
    // }
    return test_passed;
}


int test_init_guild()
{
    int seed = time(NULL);

    if (!test_init_builders(seed))
    {
        fprintf(stderr, RED "test_init_guild : test_init_builder didn't run successfully\n" CRESET);
        return 0;
    }

    struct guild_t guild = create_default_guild();
    init_guild(&guild);

    int nb_builder = num_builders();
    int nb_builder_guild = guild_nb_builder(&guild);
    /*
        Check if we have the correct amount of builder in the guild
    */
    if( nb_builder != nb_builder_guild )
    {
        fprintf(stderr, RED "test_init_guild : wrong number of builder in the guild\n" CRESET);
        return 0;
    }

    /*
        Check if all the builders are available and are builders_t*
    */

    for (int index  = 0; index < nb_builder_guild; ++index)
    {
        
        if (guild.builders[index] == NULL)
        {
            fprintf(stderr, RED "test_init_guild : no builder_t* in the guild\n" CRESET);
            return 0;
        }
    }

    return 1;
}

int test_guild_pick_builder()
{
    if (!test_init_guild())
    {
        fprintf(stderr, RED "test_guild_pick_builder : test_init_guild didn't run successfully\n" CRESET);
        return 0;
    }

    /*
        Reset principal guild
    */
    int seed = time(NULL);
    srand(seed);
    struct guild_t guild = create_default_guild();
    init_guild(&guild);

    int index_picked_builder = 0;   
    
    struct builder_t* picked_builder = available_builders_get_builder(&guild, index_picked_builder);

    guild_pick_builder(&guild, picked_builder);

    if (picked_builder == NULL)
    {
        fprintf(stderr, RED "test_guild_pick_builder : no builder_t* return\n" CRESET);
        return 0;
    }
    /*
        Check if the builder is no longer available for the guild
    */
    if (guild_is_available(&guild, picked_builder))
    {
        fprintf(stderr, RED "test_guild_pick_builder : builder is still available. Pointer : %p\n" CRESET, picked_builder);
        builder_display(picked_builder, "Picked builder : ");
        return 0;
    }
    


    
    return 1;
}

int test_guild_put_builder() //nonsense with the new achievement --> maybe if it is possible to steal builders.
{

    if (!test_guild_pick_builder())
    {
        fprintf(stderr, RED "test_guild_put_builder : test_guild_pick_builder didn't run successfully\n" CRESET);
        return 0;
    }
    // int seed = time(NULL);
    // srand(seed);
    // init_guild(); //reset
    // int index_picked_builder = rand()  %  get_available_builders().n_builders_available;
    // struct builder_t* picked_builder = get_available_builders().builders[index_picked_builder];

    // //pick a random builder
    // guild_pick_builder(picked_builder);

    // //put it back and check if he is available
    //guild_put_builder(picked_builder);




    return 1;
}

int test_get_available_builders()
{
    if (!test_guild_pick_builder())
    {
        fprintf(stderr, RED "test_get_available_builders : test_guild_pick_builder didn't run successfully\n" CRESET);
        return 0;
    }

    /*
        Reset principal guild
    */
    int seed = time(NULL);
    srand(seed);
    struct guild_t guild = create_default_guild();
    init_guild(&guild);

    if (guild_nb_builder(&guild) < 2)
    {
        fprintf(stderr, RED "test_get_available_builders : not enough builders to test, need at least 2 builders\n" CRESET);
        return 0;
    }
    
    //test with 2 unavailable builders
    int index_builder = 0;

    guild_pick_builder(&guild, guild_get_available_builders(&guild)->builders[index_builder]);
    guild_pick_builder(&guild, guild_get_available_builders(&guild)->builders[index_builder]);

    struct available_builders* available_builders = guild_get_available_builders(&guild);

    if(available_builders->n_builders_available > MAX_BUILDERS_AVAILABLE_PER_LVL * BUILDER_MAX_LEVEL)
    {
        fprintf(stderr, RED "test_get_available_builders : Too much available builders\n" CRESET);
        return 0;
    }

    return 1;
}

// int test_get_first_available_builder() -- > nonsense with current achievement
// {

//     if (!test_guild_pick_builder())
//     {
//         fprintf(stderr, RED "test_get_first_available_builder : test_guild_pick_builder didn't run successfully\n" CRESET);
//         return 0;
//     }

//     int seed = time(NULL);
//     srand(seed);
//     init_guild(); //reset

//     if (get_first_available_builder(0) > 0)
//     {
//         fprintf(stderr, RED "test_get_first_available_builder : return an index while there is no available builder\n" CRESET);
//         return 0;
//     }

//     if (guild_nb_builder() < 2)
//     {
//         fprintf(stderr, RED "test_get_first_available_builder : not enough builders to test, need at least 2 builders\n" CRESET);
//         return 0;
//     }

//     int index_builder_1 = rand() % guild_nb_builder();
//     int index_builder_2 = rand() % guild_nb_builder();


//     while (index_builder_1 == index_builder_2)
//     {
//         index_builder_2 = rand() % guild_nb_builder();
//     }

//     guild_pick_builder(index_builder_1);
//     guild_pick_builder(index_builder_2);

//     int first_available_builder = get_first_available_builder(0);
//     /*  
//         Check if this index is available
//     */
//     if (!guild_is_available(first_available_builder))
//     {
//         fprintf(stderr, RED "test_get_first_available_builder : index return is not available\n" CRESET);
//         return 0;
//     }
//     /*
//         Test if it's the first available builder
//     */
//     if( (first_available_builder == index_builder_1 && index_builder_1 > index_builder_2) || (first_available_builder == index_builder_2 && index_builder_2 > index_builder_1))
//     {
//         fprintf(stderr, RED "test_get_first_available_builder : do not return the first available index\n" CRESET);
//         return 0;
//     }

//     return 1;
// }