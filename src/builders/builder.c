#include "builder.h"
#include "builder_constants.h"
#include "set.h"
#include "skills.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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

	if (seed ==  0)
	{
		while (i < n_builders)
		{
			next_color = (color + 1) % NUM_COLORS;

			builders[i].lvl = lvl;
			builders[i].pts = 5 * (lvl + 1);

			enum color_t c[NUM_COLORS] = {};  // Used to create requries and provides
			for (unsigned int i = 0 ; i < lvl + 2 ; ++i)
				c[(color + i) % NUM_COLORS] = 1;

			builders[i].requires = set_create(c);

			enum color_t c2[NUM_COLORS] = {};  // Used to create requries and provides
			for (unsigned int i = 0 ; i < lvl + 1 ; ++i)
				c2[(color + i) % NUM_COLORS] = 1;

			builders[i].provides = set_create(c2);

			lvl += (color == NUM_COLORS - 1);
			lvl = BUILDER_MIN_LEVEL + lvl % (BUILDER_MAX_LEVEL - BUILDER_MIN_LEVEL);
			color = next_color;
			++i;
		}
	}	
	else
	{
		n_builders = BUILDER_MIN_COUNT + rand() % (MAX_BUILDERS - BUILDER_MIN_COUNT);

		for (int i = 0 ; i < n_builders ; ++i)
		{
			int builder_level = rand() % NUM_LEVELS;
			builders[i].lvl = builder_level;
			builders[i].pts = (builder_level + 1) * 5;
		
			builders[i].provides = create_random_set((builder_level + 1));
		
			builders[i].requires = create_random_set((builder_level + 2));
		}
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
			g->lvl + 1, \
			builder_points(g)
		);


	set_short_display(&builder_require, "requires=");
	printf(", ");
	set_short_display(&builder_provide, "provides=");

	if (has_skills(g))
	{
		printf(", skill(s)=");
		enum skills_id* skills= skills_get_by_trigger(g);

		for (int index = 0; index < MAX_SKILLS_PER_TRIGGER; ++index)
		{
			if (skills[index] != NO_SKILL)
			{
				skill_display(skills[index],(index != 0) ? ", " : "");
			}
		}
	}

	printf(")\n");
}
