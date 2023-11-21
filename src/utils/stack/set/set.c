#include "set.h"

#include "color_second_header.h"

unsigned int* set_get_colors(struct set_t* set)
{
    return set->c;
}

struct set_t set_create(unsigned int c[NUM_COLORS])
{
    struct set_t s = {};
    for (unsigned int index = 0; index < NUM_COLORS ; ++index)
    {
        s.c[index] = c[index];
    }
    return s;
}

int set_are_equals(struct set_t* s1, struct set_t* s2)
{
    for(int index = 0 ; index < NUM_COLORS; ++index)
    {
        if (s1->c[index] != s2->c[index])
        {
            return 0;
        }
    }
    return 1;
}

void set_display(struct set_t *set, char *prefix)
{
    printf("%s(", prefix);
	for (enum color_t i = 0 ; i < NUM_COLORS ; ++i)
	{
		if (set->c[i] != 0)
		{
			printf("%s%s%s=%d (Q:%d)," ,color_prefix(i), color_to_short_string(i),CRESET, i, set->c[i]);	  
		}
	}
  printf(")");
}

void set_short_display(struct set_t* set, char * prefix)
{
    printf("%s(", prefix);
	for (enum color_t i = 0; i < NUM_COLORS; ++i)
	{
		if(set->c[i] != 0)
		{	
			printf("%s%s=%d%s", color_prefix(i), color_to_short_string(i), set->c[i], CRESET);
		}
	}
	printf(")");
}