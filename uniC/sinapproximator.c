#include <stdio.h>
#include <math.h>

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

float sineApproximator(float f, int iterations)
{
    if(iterations > 8) {
        printf("Warning, output won't be correct, overflows will happen \n");
    }
    f *= 3.1415f / 180; // Conversion from degrees to radians
    float result = 0;
    short sign = 1;
    for (int i = 0; i < iterations; i++)
    {
        int index = 2 * i + 1;
        float num = sign * pow(f, index);
        result += num / factorial(index);
        sign *= -1;
    }
    return result;
}

int main()
{
    float angle = 0;
    int iterations = 8;
    printf("Please enter angle in degree and number of iterations, from 1 to 8: ");
    scanf("%f %d", &angle, &iterations);
    printf("Sine: %f\n", sineApproximator(angle, iterations));
}
