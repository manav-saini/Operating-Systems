       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/un.h>
       #include <unistd.h>
       #include "connection.h"

       int
       main(int argc, char *argv[])
       {
           struct sockaddr_un name;
           int down_flag = 0;
           int ret;
           int connection_socket;
           int data_socket;
           int result;
           char buffer[BUFFER_SIZE];
           connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
           if (connection_socket == -1) {
               perror("socket");
               exit(EXIT_FAILURE);
           }
           memset(&name, 0, sizeof(name));
           name.sun_family = AF_UNIX;
           strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

           ret = bind(connection_socket, (const struct sockaddr *) &name,
                      sizeof(name));
           if (ret == -1) {
               perror("bind");
               exit(EXIT_FAILURE);
           }
           ret = listen(connection_socket, 20);
           if (ret == -1) {
               perror("listen");
               exit(EXIT_FAILURE);
           }
           for (;;) {
               data_socket = accept(connection_socket, NULL, NULL);
               if (data_socket == -1) {
                   perror("accept");
                   exit(EXIT_FAILURE);
               }
               result = 0;
               for (;;) {
                   ret = read(data_socket, buffer, sizeof(buffer));
                   if (ret == -1) {
                       perror("read");
                       exit(EXIT_FAILURE);
                   }
                   buffer[sizeof(buffer) - 1] = 0;
                   if (!strncmp(buffer, "DOWN", sizeof(buffer))) {
                       down_flag = 1;
                       break;
                   }

                   if (!strncmp(buffer, "END", sizeof(buffer))) {
                       break;
                   }
                   printf("%s\n",buffer);
               }
               int arr2[5];
               for(int i=0;i<5;i++){
                read(data_socket,&arr2[i],sizeof(int));
                printf("Read %d\n",arr2[i]);
                }
                ret = write(data_socket,&arr2[4], sizeof(int));
                while(arr2[4]+5<50){
                    for(int i=0;i<5;i++){
                    ret = read(data_socket, buffer, sizeof(buffer));
                    buffer[sizeof(buffer) - 1] = 0;
                    printf("%s\n",buffer);
                    }
                    for(int i=0;i<5;i++){
                        read(data_socket,&arr2[i],sizeof(int));
                        printf("Read %d\n",arr2[i]);
                    }
                    write(data_socket,&arr2[4],sizeof(int));
                }
               if (ret == -1) {
                   perror("write");
                   exit(EXIT_FAILURE);
               }
               close(data_socket);
               if (down_flag) {
                   break;
               }
           }
           
           close(connection_socket);
           unlink(SOCKET_NAME);
           exit(EXIT_SUCCESS);
       }


//Help taken from manpage
