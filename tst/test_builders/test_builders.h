#ifndef __TEST_BUILDERS_H__
#define __TEST_BUILDERS_H__

#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdio.h>
#endif

#include "builder.h"


#define SEED 0


// Returns the number of tests passed
int test_builders();


// Tests if init is executable and create all builders
int test_init_builders();


/*
 * Tests if builder_level() is executable and if the returned level
 * is legal
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs well, 0 otherwise
 */
int test_builders_levels();


/*
 * Tests if builder_level() is executable and if the returned level
 * is legal
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs well, 0 otherwise
 */
int test_builders_requires();

#endif
