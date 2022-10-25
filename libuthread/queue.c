#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {

	void* data;  //  holds data a specific memory address
    queue_t next;  //  points to next structure node in queue
};

queue_t queue_create(void)
{
	queue_t head = malloc(sizeof(struct queue));  //  dynamic allocation 
    head->next = NULL;  //  set both to NULL
    head->data = NULL;

    return head;
}

int queue_destroy(queue_t queue)
{
	 if(queue == NULL){
        return -1;
    }

    queue_t freeQueue = NULL;
    
    while(queue != NULL){
        freeQueue = queue;
        queue = queue->next;
        free(freeQueue);
    }
    freeQueue = NULL;
    return 0;
}

int queue_enqueue(queue_t queue, void *data)
{

	if (queue == NULL || data == NULL) {  //  Error catcher
		return -1;
	}

	if (queue->data == NULL) {  //  if first enqueued item

        queue->data = data;  
        return 0;

    }

    if (queue->next == NULL) {  //  if we have reached end of list 

        queue_t newNode = malloc(sizeof(queue_t));  //  dyanmic allocation 
        newNode->data = data;  //  point to data passed
        newNode->next = NULL;  //  SET NEXT TO NULL (critical for segfaults)
        queue->next = newNode;  //  set new node to null
        return 0;  //  clean exit value 

    } else {

        return queue_enqueue(queue->next, data);  //  recurse through queue
    }

	return -1;  //  should never reach this point (if it does, error)

}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
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
	/* TODO Phase 1 */
}

