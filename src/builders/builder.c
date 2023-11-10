/**
 *
 * @filename builder.c
 * @date 2023-11-07 14:29
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include "builder.h"
#include "color.h"

#ifndef STDLIB
	#include <stdlib.h>
	#define STDLIB
#endif

#ifndef STDIO
	#include <stdio.h>
	#define STDIO
#endif

struct builder_t {
	unsigned int lvl;
	unsigned int pts;
	struct buildcost_t requires;
	struct buildcost_t provides;
};


static struct builder_t builders[MAX_BUILDERS];
static int n_builders = 0;


static unsigned int max(unsigned int a, unsigned int b)
{
	if (a < b)
		return b;

	return a;
}


void init_builders(unsigned int seed)
{
	srand(seed);

	n_builders = max(rand() % MAX_BUILDERS, MIN_BUILDERS);

	for (int i = 0 ; i < n_builders ; ++i)
	{
		builders[i].lvl = rand() % NUM_LEVELS;
		builders[i].pts = 0;

		builders[i].provides.c = rand() % MAX_COLORS;
		builders[i].provides.n = rand() % MAX_PROVIDES;

		builders[i].requires.c = rand() % MAX_COLORS;
		builders[i].requires.c = rand() % MAX_COST;

	}
}


unsigned int num_builders()
{
	return n_builders;
}


struct builder_t* make_builder(unsigned int index)
{
	if (index >= MAX_BUILDERS)
		return NULL;

	return &builders[index];
}


unsigned int builder_level(const struct builder_t *g)
{
	return g->lvl;
}


unsigned int builder_points(const struct builder_t *g)
{
	return g->pts;
}


struct buildcost_t builder_requires(const struct builder_t *g)
{
	return g->requires;
}


struct buildcost_t builder_provides(const struct builder_t *g)
{
	return g->provides;
}


void builder_display(const struct builder_t *g, const char *prefix)
{
	printf("%sBuilder(lvl=%d,cost=%d%s,prod=%d%s)\n", \
			prefix, \
			g->lvl, \
			g->requires.n, \
			color_to_short_string(g->requires.c), \
			g->provides.n,
			color_to_short_string(g->provides.c)
			);
}









