#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <sys/time.h>
pid_t pid;
long int f;
long int bt;
unsigned long long rdtscl()
{
    unsigned int lo, hi;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));                        
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );  
}
int read_line_from_file(int fd, char *buff, int buffsize) {
    memset(buff, 0, 100);
    int i=0;
    while(i<buffsize-1 && read (fd, &buff[i], 1) >= 0 && errno != EINTR) {
        if(buff[i] == '\n') {
            buff[i] = '\0';
            return 1;
        }
        i++;
        errno = 0;
    }
    return 0;
}

long frequency(){
	int fd  = open("/proc/cpuinfo", O_RDONLY);
    int f;
	int count=0;
        if(fd == -1) {
            fprintf(stderr, "Error opening file!\n");
            exit(0);
        }
        char str[100];
        read_line_from_file(fd, str, 100);
	char freq;
        while(read_line_from_file(fd, str, 100) > 0){
            char *pch;
            pch = strtok(str,":");
	        char c[] = "cpu MHz		";
            // pch = strtok(NULL,":");
            // printf("%s\n",pch);
            int value=strcmp(pch,c);
	        if(value==0){
                pch = strtok(NULL,":");
                f = atoi(pch);
                break;
		    }    
	}

    return (long)f*1000000;
}

long btime(){
	int fd  = open("/proc/stat", O_RDONLY);
    long int btime;
	int count=0;
        if(fd == -1) {
            fprintf(stderr, "Error opening file!\n");
            exit(0);
        }
        char str[100];
        read_line_from_file(fd, str, 100);
	char freq;
        while(1){
            read_line_from_file(fd, str, 100);
            char *pch;
            pch = strtok(str," ");
	        char c[] = "btime";
            int value=strcmp(pch,c);
	        if(value==0){
                pch = strtok(NULL,":");
                btime = atoi(pch);
                break;
		    }    
	}
    return btime;
}

void siglarm_handler(int signum){
    unsigned long long time = rdtscl()/f;
    long int epoc = btime+time; 
    union sigval value;
    value.sival_int = epoc;
    sigqueue(pid,SIGTERM,value);  
}
int main(int argc, char *argv[]){
    sleep(2);
    f = frequency();
    bt = btime();
    struct itimerval timer;
    signal(SIGALRM,siglarm_handler);
    pid = atoi(argv[1]);
    pid_t pid_sr = atoi(argv[2]);
    union sigval value;
    value.sival_int = 2;
    sigqueue(pid,SIGTERM,value);
    kill(pid_sr,SIGALRM);
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 700000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 700000;
    setitimer (ITIMER_REAL, &timer, NULL);
    while (1);
}
