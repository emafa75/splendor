#ifndef __BUILDER_H__
#define __BUILDER_H__

#include "color.h"

/** The maximum level for a builder */
#ifndef NUM_LEVELS
  #define NUM_LEVELS 2
#endif

/** The maximum number of builders */
#ifndef MAX_BUILDERS
  #define MAX_BUILDERS 10
#endif

/** A pair representing a number of tokens of the same color that is
    required to buy a builder or that is produced by a builder. */
struct buildcost_t {
  enum color_t c; // the color
  unsigned int n; // the number of tokens
};

/** Abstract struct representing a builder. A builder is identified by
    its level and its index between 0 and num_builders(level)-1. */
struct builder_t;

/** Initializes the builders depending on an integer `seed`.
    Can be called multiple times. Can also do nothing. */
void init_builders(unsigned int seed);

/** Returns the total number of builders in the game. */
unsigned int num_builders();

/** Returns the `index`-th builder and NULL if it does not exist. */
struct builder_t* make_builder(unsigned int index);

/** Returns the level of the builder. */
unsigned int builder_level(const struct builder_t* g);

/** Returns the number of points of the builder. */
unsigned int builder_points(const struct builder_t* g);

/** Returns the cost that must be payed in order to hire this builder. */
struct buildcost_t builder_requires(const struct builder_t* g);

/** Returns the cost of the tokens that can be produced by this builder. */
struct buildcost_t builder_provides(const struct builder_t* g);

/** Displays the builder on the stdout, after a possible prefix.
    Example : builder_display(g, "    - ") displays on the screen :
    - Builder(lvl=1,cost=1W,prod=1B)
*/
void builder_display(const struct builder_t* g, const char* prefix);

#endif // __BUILDER_H__
