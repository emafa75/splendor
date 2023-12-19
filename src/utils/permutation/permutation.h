#ifndef __PERMUTATION_H__
#define __PERMUTATION_H__

#include "token.h"


struct permutation_t{
	int permutation[NUM_TOKENS];
};


/*
	Returns the identity permutation
*/
struct permutation_t identity();


/*
	Returns a random permutation
*/
struct permutation_t random_permutation();

#endif
