#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node* node_t;

struct queue {

	node_t head;
    node_t tail;
    int size;
};

struct node{
    void* data;  //  holds data a specific memory address
    node_t next;  //  points to next structure node in queue
};

queue_t queue_create(void)
{
	queue_t newQueue = (queue_t) malloc(sizeof(struct queue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->size = 0;

}

int queue_destroy(queue_t queue)
{

}

int queue_enqueue(queue_t queue, void *data)
{

	    if (queue == NULL || data == NULL) {
        return -1;
    }
    /*allocate and initialize new node */
    node_t newNode = (node_t)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->tail == NULL) {
        /* if it is the first item in queue, set head and tail to point at it */
        queue->head = newNode;
        queue->tail = newNode;

    } else {
        queue->tail->next = newNode;  // have last node point to new node
        queue->tail = newNode;  //  update last pointer (anchor) to point to last node
    }

    queue->size++;  //  increment size by +1 
    return 0;

}

int queue_dequeue(queue_t queue, void **data)
{
    
	if (queue == NULL || data == NULL) {  //  Error Catcher
        return -1;
    }

    if (queue->head == NULL) {  //  empty queue
        return -1;
    }

    *data = queue->head->data;
    node_t freeNode = queue->head;
    queue->head = queue->head->next;

    free(freeNode);
    queue->size--;

    return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

int queue_length(queue_t queue)
{
	return queue->size;
}

