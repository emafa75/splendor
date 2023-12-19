#ifndef __TEST_MARKET_H__
#define __TEST_MARKET_H__

// Returns the number of tests passed
int test_market();


// Tests if init is executable and create correctly all tokens
int test_init_market();


/*
 * Tests if pick_token(int seed) is executable and runs as expected
 *
 * Notes: it executes init_builders
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_pick_token();


int test_market_pay_token();


int test_market_get_token();


#endif
