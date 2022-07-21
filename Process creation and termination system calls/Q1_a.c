#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
float A[6]={0,0,0,0,0,0};
float B[6]={0,0,0,0,0,0};
int secA=0,secB=0;
struct stud {
    unsigned int id;
    char sect;
    int marks[6];
};

void out(char *str) {
    int len = strlen(str);
    syscall(1, STDOUT_FILENO, str, len);
}

void id(struct stud *student, char *point){
    student->id = atoi(point);
}

void inc_secA(){
    secA++;
}

void inc_secB(){
    secB++;
}

void extractData(char *str){
    struct stud new;
    details(str, &new);
    if(new.sect == 'B')
        printStudent(&new);
}

int details(char *str, struct stud *s) {
    char *pch;
    pch = strtok(str, ",");

    if(pch == NULL)
        return -1;
    
    s->id = atoi(pch);
    pch = strtok(NULL, ",");

    if(pch == NULL)
        return -1;

    s->sect = pch[0];
    if(pch[0]=='A'){
        inc_secA();
    }
    if(pch[0]=='B'){
        inc_secB();
    }

    int ii=0;
    while(ii<5) {
        pch = strtok(NULL, ",");
        if(pch == NULL)
            return -1;
        s->marks[ii] = atoi(pch);
        ii++;
    }
    s->marks[5] = atoi(pch+strlen(pch)+1);
    return 0;
}
void p_integer(int input) {
    char string[20];
    sprintf(string, "%d", input);
    out(string);
}
void printStudent(struct stud *student) {
    p_integer(student->id);
    out("\t");
    char sec[2];
    sec[0] = student->sect;
    sec[1] = '\0';
    out(sec);
    out("\t");
    float avg = 0;
    int count=0;
    for(int i=0; i<6; ++i) {
        p_integer(student->marks[i]);
        if(i==count && strcmp(&sec[0],"A")==0){
            A[i]+=(float)student->marks[count];
            count++;
        }
        if(i==count && strcmp(&sec[0],"B")==0){
            B[i]+=(float)student->marks[count];
            count++;
        }
        out("\t");
    }

    out("\n");
}

int line(int f, char *buff, int buffsize) {
    memset(buff, 0, 100);
    int i=0;
    while(errno != EINTR && i<buffsize-1 && read (f, &buff[i], 1) >= 0) {
        if(buff[i] == '\n') {
            buff[i] = '\0';
            return 1;
        }
        i++;
        errno = 0;
    }
    return 0;
}

void throwError(int i){
    if(i==0){
        out("Error");
        exit(1);
    }else if(i==1){
        printf("ERROR");
        exit(0);
    }
}

int main() {
    pid_t p;
    p = fork();
    if(p < 0) {
        throwError(0);
    }
    else if(p == 0) {
        int f  = open("student_record.csv", O_RDONLY);
        if(f == -1) {
            throwError(1);
        }

        char str[100];

        line(f, str, 100);
        
        while(line(f, str, 100) > 0) {
            struct stud new;
            details(str, &new);
            if(new.sect == 'A')
                printStudent(&new);
        }
        for(int i=0;i<6;i++){
            printf("\n");
            printf("Average of assignment %d =%f\n",i+1,A[i]/secA);
        }
        close(f);
        exit(0);
    }
    else {
        waitpid(-1, NULL, 0);
        printf("Child Finished!\n");

        int f  = open("student_record.csv", O_RDONLY);
        if(f == -1) {
            printf("ERROR\n");
            return;
        }

        char str[100];

        line(f, str, 100);
        
        while(line(f, str, 100) > 0) {
            extractData(str);
        }
        
        for(int i=0;i<6;i++){
            printf("\n");
            printf("Average of assignment %d =%f\n",i+1,B[i]/secB);
        }
        close(f);
    }
    return 0;
}



