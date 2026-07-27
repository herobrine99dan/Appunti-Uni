#include <stdio.h>
#include <math.h>

int isPrimeNumber(int x) //algoritmo brute force, non usa la conoscenza dei vecchi numeri primi
{
    for (int i = 2; i < x; i++)
    {//TODO Forse c'è un'ottimizzazione testando fino a sqrt(n) numeri? Vedere slide
        if (x % i == 0 && i != x)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int max = 16;
    printf("Inserire quanti numeri primi bisogna computare: ");
    scanf("%d", &max);
    int numeriPrimiTrovati = 0;
    int i = 2;
    while(numeriPrimiTrovati < max) {
        if (isPrimeNumber(i) == 1)
        {
            printf("%d ", i);
            numeriPrimiTrovati++;
        }
        i++;

    }
    printf("\n");
}