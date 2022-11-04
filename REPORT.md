# Introduction
------
The overall goal of this programming project was to undestand the essential building blocks of concurrency and multi-threaded programming. It built off of our previous knowledge of processes and required incorporating new concepts including locks, critical section, semaphores, resource preemption and unit-testing.
# Implementation
------
Our implementation follows the phases laid out in the project instructions very closely. Starting with *queue.c* and *queue_tester.c* and then moving onto *uthread.c* and *
### Data Structures
------
The main data structure used in this project was definitely the self implemented queue (see *queue.c* section for more details). The queue was utilized twice inside of *uthread.c* and once on the *sem.c* file. The two occurrences inside the *uthread.c* file were the *threadQueue* and *deadThread*, both of which were of type *queue_t* (queue pointer). *threadQueue* is a global queue that holds type *uthread_tcb ptr* (this data type will be talked about shortly). These structures essentially hold the different threads in the ready queue waiting to be dequeued. The other queue, *deadThread*, is also a global queue that holds all the exited threads and is constantly emptied for the dead threads to be deallocated. This thread's entire purpose is to prevent memory leaks when a thread is exiting and will never be called again. The final queue structure used in this project was in *sem.c*, it was called *waitQueue*. This queue holds the blocked threads for each specific semaphore and dequeues them when *sem_up()* is called and enqueues threads when *sem_down()* is called (obviously this is all dependent on the count of the semaphore). 

The next prominent data structure used in this project was the *uthread_tcb*. A typedef called *tcb* was implemented for a pointer to a *uthread_tcb*. The *tcb* data structure holds a pointer to the context of the thread and a pointer to the stack of a specific thread. Both of these data values are initialized in either *uthread_run()* (idle thread) or *uthread_create()*. These structures are held in the queues above in order to efficiently swap contexts and run different threads at the desire of the program. 

The final data structure implemented in this project was a *semaphore* structure. This structure held each *waitQueue* and integer *count*. The count shows the number of available resources and is incremented up and down depending on the sem call. 
### queue.c
------
We had a combination 3 main principles to create our queue. This included defining the stucts for the node and queue, allocating memory for each of these stucts when creation was necessary, and freeing this allocated memory when a node/queue was being destroyed. We also added the several error catching statements for queue to return -1 for any invalid behavior.

The queue_tester.c file contains the testing information for queue.c. We reused the TEST_ASSERT function defined from the lecture code to pass in a number of different tests of our queue implementation. Cases ranged from checking the normal use of our queue if the expected values were returned to passing in cases where the queue was used in a wrong manner, wether by inputing a NULL variable into the function itself or by NULL being generated and used in a function's runtime.
### uthread.c
------
### sem.c
------
### preempt.c
------
### Makefile
------
ADD STUFF HERE WALE
# Conclusion
------
