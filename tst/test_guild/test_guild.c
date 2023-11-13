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

    if(test_get_first_available_builder())
    {
        printf(GRN "test_get_first_available_builder passed\n" CRESET);
        ++test_passed;
    }
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
    init_guild();

    int nb_builder = num_builders();
    int nb_builder_guild = guild_nb_builder();
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
        if (!guild_is_available(index))
        {
            fprintf(stderr, RED "test_init_guild : Buidlers are not all available after init\n" CRESET);
            return 0;
        }
        if (make_builder(index) == NULL)
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
    int seed = time(NULL);
    srand(seed);
    init_guild(); //reset
    int index_picked_builder = rand() % guild_nb_builder();

    struct builder_t* picked_builder = guild_pick_builder( index_picked_builder );

    if (picked_builder == NULL)
    {
        fprintf(stderr, RED "test_guild_pick_builder : no builder_t* return\n" CRESET);
        return 0;
    }
    /*
        Check if the builder is no longer available for the guild
    */
    if (guild_is_available(index_picked_builder))
    {
        fprintf(stderr, RED "test_guild_pick_builder : builder is still available\n" CRESET);
        return 0;
    }
    


    
    return 1;
}

int test_guild_put_builder()
{

    if (!test_guild_pick_builder())
    {
        fprintf(stderr, RED "test_guild_put_builder : test_guild_pick_builder didn't run successfully\n" CRESET);
        return 0;
    }
    int seed = time(NULL);
    srand(seed);
    init_guild(); //reset
    int index_picked_builder = rand() % guild_nb_builder();

    //pick a random builder
    guild_pick_builder(index_picked_builder);

    //put it back and check if he is available
    guild_put_builder(index_picked_builder);

    if(!guild_is_available(index_picked_builder)) 
    {
        fprintf(stderr, RED "test_guild_put_builder : the builder is still not available\n " CRESET);
        return 0;
    }



    return 1;
}

int test_get_available_builders()
{
    if (!test_guild_pick_builder())
    {
        fprintf(stderr, RED "test_get_available_builders : test_guild_pick_builder didn't run successfully\n" CRESET);
        return 0;
    }

    int seed = time(NULL);
    srand(seed);
    init_guild(); //reset

    if (guild_nb_builder() < 2)
    {
        fprintf(stderr, RED "test_get_available_builders : not enough builders to test, need at least 2 builders\n" CRESET);
        return 0;
    }
    
    //test with 2 unavailable builders
    int index_builder_1 = rand() % guild_nb_builder();
    int index_builder_2 = rand() % guild_nb_builder();


    while (index_builder_1 == index_builder_2)
    {
        index_builder_2 = rand() % guild_nb_builder();
    }

    guild_pick_builder(index_builder_1);
    guild_pick_builder(index_builder_2);

    struct available_builders available_builders = get_available_builders();

    if(available_builders.n_builders_available != (num_builders()-2))
    {
        fprintf(stderr, RED "test_get_available_builders : wrong number of available builders\n" CRESET);
        return 0;
    }
    for (int index = 0; index < guild_nb_builder(); ++index)
    {
        if (index  == index_builder_1 || index == index_builder_2)
        {
            /*
                Check if the pikced builders are not in the list of available builders
            */
            if(available_builders.available[index])
            {
                fprintf(stderr, RED "test_get_available_builders : returns builders index which are supposed to be unavailable\n" CRESET);
                return 0;
            }
        } 
        else {
            /*
                Check if available builders are in the list
            */
            if(!available_builders.available[index])
            {
                fprintf(stderr, RED "test_get_available_builders : some available builders are not listed\n" CRESET);
                return 0;
            }
        }
    }

    return 1;
}

int test_get_first_available_builder()
{

    if (!test_guild_pick_builder())
    {
        fprintf(stderr, RED "test_get_first_available_builder : test_guild_pick_builder didn't run successfully\n" CRESET);
        return 0;
    }

    int seed = time(NULL);
    srand(seed);
    init_guild(); //reset

    if (get_first_available_builder(0) > 0)
    {
        fprintf(stderr, RED "test_get_first_available_builder : return an index while there is no available builder\n" CRESET);
        return 0;
    }

    if (guild_nb_builder() < 2)
    {
        fprintf(stderr, RED "test_get_first_available_builder : not enough builders to test, need at least 2 builders\n" CRESET);
        return 0;
    }

    int index_builder_1 = rand() % guild_nb_builder();
    int index_builder_2 = rand() % guild_nb_builder();


    while (index_builder_1 == index_builder_2)
    {
        index_builder_2 = rand() % guild_nb_builder();
    }

    guild_pick_builder(index_builder_1);
    guild_pick_builder(index_builder_2);

    int first_available_builder = get_first_available_builder(0);
    /*  
        Check if this index is available
    */
    if (!guild_is_available(first_available_builder))
    {
        fprintf(stderr, RED "test_get_first_available_builder : index return is not available\n" CRESET);
        return 0;
    }
    /*
        Test if it's the first available builder
    */
    if( (first_available_builder == index_builder_1 && index_builder_1 > index_builder_2) || (first_available_builder == index_builder_2 && index_builder_2 > index_builder_1))
    {
        fprintf(stderr, RED "test_get_first_available_builder : do not return the first available index\n" CRESET);
        return 0;
    }

    return 1;
}