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
	if ( (sem == NULL) || (queue_length(sem->waitQueue) != 0) ) {  //  if sem is NULL or if threads are still being blocked
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

	

	while (sem->count == 0) {

		preempt_disable();

		struct uthread_tcb* blockedThread = uthread_current();
		queue_enqueue(sem->waitQueue, blockedThread);
		
		preempt_enable();
		uthread_block();

	} 
		
	sem->count--;

	preempt_enable(); 
	
	return 0; 
}

int sem_up(sem_t sem)
{
	if (sem == NULL) {
		return -1; 
	}

	sem->count++;

	preempt_disable();

	if (queue_length(sem->waitQueue) > 0 ) {
		struct uthread_tcb* unblockedThread;
		queue_dequeue(sem->waitQueue, (void**)&unblockedThread);
		uthread_unblock(unblockedThread);

	}

	preempt_enable();
	
	return 0; 
}

