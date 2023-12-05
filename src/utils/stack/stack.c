
#include "stack.h"
#include <stdlib.h>
#include <string.h>


/*
 *
 */
struct stack_t create_default_stack()
{
	struct stack_t out = {};
	return out;
}



unsigned int stack_get_head(struct stack_t * stack)
{
	return stack->head;
}



void * stack_pop(struct stack_t * stack)
{
	if (stack->head < 0)
		return NULL;

	void *out = stack->values[stack->head];
	stack->head--;
	return out;
}



unsigned int stack_append(struct stack_t *stack, void *value)
{
	if (stack == NULL)
	{
		return 0;
	}

	if (stack->head < MAX_STACK_SIZE - 1)
	{
		stack->head++;
		stack->values[stack->head] = value;

		return 1;
	}

	return 0;
}



unsigned int stack_is_empty(struct stack_t *stack)
{
	return stack->head == 0;
}



unsigned int stack_get_values(struct stack_t *stack, void *values, unsigned int size)
{
	memcpy(values, stack->values, size);
	return stack->head;
}
