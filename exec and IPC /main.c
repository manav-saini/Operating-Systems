#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
pid_t sr;
pid_t st;
int count=0;

void converter(char buf[], long epoc){
    time_t now = (time_t)epoc;
    struct tm  ts;
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %y-%m-%d %H:%M:%S %Z", &ts);
    printf("%s\n", buf);
    return 0;
}
void sig_handler(int signum ,siginfo_t * info, void * nothing){
    if(count==0){
        sr = info->si_pid;
        count++;
    }
    else if(count==1){
        st = info->si_pid;
        count++;
    }
    // if(info->si_pid < sr) {
    //     sr = info->si_pid;
    // }

    // else{
    //     st = info->si_pid;
    // }
    if( info->si_pid == sr){
        printf("Random number = %d\n",info->si_value.sival_int);
    }
    else if( info->si_pid == st){
        char buf[80];
        converter(buf,info->si_value.sival_int);
        printf("Time = %d\n",info->si_value.sival_int);
    }
}

int main(){
    pid_t pid = fork();
    if(pid == 0){
        struct sigaction sig_struc;
        sig_struc.sa_flags = SA_SIGINFO; 
        sig_struc.sa_sigaction = sig_handler;
        sigaction(SIGTERM,&sig_struc,NULL);
    }
    else if(pid==-1){
        printf("ERROR\n");
    }
    else{
        pid_t pid_sr = fork();
        char A[32];
        sprintf(A,"%d",pid);
        if(pid_sr==0){
            char *args[] = {"./E1",A,NULL};
            execv(args[0],args);
        }
        else if(pid_sr==-1){
            printf("ERROR\n");
        }
        else{
            pid_t pid_st = fork();
            char B[32];
            sprintf(B,"%d",pid_sr);
            if(pid_st == 0){
                char *args[] = {"./E2",A,B,NULL};
                execv(args[0],args);
            }
            else if(pid_st==-1){
                printf("ERROR\n");
            }
        }  
    }
    while(1);
}
