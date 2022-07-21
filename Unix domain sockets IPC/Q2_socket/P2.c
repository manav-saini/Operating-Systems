    #include <errno.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/un.h>
       #include <unistd.h>
       #include "connection.h"
       #include <time.h>

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
       int main(int argc, char *argv[])
       {
           struct sockaddr_un addr;
           int ret;
           int data_socket;
           char buffer[BUFFER_SIZE];

           srand(time(NULL));
            int n =5;
            char *arr[50],res[n];
            for(int i=0;i<50;i++){
            random_string(res,n);
            arr[i] = copyString(res);
            }
            int rand_index = rand()%30;
           data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
           if (data_socket == -1) {
               perror("socket");
               exit(EXIT_FAILURE);
           }
           memset(&addr, 0, sizeof(addr));
           addr.sun_family = AF_UNIX;
           strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
           ret = connect(data_socket, (const struct sockaddr *) &addr,
                          sizeof(addr));
           if (ret == -1) {
               fprintf(stderr, "The server is down.\n");
               exit(EXIT_FAILURE);
           }
            for (int i = rand_index; i <=rand_index+5;i++) {
               ret = write(data_socket, arr[i], strlen(arr[i]) + 1);
               if (ret == -1) {
                   perror("write");
                   break;
               }
           }

           strcpy(buffer, "END");
           ret = write(data_socket, buffer, strlen(buffer) + 1);
           if (ret == -1) {
               perror("write");
               exit(EXIT_FAILURE);
           }
            int arr2[5];
            for(int i=0;i<5;i++){
                arr2[i] = rand_index;
                rand_index++;
            }

            for (int i = 0; i <5;i++) {
               ret = write(data_socket, &arr2[i], sizeof(int));
               printf("%d\n",arr2[i]);
               if (ret == -1) {
                   perror("write");
                   break;
               }
           }
           while(rand_index+5<50){
               read(data_socket,&rand_index,sizeof(int));
               printf("%d\n",rand_index);
               for(int i=rand_index+1;i<rand_index+6;i++){
                   write(data_socket,arr[i],5);
                   printf("%s\n",arr[i]);
               }
               for(int i=0;i<5;i++){
                   arr2[i] = rand_index+1;
                   rand_index++;
               }
               for(int i=0;i<5;i++){
                   write(data_socket,&arr2[i],sizeof(int));
                   printf("WROTE %d\n",arr2[i]);
               }
           }
           close(data_socket);
           exit(EXIT_SUCCESS);
}


//Help taken from manpage
