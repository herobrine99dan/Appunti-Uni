#include <stdio.h>
#include <stdlib.h>

/*Generare 20 numeri random, inserirli in un array,
determinare la prima serie di elementi uguali più lunga e metterla tra parentesi*/

void fillArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 6 + 1;
    }
}

void printSequence(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void searchBiggestSequence(int *array, int size, int *indiceInizioSequenza, int *indiceFineSequenza, int *dimensioneSequenzaMax)
{
    for (int i = 0; i < size; i++)
    {
        int mainElement = array[i];
        int dimensioneSequenza = 0;
        int j = i;
        for (; j < size; j++)
        {
            if (array[j] != mainElement)
            {
                break;
            }
            dimensioneSequenza++;
        }
        if (dimensioneSequenza > *dimensioneSequenzaMax)
        {
            *indiceInizioSequenza = i;
            *indiceFineSequenza = j;
            *dimensioneSequenzaMax = dimensioneSequenza;
        }
        printf("Dopo l'elemento %d, ci sono %d elementi uguali. \n", mainElement, dimensioneSequenza - 1);
    }
}

int main()
{
    srand(1);
    int size;
    printf("Quanti numeri nella sequenza? \n");
    scanf("%d", &size);
    int *array = calloc(size, sizeof(int));
    fillArray(array, size);
    // int array[20] = {1, 2, 3, 4, 5,9,9,1,2,3,4,4,4,2,3,4,1,1,1,1};
    printSequence(array, size);

    int indiceInizioSequenza = 0;
    int indiceFineSequenza = 0;
    int dimensioneSequenzaMax = 0;
    searchBiggestSequence(array, size, &indiceInizioSequenza, &indiceFineSequenza, &dimensioneSequenzaMax);

    //  for (int i = indiceInizioSequenza; i < indiceFineSequenza; i++)
    for (int i = 0; i < size; i++)
    {
        if (i == indiceInizioSequenza)
        {
            printf("(");
        }

        printf("%d", array[i]);
        // printf(i == indiceFineSequenza ? "" : " ");
        if (i != indiceFineSequenza - 1)
        {
            printf(" ");
        }
        if (i == indiceFineSequenza - 1)
        {
            printf(") ");
        }
    }
    printf("\n");
    free(array);
    array = NULL;
}