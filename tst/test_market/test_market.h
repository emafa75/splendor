#ifndef __TEST_MARKET_H__
#define __TEST_MARKET_H__

#include "market.h"
#include "ansi_color.h"
#include "market.h"



// Returns the number of tests passed
int test_market();


// Tests if init is executable and create correctly all tokens
int test_init_market(int seed);


/*
 * Tests if pick_token(int seed) is executable and runs as expected
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_pick_token(int seed);


int test_pay_token(int seed);


int test_get_token(int seed);


int test_get_available_tokens(int seed);

#endif
