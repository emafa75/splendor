#include "set.h"
#include "color_second_header.h"
#include "ansi_color.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>


struct set_t SET_ZEROS = {};


unsigned int* set_get_colors(struct set_t* set)
{
	return set->c;
}


struct set_t set_zero(void)
{
	return SET_ZEROS;
}


struct set_t set_union(const struct set_t *set1, const struct set_t *set2)
{
	struct set_t out = {};

	for (int i = 0 ; i < NUM_COLORS ; ++i)
	{
		out.c[i] = set1->c[i] + set2->c[i];
		out.num_colors += (set1->c[i] || set2->c[i]);
	}

	return out;
}


struct set_t set_inter(const struct set_t* set1, const struct set_t* set2)
{
	struct set_t out = {};
	unsigned int cmp;

	for (int i = 0 ; i < NUM_COLORS ; ++i)
	{
		cmp = (set1->c[i] && set2->c[i]);
		out.c[i] = MIN(set1->c[i], set2->c[i]) * cmp;
		out.num_colors += cmp;
	}

	return out;
}



struct set_t set_create(unsigned int c[NUM_COLORS])
{
	struct set_t s = {};

	for (unsigned int index = 0 ; index < NUM_COLORS ; ++index)
	{
		s.c[index] = c[index];
				if (c[index])
					s.num_colors++;
	}

	return s;
}


int set_are_equals(const struct set_t* s1, const struct set_t* s2)
{
	for(int index = 0 ; index < NUM_COLORS ; ++index)
	{
		if (s1->c[index] != s2->c[index])
		{
			return 0;
		}
	}
	return 1;
}


unsigned int set_get_num_els(struct set_t set)
{
	return set.num_colors;
}


void set_display(const struct set_t* set)
{
	for (enum color_t i = 0 ; i < NUM_COLORS ; ++i)
	{
		// Only print colors with non-zero occurences
		if (set->c[i] != 0)
		{
			printf("%s%s%s=%d (Q:%d),", color_prefix(i), color_to_short_string(i), CRESET, i, set->c[i]);	  
		}
	}
}


void set_short_display(const struct set_t* set, const char * prefix)
{
	printf("%s(", prefix);

	for (enum color_t i = 0 ; i < NUM_COLORS ; ++i)
	{
		if(set->c[i] != 0)
		{	
			printf("%s%s=%d%s", color_prefix(i), color_to_short_string(i), set->c[i], CRESET);
		}
	}

	printf(")");
}


struct set_t create_simple_set(enum color_t c)
{
	struct set_t set = {};

	set.c[c] = 1;
	set.num_colors = 1;

	return set;
}


struct set_t create_complex_set(unsigned int c[NUM_COLORS])
{
	struct set_t set = {};

	for (int index = 0 ; index < NUM_COLORS ; ++index)
	{
		if(c[index])
		{
			set.c[index] = c[index];
			++set.num_colors;
		}
	}

	return set;
}


struct set_t create_random_set(int num_colors)
{
	struct set_t set_for_complex_token = {};

	for (int index = 0 ; index < num_colors ; ++index)
	{
		/*
			Choose a random color and add it to the set
		*/
		enum color_t rand_color = rand() % NUM_COLORS;
		++set_for_complex_token.c[rand_color];
		set_for_complex_token.num_colors += (set_for_complex_token.c[rand_color] == 1);	
	}

	return set_for_complex_token;
}


int set_num_ressources(struct set_t* set)
{
	int num_ressources = 0;

	for (int index = 0; index < NUM_COLORS; ++index)
	{
		num_ressources += set->c[index];
	}

	return num_ressources;
}
