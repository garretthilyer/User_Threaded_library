#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"
#include "uthread.h"

struct semaphore {
	int count;
	queue_t waitQueue; 
	
};

sem_t sem_create(size_t count)
{
	sem_t newSem = (sem_t)malloc(sizeof(struct semaphore));
	newSem->count = count;
	newSem->waitQueue = queue_create();
	return newSem;

}

int sem_destroy(sem_t sem)
{
	if ( (sem == NULL) || (sem->count == 0) ) {  //  if sem is NULL or if threads are still being blocked
		return -1;
	}

	queue_destroy(sem->waitQueue);
	free(sem);
	return 0; 

}

int sem_down(sem_t sem)
{
	if (sem == NULL) {
		return -1;
	}

	if (sem->count == 0) {

		struct uthread_tcb* blockedThread = uthread_current();
		queue_enqueue(sem->waitQueue, blockedThread);
		uthread_block();

	} else {
		sem->count--;
	}
	
	return 0; 
}

int sem_up(sem_t sem)
{
	if (sem == NULL) {
		return -1; 
	}

	if (sem->count == 0) {
		sem->count++;

		if (queue_length(sem->waitQueue) > 0) {

			struct uthread_tcb* waitingThread;
			queue_dequeue(sem->waitQueue, (void**)&waitingThread);
			uthread_unblock(waitingThread);

		}
	}
	
	return 0; 
}

