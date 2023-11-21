#ifndef __SET_H__
#define __SET_H__

#include "color.h"

struct set_t {    
  unsigned int c[NUM_COLORS];
};

/*
    Display set
*/
void set_display(struct set_t);


unsigned int* set_get_colors(struct set_t);

#endif