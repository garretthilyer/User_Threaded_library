#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	int count;
	queue_t waitQueue; 
	
};

sem_t sem_create(size_t count)
{
	sem_t newSem = (sem_t)malloc(sizeof(semaphore));
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
	
}

int sem_up(sem_t sem)
{
	
}

