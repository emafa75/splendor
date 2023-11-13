#ifndef __TEST_TOKEN_H__
#define __TEST_TOKEN_H__

#include "token.h"
#include "color.h"
#include <stdio.h>
#include "ansi_color.h"


// Returns the number of tests passed
int test_token();


int test_token_legal(struct token_t token);


int test_create_simple_token();


/*
 * Tests if create_complex_token() runs as expected
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_create_complex_token();

/*
 * Tests if test_token_equals() runs as expected
 *
 * Returns 1 if runs as expected, 0 otherwise
 */
int test_token_equals();

#endif
