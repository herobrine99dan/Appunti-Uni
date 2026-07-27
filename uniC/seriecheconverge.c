#include <stdio.h>
#include <math.h>

int main()
{
    double sum = 0;
    for (int i = 1; i < 15; i++)
    {
        sum += 1 / pow(2, i);
    }
    printf("Serie convergente: %.15f \n", sum);
}
