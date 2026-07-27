#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileNames
{
    char *fileNameInput;
    char *fileNameOutput;
} FileNames;

typedef struct MatriceInteri
{
    int *arr;
    int righe;
    int colonne;
} MatriceInteri;

typedef struct MatriceDouble
{
    double *arr;
    int righe;
    int colonne;
} MatriceDouble;

void *safeCalloc(int j, int i)
{
    void *rb = calloc(j, i);
    if (rb == NULL)
    {
        perror("Allocation failed \n");
        exit(1);
    }
    return rb;
}

FileNames decodeParameters(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments \n");
        exit(1);
    }
    if (strlen(argv[1]) > 15 || strlen(argv[2]) > 15)
    {
        fprintf(stderr, "Strings too large \n");
        exit(1);
    }
    char *clonedInputF = safeCalloc(strlen(argv[1]) + 1, sizeof(char)); // Necessary because strrchr edits the string
    strcpy(clonedInputF, argv[1]);

    char *clonedOutputF = safeCalloc(strlen(argv[2]) + 1, sizeof(char));
    strcpy(clonedOutputF, argv[2]);

    char *extension = strrchr(argv[1], '.');
    char *extension1 = strrchr(argv[2], '.');
    if (strcmp(extension, ".bin") || strcmp(extension1, ".txt"))
    {
        fprintf(stderr, "Wrong extension \n");
        exit(1);
    }
    FileNames params = {clonedInputF, clonedOutputF};
    return params;
}

double getMeanSinglePixel(MatriceInteri mat, int x, int y)
{
    int counter = 0;
    double sum = 0;
    for (int addX = -1; addX <= 1; addX++)
    {
        for (int addY = -1; addY <= 1; addY++)
        {
            int newX = x + addX;
            int newY = y + addY;
            if (newX >= 0 && newX < mat.colonne && newY >= 0 && newY < mat.righe)
            {
                sum += mat.arr[newY * mat.colonne + newX];
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        printf("Illegal event \n");
        exit(1);
    }
    return sum / counter;
}

MatriceDouble computeCrossMean(MatriceInteri mat)
{
    //printf("CrossMat \n");
    double *arr = safeCalloc(mat.righe * mat.colonne, sizeof(double));
    MatriceDouble matDouble = {arr, mat.righe, mat.colonne};
    for (int y = 0; y < mat.righe; y++)
    {
        for (int x = 0; x < mat.colonne; x++)
        {
            arr[y * mat.colonne + x] = getMeanSinglePixel(mat, x, y);
          //  printf("%d ", mat.arr[y * mat.colonne + x]);
        }
      //  printf("\n");
    }
    return matDouble;
}

MatriceInteri readBinMatrix(char *fileName)
{
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        printf("File non leggibile \n");
        exit(1);
    }
    int matParams[2];                                            // rows and columns
    size_t ret_code = fread(matParams, sizeof(int), 2, filePtr); // reads an array of doubles
    if (ret_code != 2)
    {
        printf("Errore in lettura \n");
        exit(1);
    }
    if (matParams[0] <= 0 || matParams[1] <= 0)
    {
        printf("Valore di R e/o C non ammesso \n");
        exit(1);
    }
    int *arr = safeCalloc(matParams[0] * matParams[1], sizeof(int));
    ret_code = fread(arr, sizeof(int), matParams[0] * matParams[1], filePtr); // reads an array of floats
    if ((int)ret_code != matParams[0] * matParams[1])
    {
        printf("Errore in lettura \n");
        exit(1);
    }
    fclose(filePtr);
    MatriceInteri mat = {arr, matParams[0], matParams[1]};
    return mat;
}

void writeTextMatrix(MatriceDouble mat, char* fileName) {
    FILE* filePtr = fopen(fileName, "w");
    for (int i = 0; i < mat.righe * mat.colonne; i++)
    {
        if (i % mat.colonne == 0 && i > 0)
        {
            fprintf(filePtr, "\n");
        }
        fprintf(filePtr, "%.2f ", (float) mat.arr[i]);
    }
    fclose(filePtr);
}

int main(int argc, char *argv[])
{
    FileNames pam = decodeParameters(argc, argv);
    printf("Struct FileNames: \n");
    printf("inFile = %s: \n", pam.fileNameInput);
    printf("outFile = %s: \n \n", pam.fileNameOutput);
    MatriceInteri mat = readBinMatrix(pam.fileNameInput);
    printf("Matrice A: R = %d, C = %d \n", mat.righe, mat.colonne);
    for (int i = 0; i < mat.righe * mat.colonne; i++)
    {
        if (i % mat.colonne == 0 && i > 0)
        {
            printf("\n");
        }
        printf("%d ", mat.arr[i]);
    }
    printf("\n \n");
    MatriceDouble matProcessed = computeCrossMean(mat);
    printf("Matrice B: \n");
    double maxVal = -1;
    int maxIndex = -1;
    for (int i = 0; i < matProcessed.righe * matProcessed.colonne; i++)
    {
        if (i % matProcessed.colonne == 0 && i > 0)
        {
            printf("\n");
        }
        printf("%.2f ", (float) matProcessed.arr[i]);
        if(matProcessed.arr[i] > maxVal) {
            maxVal = matProcessed.arr[i];
            maxIndex = i;
        }
    }
    printf("\n \n");
    printf("Massimo in B: %.2f\n", maxVal);
    printf("Coordinate: (%d, %d) \n", maxIndex % mat.righe, maxIndex / mat.colonne);
    writeTextMatrix(matProcessed, pam.fileNameOutput);
    

    free(mat.arr);
    free(matProcessed.arr);
    free(pam.fileNameInput);
    free(pam.fileNameOutput);
}