#include <stdio.h>

int operazione(int a, int b, int (*op)(int, int))
{
    return op(a, b);
}

int somma(int a, int b)
{
    return a + b;
}

int moltiplica(int a, int b)
{
    return a * b;
}

int main()
{
    int (*sommaPuntatore)(int, int) = &somma;
    int risultato = sommaPuntatore(3, 4);
    printf("Test1: %d\n ", risultato);
    int r1 = operazione(2, 3, somma);      // 5
    int r2 = operazione(2, 3, moltiplica); // 6
    printf("r1: %d\n ", r1);
    printf("r2: %d\n ", r2);
}