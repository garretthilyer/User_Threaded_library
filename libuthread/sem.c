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
	/* Create new semaphore and initialize count and blocked queue inside */
	sem_t newSem = (sem_t)malloc(sizeof(struct semaphore));
	newSem->count = count;
	newSem->waitQueue = queue_create();
	return newSem;

}

int sem_destroy(sem_t sem)
{
	if ( (sem == NULL) || (queue_length(sem->waitQueue) != 0) ) {  //  if sem is NULL or if threads are still being blocked
		return -1;
	}
	/* Destory Queue, then Free the semaphore */
	queue_destroy(sem->waitQueue);
	free(sem);
	return 0; 

}

int sem_down(sem_t sem)
{
	if (sem == NULL) {
		return -1;
	}

	
	while (sem->count == 0) {  //  Catches the corner case corretly with a while loop since it always rechecks condition 

		preempt_disable();  //  entering critical section 

		struct uthread_tcb* blockedThread = uthread_current();
		queue_enqueue(sem->waitQueue, blockedThread);  //  enqueue the blocked thread in this semaphores waiting list 

		preempt_enable();

		uthread_block();  //  leaving critical section 

	} 
		
	sem->count--;

	
	return 0; 
}

int sem_up(sem_t sem)
{
	if (sem == NULL) {
		return -1; 
	}

	preempt_disable();  //  enters critical section 
	
	sem->count++;

	if (queue_length(sem->waitQueue) > 0 ) {

		struct uthread_tcb* unblockedThread;
		queue_dequeue(sem->waitQueue, (void**)&unblockedThread);  //  dequeue oldest thread in waiting list 
		uthread_unblock(unblockedThread);  //  send it to unblock for it to be enqueued 

	}

	preempt_enable();  //  leaves critical section 
	
	return 0; 
}

