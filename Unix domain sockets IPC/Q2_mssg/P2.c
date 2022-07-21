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

int main()
{
	key_t key;
	int msgid;
	key = ftok("progfile", 65);
	msgid = msgget(key, 0666 | IPC_CREAT);
    for(int i=0;i<5;i++){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Data Received is : %s\n",
					message.mesg_text);

    }
    int arr2[5];
    for(int i=0;i<5;i++){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Index : %s\n",
					message.mesg_text);
        arr2[i]=atoi(message.mesg_text);

    }
    message.mesg_type = 2;
    sprintf(message.mesg_text,"%d",arr2[4]);
    msgsnd(msgid, &message, sizeof(message), 0);
    while(arr2[4]+5<50){
        for(int i=0;i<5;i++){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Data Received is : %s \n",message.mesg_text);
        }
        for(int i=0;i<5;i++){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Data Received is : %s \n",
					message.mesg_text);
        arr2[i]=atoi(message.mesg_text);
        }
        message.mesg_type = 2;
        sprintf(message.mesg_text,"%d",arr2[4]);
        msgsnd(msgid, &message, sizeof(message), 0);
    
    }
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}


//Help taken from geeks for geeks
