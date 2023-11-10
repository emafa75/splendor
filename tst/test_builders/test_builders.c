
#include "test_builders.h"
#include "builder.h"


int test_builders()
{
	int i = 0;

	if (test_init_builders())
	{
		printf("test_init_builders passed\n");
		++i;
	}


	if (test_builders_levels())
	{
		printf("test_builders_levels passed\n");
		++i;
	}



	return i;
}


int test_init_builders()
{
	init_builders(time(NULL));  // Use random seed
	
	int n = num_builders();
	struct builder_t *builder;

	// Test if enough builders have been created
	if (n < MIN_BUILDERS)
	{
		fprintf(stderr, "test_init_builders: not enough builders have been created.\n");
		return 0;
	}

	if (n > MAX_BUILDERS)
	{
		fprintf(stderr, "test_init_builders: not enough builders have been created.\n");
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


int test_builders_levels()
{
	// make sure the builders are init and does it well
	if (!test_init_builders())
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
		if (builder_lvl < 0 || builder_lvl >= NUM_LEVELS)
		{
			fprintf(stderr, "test_builders_levels: illegal level, builder.lvl=%d, MIN_LEVEL=%d, MAX_LEVEL=%d\n", builder_lvl, 0, NUM_LEVELS);
			return 0;
		}
	}

	return 1;
}


int test_builders_requires()
{
	// make sure the builders are init and does it well
	if (!test_init_builders())
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
		if (builder_lvl < 0 || builder_lvl >= NUM_LEVELS)
		{
			fprintf(stderr, "test_builders_levels: illegal level, builder.lvl=%d, MIN_LEVEL=%d, MAX_LEVEL=%d\n", builder_lvl, 0, NUM_LEVELS);
			return 0;
		}
	}

	return 1;
}














































