
#include "test_builders.h"
#include "builder.h"
#include "color.h"
#include "set.h"

int test_builders()
{
	int i = 0;  // number of passed tests
	int seed = time(NULL);  // Use random seed

	if (test_init_builders(seed))
	{
		printf(GRN "test_init_builders passed\n" CRESET);
		++i;
	}


	if (test_builders_levels(seed))
	{
		printf(GRN "test_builders_levels passed\n" CRESET);
		++i;
	}


	if (test_builders_pts(seed))
	{
		printf(GRN "test_builders_pts passed\n" CRESET);
		++i;
	}


	if (test_builders_requires(seed))
	{
		printf(GRN "test_builders_requires passed\n" CRESET);
		++i;
	}


	if (test_builders_provides(seed))
	{
		printf(GRN "test_builders_provides passed\n" CRESET);
		++i;
	}

	return i;
}


int test_init_builders(int seed)
{
	init_builders(seed);
	int n = num_builders();
	struct builder_t *builder;

	// Test if enough builders have been created
	if (n < BUILDER_MIN_COUNT)
	{
		fprintf(stderr, RED "test_init_builders: not enough builders have been created.\n" CRESET);
		return 0;
	}

	if (n > MAX_BUILDERS)
	{
		fprintf(stderr, RED "test_init_builders: too many builders have been created.\n" CRESET);
		return 0;
	}


	// Tests if all builders are actually builders
	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		if (builder == NULL)
		{
			fprintf(stderr, RED "test_init_builders: init_builders() don't create the right amount of builders\n" CRESET);
			return 0;
		}
	}

	return 1;
}


int test_builders_levels(int seed)
{
	// make sure the builders are init and does it well
	if (!test_init_builders(seed))
	{
		fprintf(stderr, RED "test_builder_level: test_init_builder didn't run successfully" CRESET);
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	unsigned int builder_lvl;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_lvl = builder_level(builder);

		// Tests if the level is legal
		if (builder_lvl > BUILDER_MIN_LEVEL + NUM_LEVELS)
		{
			fprintf(stderr, RED "test_builders_levels: illegal level, builder.lvl=%d, MIN_LEVEL=%d, MAX_LEVEL=%d\n" CRESET,
					builder_lvl, BUILDER_MIN_LEVEL, BUILDER_MIN_LEVEL + NUM_LEVELS);
			return 0;
		}
	}

	return 1;
}


int test_builders_pts(int seed)
{
	// make sure the builders are init and does it well
	if (!test_init_builders(seed))
	{
		fprintf(stderr, RED "test_builder_pts: test_init_builder didn't run successfully" CRESET);
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	unsigned int builder_pts;
	unsigned int builder_lvl;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_pts = builder_points(builder);
		builder_lvl = builder_level(builder);

		// Tests if the level is legal
		if (builder_pts != 5 * (builder_lvl + 1))
		{
			fprintf(stderr, RED "test_builders_pts: illegal amount of pts, builder.pts=%d, \
					MIN_PTS=%d, MAX_PTS=%d\n" CRESET,
					builder_pts,
					BUILDER_MIN_PTS,
					BUILDER_MAX_PTS);
			return 0;
		}
	}

	return 1;
}



int test_builders_requires(int seed)
{
	// make sure the builders are init and does it well
	if (!test_init_builders(seed))
	{
		fprintf(stderr, RED "test_builder_requires: test_init_builder didn't run successfully" CRESET);
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	struct set_t builder_require;


	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_require = builder_requires(builder);

		// Tests if the requires color is legal and cost legal
		for (int index = 0; index < NUM_COLORS; ++index){
			if (builder_require.c[index] >= NUM_COLORS)
			{
				fprintf(stderr, RED "test_builders_requires: illegal require color, \
						builder.require.c=%d, MIN_COLOR=%d, MAX_COLOR=%d\n" CRESET, 
						builder_require.c[index],
						0,
						NUM_COLORS);
				return 0;
			}
			if (builder_require.c[index] > BUILDER_MAX_COST)
			{
				fprintf(stderr, RED "test_builders_requirerequiress: illegal require cost, \
				builder.require.n=%d, MIN_COST=%d, MAX_COST=%d\n" CRESET, 
				builder_require.c[index],
				BUILDER_MIN_COST,
				BUILDER_MAX_COST);
				return 0;
			}
		}
	}

	return 1;
}


int test_builders_provides(int seed)
{
	// make sure the builders are init and does it well
	if (!test_init_builders(seed))
	{
		fprintf(stderr, RED "test_builder_provide: test_init_builder didn't run successfully" CRESET);
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	struct set_t builder_provide;

	unsigned int builder_lvl;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_provide = builder_provides(builder);

		builder_lvl = builder_level(builder);
		for (int index = 0; index < NUM_COLORS; ++index)
		{
			// Tests if the level is legal
			if (builder_provide.c[index] > builder_lvl + 1)
			{
				fprintf(stderr, RED "test_builders_provides: illegal provide cost, \
						builder.provide.c[index] (%d) != builder_lvl (%d)\n" CRESET, 
						builder_provide.c[index], builder_lvl + 1);
				return 0;
			}

			// Tests if the requires color is legal
			if (builder_provide.c[index] >= NUM_COLORS)
			{
				fprintf(stderr, RED "test_builders_provides: illegal require color, \
						builder.require.c=%d, MIN_COLOR=%d, MAX_COLOR=%d\n" CRESET, 
						builder_provide.c[index],
						0,
						NUM_COLORS);
				return 0;
			}
		}

	}

	return 1;
}


