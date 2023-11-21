#ifndef __SET_H__
#define __SET_H__

#include <stdio.h>

#include "color.h"


struct set_t {    
  unsigned int c[NUM_COLORS];
};

/*
    Display set
*/
void set_display(const struct set_t* set);
/*
  Short way to display set
*/
void set_short_display(struct set_t* set, char * prefix);

/*
  Get color associated to the set
*/
unsigned int* set_get_colors(struct set_t* set);

/*
  Create an empty set
*/
struct set_t set_create(unsigned int c[NUM_COLORS]);

/*
  Compare the two sets and return 0 if different, 1 if equals
*/
int set_are_equals(const struct set_t* s1, const struct set_t* s2);

#endif