/**
 *
 * @filename test.c
 * @date 2023-11-07 16:04
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include "cli_tests.h"
#include "test_can_buy.h"
#include "test_players.h"
#include "test_skills.h"
#define SEED 0

#include <stdlib.h>
#include <stdio.h>

#include "test_builders.h"
#include "test_tokens.h"
#include "test_guild.h"
#include "test_market.h"

#define _NB_MIN_PARAMS_ 1


void print_usage(char *argv[]);


int main(int argc, char *argv[])
{
	if (argc < _NB_MIN_PARAMS_)
	{
		print_usage(argv);
		return EXIT_FAILURE;
	}

	// test_token();
	// test_builders();
	// test_market();
	// test_guild();
	// test_players();
	// test_utils();
	// test_skills();
	
	cli_tests();
	return EXIT_SUCCESS;
}


void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s ....\n", argv[0]);
	return;
}
