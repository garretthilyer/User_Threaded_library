#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <uthread.h>
#include <preempt.c>


void thread3(void* arg) { /* Terminates entire proccess*/
    (void)arg;
    printf("In Thread THREE\n");
    printf("Terminate Threads \n"); 
    raise(SIGKILL);
}

void thread2(void* arg) { /*Creates a Third Thread */
    (void)arg;

    preempt_disable();
    uthread_create(thread3, NULL);
    printf("In Thread TWO\n");
    preempt_enable(); 

    while (true) { /*Infinite while loop*/
        printf("In Thread TWO While Loop\n");
    }
    
}

void thread1(void* arg) { /*Creates a Second Thread */
    (void)arg;

    preempt_disable(); 
    uthread_create(thread2, NULL);
    printf("In Thread ONE\n");
    preempt_enable();

    while (true) { /*Infinte while loop*/
        printf("In Thread ONE While Loop\n");
    }
    
}

int main(void)
{
	uthread_run(true, thread1, NULL);
	return 0;
}