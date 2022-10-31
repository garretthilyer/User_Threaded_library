#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

typedef struct uthread_tcb* tcb;

queue_t threadQueue;

struct uthread_tcb {

	uthread_ctx_t *context;
	void* stackTop;

};

struct uthread_tcb *uthread_current(void)
{
	tcb currentThread = (tcb)malloc(sizeof(struct uthread_tcb));
	currentThread->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));

	getcontext(currentThread->context);
	currentThread->stackTop = currentThread->context->uc_stack.ss_sp;

	return currentThread;
}

void uthread_yield(void)
{
	if(queue_length(threadQueue) == 0) {
		return; 
	}
	
	tcb yieldThread = uthread_current();
	queue_enqueue(threadQueue, yieldThread);

	tcb newThread; 
	queue_dequeue(threadQueue, (void**)&newThread);

	swapcontext(yieldThread->context, newThread->context);

}

void uthread_exit(void)
{
	tcb deleteThread = uthread_current();
	free(deleteThread->context);
	uthread_ctx_destroy_stack(deleteThread->stackTop);
	free(deleteThread);

	if (queue_length(threadQueue) > 0) {
		
		tcb newThread;
		queue_dequeue(threadQueue, (void**)&newThread);
		setcontext(newThread->context);

	} else {
		return; 
	}

}

int uthread_create(uthread_func_t func, void *arg)
{
	
	tcb createThread = (tcb)malloc(sizeof(struct uthread_tcb));  //  allocate space for thread ptr
	createThread->stackTop = uthread_ctx_alloc_stack();
	createThread->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));

	if ( createThread->stackTop == NULL ){
		return -1;
	}

	if ( uthread_ctx_init(createThread->context, createThread->stackTop, func, arg) ){
		return -1;
	}

	queue_enqueue(threadQueue, createThread);

	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	if (preempt) {  //  if preempt is TRUE, enable preemptive scheduling 
		//preempt_enable();
	} 

	tcb idleThread = (tcb)malloc(sizeof(struct uthread_tcb));  //  allocate space for thread ptr
	idleThread->stackTop = uthread_ctx_alloc_stack();
	idleThread->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));

	if ( idleThread->stackTop == NULL ){
		return -1;
	}

	if ( uthread_ctx_init(idleThread->context, idleThread->stackTop, func, arg) ){
		return -1;
	}

	threadQueue = queue_create();
	uthread_create(func, arg);

	while (queue_length(threadQueue) > 0) {
		uthread_yield();
	}

	queue_destroy(threadQueue);
	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 3 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	uthread->context = NULL;
}

