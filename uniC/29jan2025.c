#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct params
{
    char *inputFile;
    char *outputFile;
} params;

typedef struct Person
{
    char *name;
    char *surname;
    int age;
    float height;
} Person;

void *eazyCalloc(size_t __nmemb, size_t __size)
{
    void *returnVal = calloc(__nmemb, __size);
    if (returnVal == NULL)
    {
        perror("Memory allocation error\n");
        exit(1);
    }
    return returnVal;
}

Person **readFile(int n, FILE *filePtr)
{
    char buf[1024];                             // Should be enough
    Person **arr = eazyCalloc(n, sizeof(Person *)); // Array of pointers...
    for (int i = 0; i < n; i++)
    {
        Person *obj = eazyCalloc(1, sizeof(Person));
        char name[1024];
        char surname[1024];
        int age;
        float height;
        if (fgets(buf, sizeof buf, filePtr) != NULL)
        {
            sscanf(buf, " %s %s %d %f ", name, surname, &age, &height);
            if (strlen(name) > 50 || strlen(surname) > 50)
            {
                perror("String bigger than expected \n");
                exit(1);
            }
        }
        else
        {
            perror("Lines missing in the file \n");
            exit(1);
        }
        char *nameInHeap = eazyCalloc(strlen(name) + 1, sizeof(char));
        char *surnameInHeap = eazyCalloc(strlen(surname) + 1, sizeof(char));
        strcpy(nameInHeap, name);
        strcpy(surnameInHeap, surname);
        obj->name = nameInHeap;
        obj->surname = surnameInHeap;
        obj->age = age;
        obj->height = height;
        arr[i] = obj;
    }

    return arr;
}

int *extractAges(Person **arr, int n)
{
    /*Si determini l’età mediana come il
valore centrale dell’array ordinato (si assuma che l’array abbia sempre una lunghezza dispari).*/
    int *ageArr = eazyCalloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        ageArr[i] = arr[i]->age;
    }
    return ageArr;
}

int sortAges(int *ageArr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j > 0 && ageArr[j] < ageArr[j - 1]; j--)
        {
            int temp = ageArr[j];
            ageArr[j] = ageArr[j - 1];
            ageArr[j - 1] = temp;
        }
    }
    return ageArr[n / 2];
}

int readHeader(FILE *filePtr)
{
    char buf[64];
    fgets(buf, sizeof buf, filePtr);
    int digit;
    sscanf(buf, " %d", &digit);
    return digit;
}

int checkExtension(char *str)
{
    char *extension = strrchr(str, '.');
    return strcmp(extension, ".txt");
}

float calculateAverageHeight(Person **arr, int n, float median)
{
    float mean = 0;
    int size = 0;
    for (int i = 0; i < n; i++)
    {
        Person *obj = arr[i];
        if (obj->age > median)
        {
            mean += obj->height;
            size++;
        }
    }
    return mean / size;
}

params *decodeParameters(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Not enough arguments \n");
        exit(1);
    }
    params *pam = eazyCalloc(1, sizeof(params));
    char *cloned1 = eazyCalloc(strlen(argv[1]) + 1, sizeof(char));
    char *cloned2 = eazyCalloc(strlen(argv[2]) + 1, sizeof(char));
    pam->inputFile = strcpy(cloned1, argv[1]);
    pam->outputFile = strcpy(cloned2, argv[2]);
    if (checkExtension(argv[1]) != 0 || checkExtension(argv[2]) != 0)
    {
        perror("Wrong extension \n");
        exit(1);
    }
    return pam;
}

void writeOutput(Person **arr, int n, float meanHeigh, char *outputFile)
{
    FILE *filePtr = fopen(outputFile, "w");
    if (filePtr == NULL)
    {
        perror("File non scrivibile \n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        Person *obj = arr[i];
        if(obj->height > meanHeigh) {
            fprintf(filePtr, "%s %s, Età: %d, Altezza: %.2f\n", obj->name, obj->surname, obj->age, obj->height);
        }
    }
    fclose(filePtr);
}

int main(int argc, char *argv[])
{
    params *pam = decodeParameters(argc, argv);
    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n", pam->inputFile, pam->outputFile);
    FILE *filePtr = fopen(pam->inputFile, "r"); // The FILE* structure is shared among readHeader and readFile
    if (filePtr == NULL)
    {
        perror("File non leggibile \n");
        exit(1);
    }
    int n = readHeader(filePtr);
    printf("======B Valori letti dall'header======\nn = %d\n", n);
    printf("======B Contenuto dell'array di strutture======\n");

    Person **arr = readFile(n, filePtr);
    for (int i = 0; i < n; i++)
    {
        Person *person = arr[i];
        //  printf("%s\n",person->surname);
        printf("%d. Nome: %s, Cognome: %s, Età: %d, Altezza: %.2ff\n", (i + 1), person->name, person->surname, person->age, person->height);
    }
    int *ageArr = extractAges(arr, n);
    printf("======C Array Z (età)======\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ageArr[i]);
    }
    printf("\n");
    int medianAge = sortAges(ageArr, n);
    printf("======C Array Z Ordinato======\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ageArr[i]);
    }
    printf("\n");
    printf("Mediana delle età: %d \n", medianAge);
    float meanHeigh = calculateAverageHeight(arr, n, medianAge);
    printf("======D Altezza media delle persone con età superiore alla mediana====== \nMedia: %.2f \n", meanHeigh);

    printf("======E Scrittura su file risultato.txt======\n");
    writeOutput(arr, n, meanHeigh, pam->outputFile);
    printf("File scritto correttamente.\n");
    for(int i = 0; i < n; i++) {
        Person* obj = arr[i];
        free(obj->name);
        free(obj->surname);
        free(obj);
    }

    free(ageArr);
    free(arr);
    fclose(filePtr);
    free(pam->inputFile);
    free(pam->outputFile);
    free(pam);
}