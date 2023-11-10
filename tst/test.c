/**
 *
 * @filename test.c
 * @date 2023-11-07 16:04
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#define SEED 0

#include <stdlib.h>

#include <stdio.h>

#include "builder.h"
#include "guild.h"

#define _NB_MIN_PARAMS_ 1


void print_usage(char *argv[]);


int main(int argc, char *argv[])
{
	if (argc < _NB_MIN_PARAMS_)
	{
		print_usage(argv);
		return EXIT_FAILURE;
	}

	init_builders(SEED);
	init_guild();
	
	struct builder_t *builder;
	builder = make_builder(0);


	return EXIT_SUCCESS;
}


void print_usage(char *argv[])
{
	fprintf(stderr, "Usage: %s ....\n", argv[0]);
	return;
}
