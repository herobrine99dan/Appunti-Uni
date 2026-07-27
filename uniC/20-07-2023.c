#include <stdio.h>
#include <stdlib.h>

typedef struct Record
{
    int n;
    int m;
} Record;

Record decodeParameters()
{
    int n = 5;
    int m = 7;
    if (n > 7 || n < 3 || m > 7 || m < 3)
    {
        fprintf(stderr, "Errore miao miao \n");
        exit(-1);
    }
    Record record = {n, m};
    return record;
}

unsigned int get_random()
{
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

int **getRandomMatrix(int n, int m, int h)
{
    int **arr = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        arr[i] = calloc(m, sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = get_random() % h + 1;
        }
    }
    return arr;
}

void removeMax(int **arr, int n, int m, int j)
{
    /*
    removeMax: funzione che prende in input la matrice A, la dimensione n e un indice di
colonna col, e rimuove il massimo valore nella colonna col come indicato nel punto C;*/
    int lastVal = 0;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][j] > lastVal)
        {
            lastVal = arr[i][j];
            index = i;
        }
    }
    arr[index][j] = 0;
    free(arr[index][j]);
}

void printMatrix(int **arr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 0)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", arr[i][j]);
            }
        }
        printf("\n");
    }
}

void modifyMatrix(int n, int m, int **mat)
{
    for (int j = 0; j < m; j++)
    {
        for (int q = 0; q < 3; q++)
        {
            removeMax(mat, n, m, j);
        }
    }
}

int rowMinNull(int **arr, int n, int m)
{
    int mostNulls = 0;
    int mostNullsRow = 0;
    for (int i = 0; i < n; i++)
    {
        int counter = 0;
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 0)
            {
                counter++;
                if (counter > mostNulls)
                {
                    mostNulls = counter;
                    mostNullsRow = i;
                }
            }
        }
        //printf("i null nella riga %d sono %d \n", i, counter);
    }
    return mostNullsRow;
}

int main()
{
    Record record = decodeParameters();
    printf("Punto A - Parametri inseriti: n=%d, m=%d \n", record.n, record.m);
    int h;
    scanf("%d", &h);
    if (h < 10 || h > 100)
    {
        fprintf(stderr, "Errore miao miao \n");
        exit(-1);
    }
    int **mat = getRandomMatrix(record.n, record.m, h);
    printf("Punto B: matrice randomica generata \n");
    printMatrix(mat, record.n, record.m);

    printf("Punto C: matrice con i tre elementi più grandi marcati \n");
    modifyMatrix(record.n, record.m, mat);
    printMatrix(mat, record.n, record.m);
    // Si stampino su standard output i valori della riga contenente il numero minore di valori NULL
    printf("Punto D: Riga con minor numero di null \n");
    int riga = rowMinNull(mat, record.n, record.m);
    for (int t = 0; t < record.m; t++)
    {
        if (mat[riga][t] == NULL)
        {
            printf("* ");
        }
        else
        {
            printf("%d ", mat[riga][t]);
        }
        
    }
   printf("\n");
    // TODO Clean stuff
    for(int i = 0; i < record.n; i++) {
        free(mat[i]);
    }
    free(mat);
}