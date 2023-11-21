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
#include "ansi_color.h"
#include "color_second_header.h"
#include "set.h"

struct builder_t {
	unsigned int lvl;
	unsigned int pts;
	struct set_t requires;
	struct set_t provides;
};


static struct builder_t builders[MAX_BUILDERS] = {};
static int n_builders = 0;


void init_builders(unsigned int seed)
{
	srand(seed);
	int i = 0;
	unsigned int lvl = BUILDER_MIN_LEVEL;
	enum color_t color = 0;
	enum color_t next_color;

	n_builders = MAX_BUILDERS;

	while (i < n_builders)
	{
		next_color = (color + 1) % NUM_COLORS;

		builders[i].lvl = lvl;
		builders[i].pts = 5 * lvl;

		enum color_t c[NUM_COLORS] = {};  // Used to create requries and provides
		for (unsigned int i = 0 ; i < lvl + 1 ; ++i)
			c[(color + i) % NUM_COLORS] = 1;

		builders[i].requires = set_create(c);
		// builders[i].requires.c = color;
		// builders[i].requires.n = lvl + 1;

		enum color_t c2[NUM_COLORS] = {};  // Used to create requries and provides
		for (unsigned int i = 0 ; i < lvl ; ++i)
			c2[(color + i) % NUM_COLORS] = 1;

		builders[i].provides = set_create(c2);
		// builders[i].provides.c = next_color;
		// builders[i].provides.n = lvl;

		lvl += (color == NUM_COLORS - 1);
		lvl = BUILDER_MIN_LEVEL + lvl % (BUILDER_MAX_LEVEL - BUILDER_MIN_LEVEL);
		color = next_color;
		++i;
	}
	

	// n_builders = BUILDER_MIN_COUNT + rand() % (MAX_BUILDERS - BUILDER_MIN_COUNT);
	//
	// for (int i = 0 ; i < n_builders ; ++i)
	// {
	// 	builders[i].lvl = rand() % NUM_LEVELS;
	// 	builders[i].pts = BUILDER_MIN_PTS + rand() % (BUILDER_MAX_PTS - BUILDER_MIN_PTS +1);
	//
	// 	builders[i].provides.c = rand() % NUM_COLORS;
	// 	builders[i].provides.n = BUILDER_MIN_PROVIDES + rand() % (BUILDER_MAX_PROVIDES - BUILDER_MIN_PROVIDES + 1);
	//
	// 	builders[i].requires.c = rand() % NUM_COLORS;
	// 	builders[i].requires.n = BUILDER_MIN_COST +  rand() % (BUILDER_MAX_COST - BUILDER_MIN_COST + 1);
	//
	// }
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


struct set_t builder_requires(const struct builder_t *g)
{
	return g->requires;
}


struct set_t builder_provides(const struct builder_t *g)
{
	return g->provides;
}


void builder_display(const struct builder_t *g, const char *prefix)
{
	struct set_t builder_require = builder_requires(g);
	struct set_t builder_provide = builder_provides(g);

	printf("%sBuilder(lvl=%d, points=%d, ", \
			prefix, \
			g->lvl, \
			builder_points(g)
			);


	set_short_display(&builder_require, "requires=");
	printf(", ");
	set_short_display(&builder_provide, "provides=");

	printf(")\n");
}

