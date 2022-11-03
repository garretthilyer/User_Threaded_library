#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

/* These four variables need to be in the global space so start and stop can access them...*/
struct itimerval NEWTIMER;  
struct itimerval OLDTIMER;

struct sigaction NEWACTION;
struct sigaction OLDACTION; 

sigset_t signalset;

/*We want our handler to force a thread to yield and swap contexts*/
void alarm_handler(int signum){
	uthread_yield();
}


void preempt_disable(void)
{
	
	/*Union of Sets*/
	sigprocmask(SIG_BLOCK, &signalset, NULL);

}

void preempt_enable(void)
{
	
	/*Intersection of Sets*/
	sigprocmask(SIG_UNBLOCK, &signalset, NULL);

}

void preempt_start(bool preempt)
{
	if (!preempt) {
		return 
	}

	/*SET UP TIMER */
	NEWTIMER.it_interval.tv.usec = 1000000 / HZ;
	NEWTIMER.it_value.tv.usec = 1000000 / HZ;

	NEWTIMER.it_interval.tv.sec = 0;
	NEWTIMER.it_value.tv.sec = 0;

	setitimer(ITIMER_VIRTUAL, &NEWTIMER, &OLDTIMER);

	sigemptyset(&signalset);
	sigaddset(&signalset, SIGVTALRM);


	/*SET UP HANDLER FOR ALARMS*/
	NEWACTION.sa_handler = alarm_handler;
	sigemptyset(&NEWACTION.sa_mask)
	NEWACTION.sa_flags = 0;

	sigaction(SIGVTALRM, &NEWACTION, &OLDACTION)

}

void preempt_stop(void)
{
	/*Restore signal and timer*/
	sigaction(SIGVTALRM, &OLDACTION, NULL);
	setitimer(ITIMER_REAL, &OLDTIMER, NULL);

}

