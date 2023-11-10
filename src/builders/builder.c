/**
 *
 * @filename builder.c
 * @date 2023-11-07 14:29
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include "builder.h"
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "builder_constants.h"

struct builder_t {
	unsigned int lvl;
	unsigned int pts;
	struct buildcost_t requires;
	struct buildcost_t provides;
};


static struct builder_t builders[MAX_BUILDERS];
static int n_builders = 0;


void init_builders(unsigned int seed)
{
	srand(seed);

	n_builders = BUILDER_MIN_COUNT + rand() % (MAX_BUILDERS - BUILDER_MIN_COUNT);

	for (int i = 0 ; i < n_builders ; ++i)
	{
		builders[i].lvl = rand() % NUM_LEVELS;
		builders[i].pts = BUILDER_MIN_PTS + rand() % (BUILDER_MAX_PTS - BUILDER_MIN_PTS);

		builders[i].provides.c = rand() % NUM_COLORS;
		builders[i].provides.n = BUILDER_MIN_PROVIDES + rand() % (BUILDER_MAX_PROVIDES - BUILDER_MIN_PROVIDES);

		builders[i].requires.c = rand() % NUM_COLORS;
		builders[i].requires.n = BUILDER_MIN_COST +  rand() % (BUILDER_MAX_COST - BUILDER_MIN_COST);

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









