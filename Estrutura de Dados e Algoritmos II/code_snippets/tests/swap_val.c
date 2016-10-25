#include <stdio.h>

/* função que troca os valores de a e b */
void swap_val(int* a, int* b)
{
   int temp = *a;
   *a = *b;
   *b = temp;
}

int main()
{
   int a=1, b=2;

   printf("a=%d, b=%d\n", a, b);
   swap_val(&a, &b);
   printf("a=%d, b=%d\n", a, b);
   return 0;
}