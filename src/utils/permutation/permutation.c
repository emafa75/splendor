#include "permutation.h"
#include "token.h"


struct permutation identity()
{
    struct permutation permutation = {};
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        permutation.permutation[index]=index;
    }
    return permutation;
}

struct permutation random_permutation(int random_seed)
{
    srand(random_seed);
    struct permutation permutation = identity();
    int rand_index = 0;
    int tmp = 0;
    //shuffle identity permutation
    for (int index = 0; index < NUM_TOKENS; ++index)
    {
        rand_index = index + rand() % (NUM_TOKENS - index);
        tmp = permutation.permutation[rand_index];
        permutation.permutation[rand_index] = permutation.permutation[index];
        permutation.permutation[index] = tmp;
    }
    return permutation;

}