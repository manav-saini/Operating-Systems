#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#define SYS_schedtime 336
void time_inc() {
    for(long long i=0; i<9999999999L; ++i);
}
void t(__U64_TYPE delay) {
    pid_t pid = fork();
    if(pid < 0) {
        perror("Forking Failed");
    }
    else if((long)pid == 0) {
        pid_t p;
        clock_t t;
        p = getpid();
        printf("\nRunning without delay\n");
        t = clock();
        time_inc();
        t = clock() - t;
        printf("Time taken: %f\n", ((double)t)/CLOCKS_PER_SEC);
        printf("\nRunning with delay\n");
        t = clock();
        syscall(SYS_schedtime, pid, delay);
        time_inc();
        t = clock() - t;
        printf("Time taken: %f\n", ((double)t)/CLOCKS_PER_SEC);

        exit(0);
    }
    else {
        wait(NULL);
        printf("\nRunning without delay\n");
        clock_t t = clock();
        time_inc();
        t = clock() - t;
        printf("Time taken: %f\n", ((double)t)/CLOCKS_PER_SEC);
    }
}

int main(int argc, char *argv[]) {
    long long delay;
    printf("Enter delay value: ");
    scanf("%lld", &delay);
    t(delay);
    return 0;
}

