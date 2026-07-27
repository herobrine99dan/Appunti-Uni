#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct params
{
    int n, m;
    char *filename;
} params;

/*
- insertionSort: funzione che permette di ordinare l’array Y mediante insertion sort;
- getCumulative: funzione che prende in input la l’array Y e restituisce l’array Z, come definito
nel testo;*/

int cumulative(int *arr, int i)
{
    int sum = 0;
    for (int j = 0; j <= i; j++)
    {
        sum += arr[j];
    }
    return sum;
}

int *getCumulative(int *arr, int size)
{
    int* zArr = calloc(size, sizeof(int));
    // Crei un nuovo array Z a partire da Y, tale che 𝑍[𝑖] = ∑ 𝑌[𝑖] !"#$ e lo stampi a schermo
    for(int i = 0; i < size; i++) {
        zArr[i] = cumulative(arr, i);
    }
    return zArr;
}

void insertionSort(int *arr, int size)
{
    for (int step = 0; step < size; step++)
    {
        for (int j = step; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            // Swap arr[j] and arr[j-1]
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

int countElements(double *mat, int row, int n, int m)
{
    double min = 1000000;
    double max = 0;
    double q = 0;
    for (int col = 0; col < m; col++)
    {
        // x + rows*y; y + rows*x
        int index = col + n * row;
        q += mat[index];
        if (mat[index] < min)
        {
            min = mat[index];
        }
        if (mat[index] > max)
        {
            max = mat[index];
        }
    }
    q /= m;
    double a = q - (max - min) * 0.3;
    double b = q + (max - min) * 0.3;
    int counter = 0;
    for (int col = 0; col < m; col++)
    {
        // x + rows*y; y + rows*x
        int index = col + n * row;
        if (mat[index] >= a && mat[index] <= b)
        {
            counter++;
        }
    }
    return counter;
}

int *getArray(double *mat, int n, int m)
{
    /*. Definisca un array Y di n interi e inserisca in Y[i] il numero di elementi nella riga i-esima di
    X che hanno un valore compreso tra a e b (esclusi), dove a=q – (max-min)*0.3 e b=q+(maxmin)*0.3, e q, min, e max sono rispettivamente il valore medio, minimo e massimo della riga
    i-esima di X. (L’operazione va effettuata per ciascun valore di i)
    Si stampi a schermo l’array Y.*/
    int *arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = countElements(mat, i, n, m);
    }
    return arr;
}

double *readFile(char *fileName, int n, int m)
{
    /*Si assuma che il file di testo contenuto al percorso indicato da filename contenga n righe,
    ciascuna contenente m double separati da virgole. Il programma legga il contenuto del file e
    lo inserisca all’interno di un matrice X di double di dimensione 𝑛 × 𝑚. */

    double *mat = calloc(n * m, sizeof(double));
    FILE *filePtr = fopen(fileName, "r");
    char buf[1024];
    int indexMat = 0;
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        char *cloned = calloc(strlen(buf) + 1, sizeof(char));
        strcpy(cloned, buf);
        char *tok = strtok(cloned, ",");
        mat[indexMat++] = atof(tok);
        for (int i = 0; i < n - 1; i++)
        {
            tok = strtok(NULL, ",");
            mat[indexMat++] = atof(tok);
        }
        free(cloned);
    }
    fclose(filePtr);
    return mat;
}

params decodeParameters(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Numero di argomenti non valido \n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    char *filename = argv[3];
    if (n < 3 || n > 7)
    {
        fprintf(stderr, "Number out of range \n");
        exit(1);
    }
    if (m < 3 || m > 7)
    {
        fprintf(stderr, "Number out of range \n");
        exit(1);
    }
    char *s = strstr(filename, ".txt");
    if (s == NULL)
    {
        fprintf(stderr, "Extension not valid \n");
        exit(1);
    }
    char *cloned = calloc(strlen(filename) + 1, sizeof(char));
    strcpy(cloned, filename);
    params pam = {n, m, cloned};
    return pam;
}

int main(int argc, char *argv[])
{
    params pam = decodeParameters(argc, argv);
    printf("======Stampa Parametri======\n n = %d\n m = %d\nfilename = %s\n", pam.n, pam.m, pam.filename);
    double *mat = readFile(pam.filename, pam.n, pam.m);
    printf("======Stampa X======");
    for (int i = 0; i < pam.m * pam.n; i++)
    {
        if (i % pam.m == 0)
        {
            printf("\n");
        }
        printf("%.2f ", (float)mat[i]);
    }
    printf("\n");

    int *arr = getArray(mat, pam.n, pam.m);
    printf("======Stampa Y====== \n");
    for (int i = 0; i < pam.n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("======Stampa Y ordinato====== \n");
    insertionSort(arr, pam.n);
    for (int i = 0; i < pam.n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("======Stampa Z====== \n");
    int *zArr = getCumulative(arr, pam.n);
    for (int i = 0; i < pam.n; i++)
    {
        printf("%d ", zArr[i]);
    }
    printf("\n");
    free(zArr);
    free(arr);
    free(mat);
    free(pam.filename);
}