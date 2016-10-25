#include <stdio.h>

int main() {
    float number;
    while (1) {
        scanf("%f", &number);
        printf("%f\n", ((number-50)/50));
    }
}