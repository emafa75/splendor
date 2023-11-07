/**
 *
 * @filename builder.c
 * @date 2023-11-07 14:29
 * @author Nemo D'ACREMONT <nemo.dacremont@enseirb-matmeca.fr>
 * @brief ...
 *
 */

#include "builder.h"

static struct builder_t *builders[MAX_BUILDERS] = {};


void init_builders(unsigned int seed)
{
	for (int i = 0 ; i < MAX_BUILDERS ; ++i)
	{
		static struct builder_t builder = {};
		builders[i] = &builder;
	}
}


unsigned int num_builders()
{
	int i = 0;

	while (builders[i] != 0 && i < MAX_BUILDERS)
		++i;

	return i + 1;  // + 1 for 1 based indexing
}


struct builder_t* make_builder(unsigned int index)
{
	if (index >= MAX_BUILDERS)
		return NULL;

	return builders[index];
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
	// printf("Builder(lvl=%d,cost=%d%s,prod=%d%c)", g->lvl, g.);
}









