#include <stdio.h>

int fib(int n)
{
    printf("fib(%d) is called\n", n);
    if(n==0) return 0;
    if(n==1) return 1;
    return(fib(n-1) + fib(n-2));
}
int main(void)
{
    fib(6);
    return 0;
}