## Introduction
------
The overall goal of this programming project was to undestand the essential building blocks of concurrency and multi-threaded programming. It built off of our previous knowledge of processes and required incorporating new concepts including locks, critical section, semaphores, resource preemption and unit-testing.

## Implementation
------
Our implementation follows the phases laid out in the project instructions very closely. Starting with *queue.c* and *queue_tester.c* and then moving onto *uthread.c* and *

#### Data Structures
------

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

## Conclusion
------



