#ifndef __SET_H__
#define __SET_H__

#include "color.h"


struct set_t {	
	unsigned int c[NUM_COLORS];
	unsigned int num_colors;
};


/*
 * Returns the union of 2 sets (makes the sum of values)
 *
 * Example: set_union({0, 1}, {1, 1}) -> {1, 2}
 */
struct set_t set_union(const struct set_t* set1, const struct set_t* set2);


/*
 *  Returns a set full of 0s
 */
struct set_t set_zero(void);


/*
 *  Returns the intersection of set1 and set2
 *
 */
struct set_t set_inter(const struct set_t* set1, const struct set_t* set2);


/*
	Display set
*/
void set_display(const struct set_t* set);
/*
  Short way to display set
*/
void set_short_display(const struct set_t* set, const char * prefix);


/*
  Get color associated to the set
*/
unsigned int* set_get_colors(struct set_t* set);


/*
  Create an empty set
*/
struct set_t set_create(unsigned int c[NUM_COLORS]);


/*
 *	Returns the number of non-zero elements of set
 */
unsigned int set_get_num_els(struct set_t set);


/*
  Compare the two sets and return 0 if different, 1 if equals
*/
int set_are_equals(const struct set_t* s1, const struct set_t* s2);


/*
	create simple set 
*/
struct set_t create_simple_set(enum color_t c);


/*
	Create complex set 
*/
struct set_t create_complex_set(unsigned int c[NUM_COLORS]);


/*
	Create a random set with max color and min color
*/
struct set_t create_random_set(int num_colors);


/*
	Returns the number of ressources of the set
*/
int set_num_ressources(struct set_t* set);
#endif
