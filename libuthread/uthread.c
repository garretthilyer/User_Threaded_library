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


typedef struct uthread_tcb* tcb;  //  Less Typing 

queue_t threadQueue;  //  global ready queue 
tcb currentThread;  //  ptr to current tcb 

struct uthread_tcb {

	uthread_ctx_t *context;  //  needs pointer to context 
	void* stackTop;  //  needs pointer stack 

};

struct uthread_tcb *uthread_current(void)
{
	return currentThread;  //  just return global tcb to current running tcb 
}

void uthread_yield(void)
{
	if(queue_length(threadQueue) == 0) {
		return; 
	}
	
	preempt_disable();  // entering critical section 

	tcb yieldThread = uthread_current();  //  get thread to yield 
	if (queue_enqueue(threadQueue, yieldThread)) {  //  add it to ready queue 
		return;
	}
	tcb newThread;  

	if (queue_dequeue(threadQueue, (void**)&newThread)) {  // get next thread to run 
		return;
	}
	currentThread = newThread;  //  set global tcb to next thread to run 

	preempt_enable();  //  leaving critical section 

	uthread_ctx_switch(yieldThread->context, newThread->context);  //  swap context

}

void uthread_exit(void)
{

	if (queue_length(threadQueue) > 0) {
		preempt_disable();  //  entering critical section 

		tcb deleteThread = uthread_current();  //  get exiting thread 
		uthread_ctx_destroy_stack(deleteThread->stackTop);  // free stack 
		tcb newThread;

		if (queue_dequeue(threadQueue, (void**)&newThread)) {  //  get next thread to run 
			return;
		}
		currentThread = newThread;

		preempt_enable();  //  leaving critical section 

		uthread_ctx_switch(deleteThread->context, newThread->context);  //  swap contexts
			
	} else {

		preempt_disable(); //  entering critical section 
		tcb deleteThread = uthread_current();  //  free everything 
		free(deleteThread->context);
		uthread_ctx_destroy_stack(deleteThread->stackTop);
		free(deleteThread);

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

	preempt_disable();  //  entering critical section 

	if ( uthread_ctx_init(createThread->context, createThread->stackTop, func, arg) ){  //  create context 
		return -1;
	}

	if ( queue_enqueue(threadQueue, createThread) ) {  //  enqueue tcb to thread queue
		return -1;
	}

	preempt_enable();  //  leaving critical section 

	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	preempt_start(preempt);  // start preemption if true 

	/* Intialize idle thread */
	threadQueue = queue_create();
	tcb idle = (tcb)malloc(sizeof(struct uthread_tcb));
	idle->stackTop = uthread_ctx_alloc_stack();
	idle->context = (uthread_ctx_t*)malloc(sizeof(uthread_ctx_t));

	getcontext(idle->context);
	currentThread = idle;
	uthread_create(func, arg);

	/*While ready queue is not empty keep yielding */
	while (queue_length(threadQueue) != 0) {
		uthread_yield();
	}

	/* Destroy everything */
	if (queue_destroy(threadQueue) ){
		return -1;
	}

	/* End Preemption */
	if (preempt) {
		preempt_stop();
	}

	return 0;
}

void uthread_block(void)
{
	preempt_disable();  //  entering critical section 

	tcb nextThread;
	tcb blockedThread = uthread_current();
	if ( queue_dequeue(threadQueue, (void**)&nextThread) ) {
		return;
	}
	currentThread = nextThread;

	preempt_enable();  //  leaving critical section 

	uthread_ctx_switch(blockedThread->context, nextThread->context);

}

void uthread_unblock(struct uthread_tcb *uthread)
{

	queue_enqueue(threadQueue, uthread);  // enqueue unblocked 
	
}

