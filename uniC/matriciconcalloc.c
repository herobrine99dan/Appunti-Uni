#include <stdio.h>
#include <stdlib.h>

int traccia(int *mat, int rows, int columns)
{
    int somma = 0;
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            if (x == y)
            {
                somma += mat[y * rows + x];
            }
        }
        printf("\n");
    }
    printf("Traccia %d \n", somma);
    return somma;
}

int tracciaFaster(int *mat, int rows, int columns)
{
    int somma = 0;
    for (int i = 0; i < rows * columns; i++)
    {
        int x = i / rows;
        int y = i % columns;
        if (x == y)
        {
            somma += mat[i];
        }
    }
    printf("Traccia %d \n", somma);
    return somma;
}

void trasposta(int mat[], int rows, int columns)
{
    int *temp = calloc(rows * columns, sizeof(int));

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            printf("In x %d e y %d ho il valore %d \n", x, y, mat[x * rows + y]);
            printf("Da sostituire con %d \n", mat[y * rows + x]);
            temp[x * rows + y] = mat[y * rows + x];
        }
    }
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            mat[x * rows + y] = temp[x * rows + y];
        }
    }
    free(temp);
    temp = NULL;
}

void printMatrix(int mat[], int rows, int columns)
{
    printf("La matrice che hai scritto è: \n");
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            printf("%d ", mat[x * rows + y]);
        }
        printf("\n");
    }
}

int determinanteRicorsivo(int mat[], int rows, int columns)
{
    if (rows != columns)
    {
        printf("Determinant is unavailable for this matrix. \n");
        return -1;
    }
    if (rows == 2 && columns == 2)
    {
        int det = mat[0] * mat[3] - mat[1] * mat[2];
        return det;
    }
    int determinante = 0;
    for (int i = 0; i < rows; i++)
    { // Scorri gli elementi della prima riga, preparo gli elementi per il calcolo
        int cofactorSign = i % 2 == 0 ? 1 : -1;
        int cofactorScalar = mat[0 * rows + i];
        //  calcolo la matrice cofattore
        int arr[(rows - 1) * (columns - 1)];
        int cofactorMatIndex = 0;
        for (int x = 1; x < rows; x++) // La mat. cofattori esclude gli elementi che hanno stessa riga o stessa colona dell'elemento per cui sto calcolando, considero sempre la prima riga
        {
            for (int y = 0; y < columns; y++)
            {
                int element = mat[x * rows + y];
                if (y != i)
                {
                    arr[cofactorMatIndex] = element;
                    cofactorMatIndex++;
                }
            }
        }
        int detCofattore = determinanteRicorsivo(arr, (rows - 1), (columns - 1));
        // printf("Cofattore per scalare %d \n ", cofactorScalar);
        // printMatrix(arr, 2, 2);
        int intermedio = cofactorSign * cofactorScalar * detCofattore;
        // printf("Fase intermedia: %d*%d*%d \n", cofactorSign, cofactorScalar, detCofattore);
        determinante += intermedio;
    }
    return determinante;
}

/* int rankMatrix(int mat[], int rows, int columns)
{
    if (determinanteRicorsivo(mat, rows, columns) != 0)
    {
        return rows; // Rows and columns should be equal
    }


} */

int main()
{
    printf("Scrivi numero di righe e colonne m,n \n");
    int rows;
    int columns;
    scanf("%d,%d", &rows, &columns);
    int *arr = (int *)calloc((size_t)rows * (size_t)columns, sizeof(int)); // int arr[rows * columns];
    if (arr == NULL)
    {
        printf("BEEEP BEEEP!!! Non c'ho spazio.\n");
        return 1;
    }
    printf("Scrivi i componenti della matrice nel formato a b c d e... \n");
    for (int i = 0; i < rows * columns; i++)
    {
        int n;
        scanf("%d", &n);
        arr[i] = n;
    }
    printMatrix(arr, rows, columns);
    trasposta(arr, rows, columns);
    printMatrix(arr, columns, rows);
    printf("Determinante: %d \n", determinanteRicorsivo(arr, rows, columns));
    printf("Rilasciare ptr? S\\n \n");
    char c;
    scanf(" %c", &c); // Importantissimo per ignorare white spaces e caratteri strani
    if (c == 's')
    {
        free(arr);
        arr = NULL; // avoid dangling pointers
    }
}