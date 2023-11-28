#ifndef __PERMUTATION_H__
#define __PERMUTATION_H__

#include "token.h"
#include <stdlib.h>

struct permutation{
    int permutation[NUM_TOKENS];
};

/*
    Returns the identity permutation
*/
struct permutation identity();


/*
    Returns a random permutation
*/
struct permutation random_permutation(int random_seed);

#endif