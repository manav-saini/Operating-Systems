#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

int read_line_from_file(int fd, char *buff, int buffsize) {
    memset(buff, 0, 5);
    int i=0;
    while(i<buffsize && read (fd, &buff[i], 1) >= 0) {
        if(buff[i] == '\n') {
            buff[i] = '\0';
            return 1;
        }
        i++;
    }
    return 0;
}
int main(){
    int fd = open("fifo",O_RDONLY);
    char str[5];
    for(int i=0;i<5;i++){
        read_line_from_file(fd, str,5);
        printf("%s\n",&str);
    }
    int arr2[5];
    for(int i=0;i<5;i++){
        read(fd,&arr2[i],sizeof(int));
        printf("Read %d\n",arr2[i]);
    }
    close(fd);
    fd = open("fifo",O_WRONLY);
    write(fd,&arr2[4],sizeof(int));
    close(fd);

    while(arr2[4]+5<50){
        fd = open("fifo",O_RDONLY);
        for(int i=0;i<5;i++){
        read_line_from_file(fd, str,5);
        printf("%s\n",&str);
    }
        for(int i=0;i<5;i++){
        read(fd,&arr2[i],sizeof(int));
        printf("Read %d\n",arr2[i]);
    }
        close(fd);
        fd = open("fifo",O_WRONLY);
        write(fd,&arr2[4],sizeof(int));
        close(fd);
    }
    return 0;
}