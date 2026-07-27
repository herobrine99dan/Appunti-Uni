#include <stdio.h>

int factorial(int n);
int fibonacciIter(int n);

int main()
{
    // Fibonacci and factorial
    for (int i = 0; i < 15; i++)
    {
        printf("Fattoriale: %d \n", factorial(i));
    }
    printf("------------------- \n");
    for (int i = 0; i < 20; i++)
    {
        printf("Fibonacci: %d \n", fibonacciIter(i));
    }
}

int fibonacciIter(int n)
{
    // 0,1,1,2,3,5,8,13,21,34,55...
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    float fibo = 0;
    float lastFibo = 1;
    float lastLastFibo = 0;
    for (int i = 1; i < n; i++)
    {
        fibo = lastFibo + lastLastFibo;
        lastLastFibo = lastFibo;
        lastFibo = fibo;
    }
    return fibo;
}

int factorial(int n)
{
    float total = 1;
    for (int i = n; i > 0; i--)
    {
        total *= i;
    }
    return total;
}