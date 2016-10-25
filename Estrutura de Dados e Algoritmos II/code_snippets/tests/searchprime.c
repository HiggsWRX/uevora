#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long is_prime(unsigned long n)
{
    unsigned long i;
    if (n < 2) {return 0;}
    if (n == 2 || n == 3) {return 1;}
    if (n % 2 == 0 || n % 3 == 0) {return 0;}
    unsigned long sqrtN = sqrt(n) + 1;
    for (i = 6; i < sqrtN; i += 6) {
        if (n % (i - 1) == 0 || n % (i + 1) == 0) {return 0;}
    }
    return 1;
}

unsigned long proc_primo_ant(unsigned long n)
{
    int found = 0;
    while (!found) {
        if (is_prime(n)) {
            found = 1;
        } else {
            n--;
        }
    }
    return n;
}

int main()
{
    unsigned long num;
    scanf("%lu", &num);
    printf("Is %lu prime? %s\n", num, is_prime(num) ? "true" : "false");
    printf("Previous prime of %lu is %lu\n", num, proc_primo_ant(num));
    return 0;
}