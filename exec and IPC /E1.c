#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>
pid_t pid;
int rand_generator (uint32_t *rand)
{
	unsigned char c;
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (c));
	return (int) c;
}

void siglarm_handler(int signum){
    uint32_t rand;
    rand_generator (&rand);
    union sigval value;
    value.sival_int = rand;
    sigqueue(pid,SIGTERM,value);
}
int main(int argc, char *argv[]){
    struct itimerval timer;
    signal(SIGALRM,siglarm_handler);
    pid = atoi(argv[1]);
    union sigval value;
    value.sival_int = 1;
    sigqueue(pid,SIGTERM,value);
    pause();
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 700000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 700000;
    setitimer (ITIMER_REAL, &timer, NULL);
    while (1);
}
