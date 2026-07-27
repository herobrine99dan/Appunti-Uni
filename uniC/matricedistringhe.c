#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *stringa;
} String;

void replaceChar(char *arr, char toReplace)
{
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == toReplace)
        {
            arr[i] = '*';
        }
    }
}

void printStringWithMostOccurencies(String *arr, int rows, int columns, char w)
{
    String stringObj = arr[0];
    int lastCount = 0;
    int lastIndex = 0;
    for (int i = 0; i < rows * columns; i++)
    {
        String string = arr[i];
        int counter = 0;
        for (int j = 0; string.stringa[j] != '\0'; j++)
        {
            if (string.stringa[j] == w)
            {
                counter++;
            }
        }
        if (counter > lastCount)
        {
            lastCount = counter;
            stringObj = string;
            lastIndex = i;
        }
    }
    replaceChar(stringObj.stringa, w);
    if(lastCount == 0) {
        printf("Nessuna stringa ha quel carattere \n");
        return;
    }
    printf("Stringa con %d occorrenze di '%c' trovata agli indici %d, %d: %s \n", lastCount, w, lastIndex / rows + 1, lastIndex % columns + 1, stringObj.stringa);
}

void printMatrix(int rows, int columns, String *arr)
{
    for (int i = 0; i < rows * columns; i++)
    {
        String stringObj = arr[i];
        printf("%s ", stringObj.stringa);
        if (i % columns == columns - 1)
        {
            printf("\n");
        }
        // printf("%d \n",i % columns);
    }
}

char *randomString(int size)
{
    size++; // vogliamo prevenire overflow, dobbiamo mettere il carattere null terminator
    char *string = (char *)calloc(size, sizeof(char));
    for (int i = 0; i < size; i++)
    {
        string[i] = (char)(rand() % (122 - 97 + 1) + 97); // 97-122
    }
    string[size - 1] = '\0'; // WARNING!!! Forgetting the null terminator makes printf read everything
    return string;
}

void sort(int rows, int columns, String *array)
{
    // TODO  ordini ogni colonna della matrice S in modo crescente (ordinamento lessicografico), usa strcmp
    for (int col = 0; col < columns; col++) // Itero per ogni colonna
    {
        printf("column %d \n", col);
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = 0; j < rows - i - 1; j++)
            {
                // y * rows + x
                // 0-2
                // 0-3-6
                // 0-4-8-12
                int indexFirstString = (j)*rows + col;          // j
                int indexSecondString = ((j + 1)) * rows + col; // j+1
                // printf("indexFirst: %d indexSecond: %d \n", indexFirstString, indexSecondString);

                if (strcmp(array[indexFirstString].stringa, array[indexSecondString].stringa) > 0)
                {
                    String temp = array[indexFirstString];
                    array[indexFirstString] = array[indexSecondString];
                    array[indexSecondString] = temp;
                }
            }
        }
    }
}

int main()
{
    int rows, columns, stringSize;
    printf("Scrivi numero di righe, colonne, dimensione stringa nel formato m,n,q \n");
    scanf(" %d,%d,%d", &rows, &columns, &stringSize);
    printf("Ora scrivi il carattere w \n");
    char charact;
    scanf(" %c", &charact);
    int nElements = rows * columns;
    String *mat = (String *)calloc(nElements, sizeof(String));
    for (int i = 0; i < nElements; i++)
    {
        mat[i].stringa = randomString(stringSize);
    }
    printMatrix(rows, columns, mat);
    sort(rows, columns, mat);
    printf("Now ordering \n");
    printMatrix(rows, columns, mat);
    printStringWithMostOccurencies(mat, rows, columns, charact);
    for (int i = 0; i < nElements; i++)
    {
        free(mat[i].stringa);
        mat[i].stringa = NULL;
    }
    free(mat);
}