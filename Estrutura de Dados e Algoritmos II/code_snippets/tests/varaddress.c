#include <stdio.h>

int main(void)
{
    int v[100];
    printf("v  is %p\n", &v);
    printf("v0 is %p\n", &v[0]);
    printf("v1 is %p\n", &v[1]);
    printf("Size of v is %d\n",sizeof(v));
    return 0;
}