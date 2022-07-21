#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_kernel_2d_memcpy 335

int main(){
    int r = 5,c=5;
    int initial = 4;
    int og[5][5];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            og[i][j] = initial;
            initial++;
        }
    }
    int cp[5][5];
    int check = syscall(SYS_kernel_2d_memcpy,og,cp,r,c);
    if(check ==0){
        printf("ORIGINAL MATRIX\n");
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                printf("%d",og[i][j])
        }
    }
        printf("COPIED MATRIX\n");
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                printf("%d",cp[i][j])
            }
        }
    }
    else{
        printf("Error\n");
    }
    return 0; 
}
