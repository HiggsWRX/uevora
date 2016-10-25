/* Temperature Converter */
#include <stdio.h>

float convert(int);

int main(void)
{
    int temperature;
    printf("Enter the temperature in Fahrenheit to convert to Celcius.\n");
    scanf("%d",&temperature);
    printf("%d Fahrenheit is %.1f Celcius\n", temperature, convert(temperature));
    return (0);
}

float convert(int t)
{
    float new_temp = (t-32) * (5 / 9.0);
    return new_temp;
}