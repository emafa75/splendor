
#include "test_builders.h"



int test_builders()
{
	int i = 0;  // number of passed tests
	int seed = time(NULL);  // Use random seed

	if (test_init_builders(seed))
	{
		printf("test_init_builders passed\n");
		++i;
	}


	if (test_builders_levels(seed))
	{
		printf("test_builders_levels passed\n");
		++i;
	}


	if (test_builders_pts(seed))
	{
		printf("test_builders_pts passed\n");
		++i;
	}


	if (test_builders_requires(seed))
	{
		printf("test_builders_requires passed\n");
		++i;
	}


	if (test_builders_provides(seed))
	{
		printf("test_builders_provides passed\n");
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
		fprintf(stderr, "test_init_builders: not enough builders have been created.\n");
		return 0;
	}

	if (n > MAX_BUILDERS)
	{
		fprintf(stderr, "test_init_builders: too many builders have been created.\n");
		return 0;
	}


	// Tests if all builders are actually builders
	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		if (builder == NULL)
		{
			fprintf(stderr, "test_init_builders: init_builders() don't create the right amount of builders\n");
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
		fprintf(stderr, "test_builder_level: test_init_builder didn't run successfully");
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	int builder_lvl;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_lvl = builder_level(builder);

		// Tests if the level is legal
		if (builder_lvl < BUILDER_MIN_LEVEL || builder_lvl >= NUM_LEVELS)
		{
			fprintf(stderr, "test_builders_levels: illegal level, builder.lvl=%d, MIN_LEVEL=%d, MAX_LEVEL=%d\n", builder_lvl, 0, NUM_LEVELS);
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
		fprintf(stderr, "test_builder_pts: test_init_builder didn't run successfully");
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	int builder_pts;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_pts = builder_points(builder);

		// Tests if the level is legal
		if (builder_pts < BUILDER_MIN_PTS || builder_pts >= BUILDER_MAX_PTS)
		{
			fprintf(stderr, "test_builders_pts: illegal level, builder.lvl=%d, \
					MIN_LEVEL=%d, MAX_LEVEL=%d\n",
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
		fprintf(stderr, "test_builder_requires: test_init_builder didn't run successfully");
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	struct buildcost_t builder_require;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_require = builder_requires(builder);

		// Tests if the requires cost is legal
		if (builder_require.n < BUILDER_MIN_COST || builder_require.n >= BUILDER_MAX_COST)
		{
			fprintf(stderr, "test_builders_requirerequiress: illegal require cost, \
					builder.require.n=%d, MIN_COST=%d, MAX_COST=%d\n", 
					builder_require.n,
					BUILDER_MIN_COST,
					BUILDER_MAX_COST);
			return 0;
		}

		// Tests if the requires color is legal
		if (builder_require.c < 0 || builder_require.c >= NUM_COLORS)
		{
			fprintf(stderr, "test_builders_requires: illegal require color, \
					builder.require.c=%d, MIN_COLOR=%d, MAX_COLOR=%d\n", 
					builder_require.c,
					0,
					NUM_COLORS);
			return 0;
		}
	}

	return 1;
}


int test_builders_provides(int seed)
{
	// make sure the builders are init and does it well
	if (!test_init_builders(seed))
	{
		fprintf(stderr, "test_builder_provide: test_init_builder didn't run successfully");
		return 0;
	}

	int n = num_builders();
	struct builder_t *builder;
	struct buildcost_t builder_provide;

	for (int i = 0 ; i < n ; ++i)
	{
		builder = make_builder(i);
		builder_provide = builder_provides(builder);

		// Tests if the level is legal
		if (builder_provide.n < BUILDER_MIN_COST || builder_provide.n >= BUILDER_MAX_COST)
		{
			fprintf(stderr, "test_builders_provides: illegal provide cost, \
					builder.provide.n=%d, MIN_COST=%d, MAX_COST=%d\n", 
					builder_provide.n,
					BUILDER_MIN_COST,
					BUILDER_MAX_COST);
			return 0;
		}

		// Tests if the requires color is legal
		if (builder_provide.c < 0 || builder_provide.c >= NUM_COLORS)
		{
			fprintf(stderr, "test_builders_provides: illegal require color, \
					builder.require.c=%d, MIN_COLOR=%d, MAX_COLOR=%d\n", 
					builder_provide.c,
					0,
					NUM_COLORS);
			return 0;
		}

	}

	return 1;
}


