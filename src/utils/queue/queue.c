
#include "queue.h"

#include <stdlib.h>
#include <string.h>

/*
 *  Create an empty queue
 */
struct queue_t create_default_queue()
{
	struct queue_t out = {};
	out.size = MAX_QUEUE_SIZE;
	return out;
}


/*
 *  Returns the index of the head of the queue
 */
unsigned int queue_get_head(struct queue_t* queue)
{
	return queue->head;
}


/*
 *  Returns the index of the head of the queue
 */
unsigned int queue_get_size(struct queue_t* queue)
{
	return queue->size;
}


/*
 *  Returns the index of the head of the queue
 */
unsigned int queue_get_length(struct queue_t* queue)
{
	return queue->length;
}


void* queue_dequeue(struct queue_t* queue)
{
	void* out = queue->values[queue->head];
	queue->head = (queue->head + 1) % queue_get_size(queue);
	++queue->length;
	return out;
}


/*
 *  Returns 1 if successfully adds value to the queue
 *		0 otherwise
 */
unsigned int queue_append(struct queue_t* queue, void* value)
{
	if (queue_get_length(queue) >= queue_get_size(queue))
		return 0;

	++queue->length;
	int ind = (queue_get_head(queue) + queue_get_length(queue)) % queue_get_size(queue);

	queue->values[ind] = value;
	return 1;
}


/*
 *  Returns 1 if the queue is empty
 *		0 otherwise
 */
unsigned int queue_is_empty(struct queue_t* queue)
{
	return queue_get_length(queue) == 0;
}


