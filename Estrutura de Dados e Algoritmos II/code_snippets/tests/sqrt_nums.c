#include <stdio.h>
#include <math.h>

int main(void)
{
    int counter;

    for (counter = 1; counter <= 2000; counter++)
    {
        double current_sqrt = sqrt(counter);
        printf("Current number: %d | Current sqrt: %.2f\n", counter, current_sqrt);
    }
    return 0;
}