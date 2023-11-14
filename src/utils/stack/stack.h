#ifndef __STACK_H__
#define __STACK_H__

#include "builder.h"
#include "token.h"
#define MAX(__x, __y) \
  ((__x) > (__y) ? (__x) : (__y))

struct stack_t {
	int head;
	void *values[MAX(MAX_BUILDERS, NUM_TOKENS)];
};

/*
 *
 */
struct stack_t stack_create();



unsigned int stack_get_head(struct stack_t * stack);



void * stack_pop(struct stack_t * stack);



void stack_append(struct stack_t *stack, void *value);



unsigned int is_empty(struct stack_t *stack);



#endif
