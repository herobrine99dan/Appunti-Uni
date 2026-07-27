#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    int i;
    struct LinkedNode *nextNode;
} LinkedNode;

void insert(LinkedNode *startNode, char *str)
{
    int len = strlen(str);
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->str = str;
    // Instead of searching the last element, we search the last element whose string's length is lower than the current
    LinkedNode *iterator = startNode;
    LinkedNode *previous = iterator;
    while (iterator != NULL)
    {
        if(len > (int) strlen(iterator->str)) {
            previous = iterator;
        }
        iterator = iterator->nextNode;
    }
   newElem->nextNode = previous->nextNode;
    previous->nextNode = newElem;
}

typedef struct
{
    int id_sensore;
    long int timestamp;
    double valore;
    char tipo;
    int anomalia; // Flag per marcare le anomalie (0 o 1)
} Rilevazione;

void *customCalloc(size_t __nmemb, size_t __size) {
    void *ptr = calloc(__nmemb, __size);
    if(ptr == NULL) {
        perror("Errore nell'allocazione di memoria \n");
        exit(1);
    }
    return ptr;
}

void readDataAndCreateList(char *fileName, LinkedNode **startNode)
{
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non leggibile \n");
        exit(1);
    }
    char buf[1024];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        int id_sensore;
        long int timestamp;
        double valore;
        char tipo;
        sscanf(buf, "%d %ld %lf %c", &id_sensore, &timestamp, &valore, &tipo);
        Rilevazione *record = malloc(sizeof(Rilevazione));
        record->id_sensore = id_sensore;
        record->timestamp = timestamp;
        record->tipo = tipo;
        record->valore = valore;
        push(startNode, record);
        // printf("%s", buf);
    }
    fclose(filePtr);
}

/*
Extension example: .bin, .txt
*/
int checkExtension(char *filename, char *extension)
{
    char *ext = strrchr(filename, '.');
    printf("extension %s\n", ext);
    if (ext == NULL || strcmp(ext, extension) != 0)
    {
        return 0;
    }
    return 1;
}

typedef struct Record
{
    int id;
    char *name;
    char *surname;
    float balance;
} Record;

void recursivelyClean(LinkedNode *node)
{
    if (node == NULL)
    {
        return;
    }
    recursivelyClean(node->nextNode);
    free(node);
}

void saveToFile(Record **arr, int sizeN, char *filename)
{
    FILE *filePtr = fopen(filename, "wb");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non accessibile\n");
        exit(1);
    }
    fwrite(&sizeN, sizeof(int), 1, filePtr);
    for (int i = 0; i < sizeN; i++)
    {
        // 1. Write ID
        fwrite(&(arr[i]->id), sizeof(int), 1, filePtr);

        // 2. Write Name Length, then the Name
        int nameLen = strlen(arr[i]->name) + 1;
        fwrite(&nameLen, sizeof(int), 1, filePtr); // The "Header"
        fwrite(arr[i]->name, sizeof(char), nameLen, filePtr);

        // 3. Write Surname Length, then Surname
        int surLen = strlen(arr[i]->surname) + 1;
        fwrite(&surLen, sizeof(int), 1, filePtr); // The "Header"
        fwrite(arr[i]->surname, sizeof(char), surLen, filePtr);

        // 4. Write Balance
        fwrite(&(arr[i]->balance), sizeof(float), 1, filePtr);
    }
    fclose(filePtr);
}

typedef struct params
{
    char *inputFile;
    char *outputFile;
} params;

params decodeParameters(int argc, char *argv[])
{ // Bisogna controllare tutto, anche quando dice "si assuma che"
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments \n");
        exit(1);
    }
    if (strlen(argv[1]) > 100 || strlen(argv[2]) > 100)
    {
        fprintf(stderr, "Strings too large \n");
        exit(1);
    }
    char *clonedInputF = calloc(strlen(argv[1]) + 1, sizeof(char)); // Necessary because strrchr edits the string
    strcpy(clonedInputF, argv[1]);

    char *clonedOutputF = calloc(strlen(argv[2]) + 1, sizeof(char)); //+ 1 because strcpy needs extra space to put '\0
    strcpy(clonedOutputF, argv[2]);

    char *extension = strrchr(argv[1], '.');
    char *extension1 = strrchr(argv[2], '.');
    if (strcmp(extension, ".txt") || strcmp(extension1, ".txt"))
    {
        fprintf(stderr, "Wrong extension \n");
        exit(1);
    }
    params params = {clonedInputF, clonedOutputF};
    return params;
}

void poppingWhileIterating(LinkedNode **headNode)
{
    /*Scorra la coda Q estraendo ciascuna stringa, una per una. Per ogni stringa estratta:
se la sua lunghezza è pari, la stringa viene reinserita in coda così com'è. Se invece la sua
lunghezza è dispari, la stringa viene invertita e quindi reinserita in coda. Tutte le stringhe
devono essere elaborate e reinserite in coda per mantenere l'ordine FIFO.
Si stampi a schermo il contenuto della coda Q dopo questa operazione.*/
    LinkedNode *iterator = *headNode;
    int size = sizeN(iterator);
    for (int i = 0; i < size; i++)
    {
        LinkedNode *tempNext = iterator->nextNode; // WARNING!!! I have to save the next node before i pop it, otherwise I get a dangling pointer.
        char *string = pop(headNode);
        int len = stringLength(string);

        if (len % 2 == 0)
        {
            append(*headNode, string);
        }
        else
        {
            append(*headNode, invertString(string));
        }
        iterator = tempNext;
    }
}

void showFileContent(char *filename)
{
    FILE *filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non accessibile\n");
        exit(1);
    }
    int sizeN;
    fread(&sizeN, sizeof(int), 1, filePtr);
    for (int i = 0; i < 5; i++)
    {
        int id;
        fread(&id, sizeof(int), 1, filePtr);
        int nameLength;
        fread(&nameLength, sizeof(int), 1, filePtr);
        char name[nameLength];
        fread(name, sizeof(char), nameLength, filePtr);

        int surNameLength;
        fread(&surNameLength, sizeof(int), 1, filePtr);
        char surname[surNameLength];
        fread(surname, sizeof(char), surNameLength, filePtr);

        float balance;
        fread(&balance, sizeof(float), 1, filePtr);
        printf("%d %s %s %.2f \n", id, name, surname, balance);
    }
    fclose(filePtr);
}