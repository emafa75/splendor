#include "queue.h"

#include <stdio.h>


/*
 *  Create an empty queue
 */
struct queue_t create_default_queue()
{
	struct queue_t out = {};

	out.size = MAX_QUEUE_SIZE;
	out.length = 0 ;

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
	if (queue_get_length(queue) == 0)
		return NULL;

	unsigned int head = queue_get_head(queue);

	void* out = queue->values[head];  // Value to return
	
	queue->head = (head + 1) % queue_get_size(queue);
	--queue->length;

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

	// May need loop in the queue if head != 0 -> get the modulo
	int append_ind = (queue_get_head(queue) + queue_get_length(queue)) % queue_get_size(queue);
	queue->values[append_ind] = value;
	
	++queue->length;
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
