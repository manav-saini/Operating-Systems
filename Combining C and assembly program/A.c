#include<stdio.h>
extern void B(long long a,void (*p));
void C();

void A(){
    long long num;
    printf("Function A\n");
    scanf("%lld",&num);
    B(num,C);
}

int main(){
    A();
    return 0;
}
