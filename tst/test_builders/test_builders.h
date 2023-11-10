#ifndef __TEST_BUILDERS_H__
#define __TEST_BUILDERS_H__

#include <stdio.h>
#include <time.h>

#include "builder.h"
#include "builder_constants.h"


#define SEED 0


// Returns the number of tests passed
int test_builders();


// Tests if init is executable and create all builders
int test_init_builders(int seed);


/*
 * Tests if builder_level() is executable and if the returned level
 * is legal
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_builders_levels(int seed);

/*
 * Tests if builder_pts() returns a legal amount of pts
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_builders_pts(int seed);

/*
 * Tests if builder_level() is executable and if the returned level
 * is legal
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_builders_requires(int seed);

/*
 * Tests if builder_level() is executable and if the returned level
 * is legal
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_builders_provides(int seed);

#endif
