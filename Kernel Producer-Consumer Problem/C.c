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
#define SYS_reader 338
int main(){
   while(1){
        char d[8];
        int r = syscall(SYS_reader, d);
        printf("%s\n",d);
        sleep(2);
  }
    return 0;
}

