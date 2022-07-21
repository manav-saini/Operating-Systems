#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

void random_string(char *res,int n){
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    for(int i=0;i<5;i++){
        res[i] = alphabet[(int) (rand() % 26)];
    }
}

char* copyString(char s[])
{
    char* s2;
    s2 = (char*)malloc(20);
 
    strcpy(s2, s);
    return (char*)s2;
}

int main()
{
	key_t key;
	int msgid;
    srand(time(NULL));
    int n =5;
    char *arr[50],res[n];
    for(int i=0;i<50;i++){
        random_string(res,n);
        arr[i] = copyString(res);
    }
    int rand_index = rand()%30;
	key = ftok("progfile", 65);
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;

    for(int i=rand_index;i<rand_index+5;i++){
        strcpy(message.mesg_text,arr[i]);

        printf("%s\n",message.mesg_text);
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    int arr2[5];
    for(int i=0;i<5;i++){
        arr2[i] = rand_index;
        rand_index++;
    }
    for(int i=0;i<5;i++){
        sprintf(message.mesg_text,"%d",arr2[i]);
        printf("%s\n",message.mesg_text);
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    while(rand_index+5<50){
        msgrcv(msgid, &message, sizeof(message), 2, 0);
        rand_index = atoi(message.mesg_text);
        for(int i=rand_index+1;i<rand_index+6;i++){
            message.mesg_type = 1;
            strcpy(message.mesg_text,arr[i]);
            printf("%s\n",message.mesg_text);
            msgsnd(msgid, &message, sizeof(message), 0);
        }
        for(int i=0;i<5;i++){
            arr2[i] = rand_index+1;
            rand_index++;
        }
        for(int i=0;i<5;i++){
            message.mesg_type = 1;
            sprintf(message.mesg_text,"%d",arr2[i]);
            printf("%s\n",message.mesg_text);
            msgsnd(msgid, &message, sizeof(message), 0);
        }
    }
	return 0;
}








//Help taken from geeks for geeks

