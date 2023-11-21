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
void set_display(struct set_t* set, char * prefix);
void set_short_display(struct set_t* set, char * prefix);

unsigned int* set_get_colors(struct set_t* set);

struct set_t set_create(unsigned int c[NUM_COLORS]);

int set_are_equals(struct set_t* s1, struct set_t* s2);

#endif