## Introduction
The overall goal of this programming project was to strengthen the understanding of system calls such as fork(), exec(), wait() and other basic UNIX system calls. This was achieved by building a very low-functioning shell called *sshell*. This shell could receive up to 3 command line arguments from the user that were pipelined togther and execute the correct output. 

The overall goal of this programming project was to undestand the essential building blocks of concurrency and multi-threaded programming. It built off of our previous knowledge of processes and required incorporating new concepts including locks, critical section, semaphores, resource preemption and unit-testing.

## Implementation 


### Data Structures
NOT TOO SURE IF THIS ECTION IS NEEDED


### Queue


### Sem


### Preempt


### Testers
The queue_tester.c file contains the testing information for queue.c. We reused the TEST_ASSERT function defined from the lecture code to pass in a number of different tests of our queue implementation. Cases ranged from checking the normal use of our queue if the expected values were returned to passing in cases where the queue was used in a wrong manner, wether by inputing a NULL variable into the function itself or by NULL being generated and used in a function's runtime.

SEM TESTER STUFF

## Conclusion

