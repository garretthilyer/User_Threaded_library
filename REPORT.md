# Introduction
------
The overall goal of this programming project was to undestand the essential building blocks of concurrency and multi-threaded programming. It built off of our previous knowledge of processes and required incorporating new concepts including locks, critical section, semaphores, resource preemption and unit-testing.
# Implementation
------
Our implementation follows the phases laid out in the project instructions very closely. Starting with *queue.c* and *queue_tester.c* and then moving onto *uthread.c* and *sem.c*. Finally, the project is wrapped up with *preempt.c* in order to replicate a real life scheduler, rather than a cooperative envirnomnent. 
### Data Structures
------
The main data structure used in this project was definitely the self implemented queue (see *queue.c* section for more details). The queue was utilized twice inside of *uthread.c* and once on the *sem.c* file. The two occurrences inside the *uthread.c* file were the *threadQueue* and *deadThread*, both of which were of type *queue_t* (queue pointer). *threadQueue* is a global queue that holds type *uthread_tcb ptr* (this data type will be talked about shortly). These structures essentially hold the different threads in the ready queue waiting to be dequeued. The other queue, *deadThread*, is also a global queue that holds all the exited threads and is constantly emptied for the dead threads to be deallocated. This thread's entire purpose is to prevent memory leaks when a thread is exiting and will never be called again. The final queue structure used in this project was in *sem.c*, it was called *waitQueue*. This queue holds the blocked threads for each specific semaphore and dequeues them when *sem_up()* is called and enqueues threads when *sem_down()* is called (obviously this is all dependent on the count of the semaphore). 

The next prominent data structure used in this project was the *uthread_tcb*. A typedef called *tcb* was implemented for a pointer to a *uthread_tcb*. The *tcb* data structure holds a pointer to the context of the thread and a pointer to the stack of a specific thread. Both of these data values are initialized in either *uthread_run()* (idle thread) or *uthread_create()*. These structures are held in the queues above in order to efficiently swap contexts and run different threads at the desire of the program. In *uthread_run()*, there is a global *tcb* structure called *currentThread*, that keeps track of the current thread running. This makes the swapping of contexts significantly easier. 

The final data structure implemented in this project was a *semaphore* structure. This structure held each *waitQueue* and integer *count*. The count shows the number of available resources and is incremented up and down depending on the sem call. 
### queue.c
------
We had a combination 3 main principles to create our queue. This included defining the stucts for the node and queue, allocating memory for each of these stucts when creation was necessary, and freeing this allocated memory when a node/queue was being destroyed. We also added the several error catching statements for queue to return -1 for any invalid behavior.

The queue_tester.c file contains the testing information for queue.c. We reused the TEST_ASSERT function defined from the lecture code to pass in a number of different tests of our queue implementation. Cases ranged from checking the normal use of our queue if the expected values were returned to passing in cases where the queue was used in a wrong manner, wether by inputing a NULL variable into the function itself or by NULL being generated and used in a function's runtime.
### uthread.c
------
The *uthread.c* consists of a multitude of functions dealt to handle and maintain an environment of multiple threads running concurrently. The first of which is *uthread_run()*. This function starts preemption if *bool preempt* is true and initializes the idle thread. It then uses *uthread_create()* to initialize another thread with the parameter *args* inside of the function parameter *uthread_func_t func*. It then enters a while loop and can only exit this while loop if *threadQueue* is ever empty. Inside of this while loop it empties and frees *tcb*’s inside of *deadThread* and calls *uthread_yield()* to swap contexts with another thread. 

The next function in the chain of commands is *uthread_create()* this function allocates space for a new *tcb* structure. This function calls both *uthread_ctx_alloc_stack()* as well as *uthread_ctx_init()* to allocate space for both the stack and context members of the *tcb*. It then enqueues this *tcb* into *threadQueue*. 

Up next is the *uthread_yield()* function. This function calls the *uthread_current()* function to get the current running thread and enqueues it into the ready queue. It then dequeues the oldest *tcb* structure and proceeds to swap contexts with the *uthread_ctx_switch()* function. 

The final prominent function inside the *uthread.c* file is *uthread_exit()*. This function checks to see if *threadQueue* is empty. In most cases, *threadQueue* is not empty and *uthread_exit()* will dequeue the oldest *tcb*, destroy the stack of the currently running tcb and enqueue the currently running *tcb* into *deadThread*. Then the *uthread_exit()* will swap contexts of the exiting thread and the dequeued thread. 

There are two other functions inside the *uthread.c* file: *uthread_block* and *uthread_unblock*. These functions will be discussed in the *sem.c* as they play more prominent roles there.
### sem.c
------
### preempt.c
------
### Makefile
------
Our makefile adopted various components from lecture and discussion including the % pattern rule convention and the -MMD flag combined with "patsubst" that checks the dependencies our files need and uses them to compile each object file accordingly. The last main feature we included was the "ar rcs" flag needed to combine our object files and create a static library. We stored this in a variable named LC and used it similar to how the CC variable is used.

# Conclusion
------
