#include <stdio.h>

int main(void)
{
    int a, *p;

    a = 1;
    p = &a;
    *p = 2;

    printf("Valor de a: %d\n", a);
    return 0;
}