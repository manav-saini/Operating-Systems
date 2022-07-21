#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include <linux/random.h>
#define SYS_writer 337
int read_line_from_file(int fd, char *buff, int buffsize) {
    memset(buff, 0,8);
    int i=0;
    while(i<buffsize-1 && read (fd, &buff[i], 1) >= 0) {
        if(buff[i] == '\n') {
            buff[i] = '\0';
            return 1;
        }
        i++;
    }
    return 0;
}
int main(){
    while(1){
        int byte_count = 8;
        char data[8];
        int fd  = open("/dev/urandom", O_RDONLY);
        read_line_from_file(fd, data, 8);
        printf("%s\n",data);
        int r = syscall(SYS_writer, data);
        sleep(2);
   }
    return 0;
}

