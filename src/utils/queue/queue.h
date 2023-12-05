#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "builder.h"
#include "token.h"

#define MAX(__x, __y) \
  ((__x) > (__y) ? (__x) : (__y))

#define MAX_QUEUE_SIZE MAX(MAX_BUILDERS, NUM_TOKENS)

/*
 *  Size is the maximum number of elements the queue can store
 *  Length is the numnber of elements the queue is storing
 */
struct queue_t {
	unsigned int head;
	unsigned int size;
	unsigned int length;
	void* values[MAX_QUEUE_SIZE];
};

/*
 *  Create an empty queue
 */
struct queue_t create_default_queue();


/*
 *  Returns the index of the head of the queue
 */
unsigned int queue_get_head(struct queue_t* queue);

/*
 *  Returns the size of the queue
 */
unsigned int queue_get_size(struct queue_t* queue);


/*
 *  Returns the length of the queue
 */
unsigned int queue_get_length(struct queue_t* queue);


/*
 *  Returns the first element of the queue and removes it from the queue
 */
void* queue_dequeue(struct queue_t* queue);


/*
 *  Returns 1 if successfully adds value to the queue
 *		0 otherwise
 */
unsigned int queue_append(struct queue_t* queue, void* value);


/*
 *  Returns 1 if the queue is empty
 *		0 otherwise
 */
unsigned int queue_is_empty(struct queue_t* queue);
#endif
