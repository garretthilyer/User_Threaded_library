#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sem.h>
#include <uthread.h>
#include <preempt.c>

int preemptCheck;

void thread2(void* arg) {

    (void)arg;
    preemptCheck = 1; 
    printf("Finishing thread 2... \n");
    return;
}

void thread1(void* arg) {
    (void)arg; 

    uthread_create(thread2, NULL);
    while(preemptCheck == 0 ){
        /* do nothing */
    }
    printf("Finishing thread 1... \n");
    return;
}

int main(void)
{
	uthread_run(true, thread1, NULL);
    printf("Finishing main function... \n");
	return 0;
}