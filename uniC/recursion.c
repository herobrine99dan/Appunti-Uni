#include <stdio.h>
int factorial(int n);
int fibonacci(int n);
int main()
{
    // Fibonacci and factorial
    for (int i = 0; i < 10; i++)
    {
        printf("Fattoriale: %d \n", factorial(i));
    }
    printf("------------------- \n");
    for (int i = 0; i < 10; i++)
    {
        printf("Fibonacci: %d \n", fibonacci(i));
    }
}

int fibonacci(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n)
{
    if (n <= 1) // Changed from n == 1
    {
        return 1;
    }
    return n * factorial(n - 1);
}