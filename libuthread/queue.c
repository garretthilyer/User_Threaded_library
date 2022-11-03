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
	queue_t newQueue = (queue_t) malloc(sizeof(struct queue));  //  Allocate space for queue
    newQueue->head = NULL;  //  set head and tail to NULL
    newQueue->tail = NULL; 
    newQueue->size = 0;  //  set size to 0
    return newQueue; 

}

int queue_destroy(queue_t queue)
{
    if (queue == NULL || queue->size != 0) {  //  if queue is null OR queue is not empty

        return -1;

    } else {  //  else free the queue and deallocate memory
        
        free(queue); 
        return 0;

    }

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

    if(queue->size == 0) {  //  dequeuing empty array
        return -1;
    }


    if (queue->head == NULL ) {  //  empty queue
        return -1;

    }

    *data = queue->head->data;  //  set return address 
    node_t freeNode = queue->head;
    queue->head = queue->head->next;
    free(freeNode);  //  free node 
    queue->size--;

    if ((queue->head == queue->tail) && (queue->size == 0)) {  //  reset head and tail to null if the last item was dequeued from list 
        queue->head = NULL;
        queue->tail = NULL;
    }

    if(queue->head == NULL) {
        queue->tail = NULL;
    }

    return 0;
}

int queue_delete(queue_t queue, void *data)
{
    if (queue == NULL || data == NULL){  //  Error catcher
        return -1;
    }

    node_t currentNode = queue->head;
    if (queue->head->data == data) {  //  first item in queue
        queue->head = queue->head->next;
        free(currentNode);
        queue->size--;

        if ((queue->head == queue->tail) && (queue->size == 0)) {  //  reset head and tail to null if the last item was deleted from list
            queue->head = NULL;
            queue->tail = NULL;
        }
        return 0;
    }
    node_t previousNode = queue->head;
    currentNode = currentNode->next;

    while (currentNode != NULL) {

        if (currentNode->data == data) {

            previousNode->next = currentNode->next;

            if (previousNode->next == NULL) {  //  current node WAS the tail, update previous with current
                queue->tail = previousNode;
            }

            queue->size--;
            free(currentNode);
            return 0;

        } else {

            currentNode = currentNode->next;
            previousNode = previousNode->next;

        }

    }

    return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
    if (queue == NULL || func == NULL){  //  Error catcher
        return -1;
    }

    node_t iteratedNode = queue->head;
    
    while (iteratedNode != NULL) {

        void* passedData = iteratedNode->data;
        iteratedNode = iteratedNode->next;
        func(queue, passedData);

    }

    return 0;
}

int queue_length(queue_t queue)
{
    if(queue == NULL) {
        return -1; 
    }

	return queue->size;
}

