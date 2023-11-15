#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include "builder.h"
#include "token.h"
#include <string.h>

#define MAX(__x, __y) \
  ((__x) > (__y) ? (__x) : (__y))

#define MAX_STACK_SIZE MAX(MAX_BUILDERS, NUM_TOKENS)

struct stack_t {
	int head;
	void *values[MAX_STACK_SIZE];
};

/*
 *
 */
struct stack_t stack_create();


/*
 *
 */
unsigned int stack_get_head(struct stack_t * stack);


/*
 *
 */
void * stack_pop(struct stack_t * stack);


/*
 *  Returns 1 if successfully adds value to the stack
 *					0 otherwise
 */
unsigned int stack_append(struct stack_t *stack, void *value);


/*
 *
 */
unsigned int stack_is_empty(struct stack_t *stack);


/*
 *  Returns the size of values void *values[] 
 */
unsigned int stack_get_values(struct stack_t *stack, void *values, unsigned int values_size);

#endif
