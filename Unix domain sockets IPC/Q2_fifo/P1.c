#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 

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

int main(){
    srand(time(NULL));
    int n =5;
    char *arr[50],res[n];
    for(int i=0;i<50;i++){
        random_string(res,n);
        arr[i] = copyString(res);
    }
    int fd = open("fifo", O_WRONLY);
    int rand_index = rand()%30;
    printf("%d\n",rand_index);
    for(int i=rand_index;i<rand_index+5;i++){
        write(fd,arr[i],5);
        printf("%s\n",arr[i]);
    }
    int arr2[5];
    for(int i=0;i<5;i++){
        arr2[i] = rand_index;
        rand_index++;
    }
    for(int i=0;i<5;i++){
        write(fd,&arr2[i],sizeof(int));
        printf("WROTE %d\n",arr2[i]);
    }
    close(fd);
   while(rand_index+5<50){
        fd = open("fifo",O_RDONLY);
        read(fd,&rand_index,sizeof(int));
        printf("%d\n",rand_index);
        close(fd);
        fd = open("fifo",O_WRONLY);
        for(int i=rand_index+1;i<rand_index+6;i++){
            write(fd,arr[i],5);
            printf("%s\n",arr[i]);
        }
        for(int i=0;i<5;i++){
        arr2[i] = rand_index+1;
        rand_index++;
        }
        for(int i=0;i<5;i++){
        write(fd,&arr2[i],sizeof(int));
        printf("WROTE %d\n",arr2[i]);
        }
        close(fd);
    }
    return 0;
}
