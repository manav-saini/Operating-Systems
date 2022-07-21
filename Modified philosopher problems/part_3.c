#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define n 5
sem_t fork[n], sauce_bowl;
pthread_t philosopher[n];
void *eat(void *args) {
    int i = *((int *)args);
    while(1) {
        sem_wait(&fork[i]);
        if(sem_trywait(&fork[(i+1) % n]) < 0) {
            sem_post(&fork[i]);
            continue;
        }
        if(sem_trywait(&sauce_bowl) < 0) {
            sem_post(&fork[i]);
            sem_post(&fork[(i+1) % n]);
            continue;
        }
        printf("Philosopher %d eats using forks %d and %d\n", i, i, (i+1)%n);
        sem_post(&fork[i]);
        sem_post(&fork[(i+1) % n]);
        sem_post(&sauce_bowl);
    }
    pthread_exit(NULL);
}

int main(void) {
    int *count = (int *) malloc(n * sizeof(int));
    for(int i=0; i<n; ++i){
        sem_init(&fork[i], 0, 1);
    }
    sem_init(&sauce_bowl,0, 4);
    for(int i=0; i<n; ++i) {
        *(count + i) = i;
        pthread_create(&philosopher[i], NULL, eat, (count+i));
    }
    for(int i=0; i<n; ++i)
        pthread_join(philosopher[i], NULL);
    for(int i=0; i<n; ++i)
        sem_destroy(&fork[i]);
    free(count);
    printf("NO DEADLOCKS\n");
    return 0;
}

