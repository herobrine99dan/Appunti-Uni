#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int getMax(int * arr, int size);

int* fillRandom( int arr[], int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    return arr;
}

int main()
{
    int a = 5;
    int *ptr = NULL;
    ptr = &a;

    printf("Valore variabile %d \n", a);
    printf("Indirizzo variabile %p \n", (void *)&a);
    printf("Indirizzo variabile (memorizzato nel puntatore) %p \n", (void *)ptr);
    printf("Valore dal puntatore %d \n", *ptr);
    printf("Indirizzo puntatore %p \n", (void *)&ptr);
    printf("Eseguire errore? s\\n \n");
    char c = (char)getchar();
    if (c == 's')
    {
        printf("Indirizzo puntatore %d \n", *++ptr);
        return 0;
    }


    int arr[5] = {1, 2, 5, 4, 3};
    int somma = 0;
    //&arr mi dà un puntatore che punta a tutto l'array in generale
    //&arr[0] mi dà il puntatore che punta alla prima cella, anche il semplce arr funziona
    int *pointer = &arr[0];
    for (int i = 0; i < 5; i++)
    {
        somma += *pointer;
        pointer++;
    }
    printf("Somma: %d \n", somma);

    
    int p = 5;
    int q = 3;
    swap(&p, &q);
    printf("a: %d, b: %d \n", p, q);
    printf("max %d\n", getMax(arr, 5));
    fillRandom(arr, 5);
    for(int i = 0; i < 5; i++) {
        printf("rand: %d   %d \n", i, arr[i]);
    }
}

int getMax(int *a, int size)
{
    int *ptr = a;
    int maximum = *ptr;
    for (int i = 0; i < size; i++)
    {
        if ((*ptr) > maximum)
        {
            maximum = *ptr;
        }
        ptr++;
    }
    return maximum;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}