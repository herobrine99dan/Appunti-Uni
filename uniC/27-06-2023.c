#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct params
{
    char *filename;
    int n;
} params;

typedef struct Record
{
    int id;
    char *name;
    char *surname;
    float balance;
} Record;

typedef struct LinkedNode
{
    Record *record;
    struct LinkedNode *nextNode;
} LinkedNode;

void append(LinkedNode *startNode, Record *rec)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->record = rec;
    LinkedNode *iterator = startNode;
    while (iterator->nextNode != NULL)
    {
        iterator = iterator->nextNode;
    }
    iterator->nextNode = newElem;
}

int size(LinkedNode *startNode)
{
    LinkedNode *iterator = startNode;
    int i = 0;
    while (iterator != NULL)
    {
        i++;
        iterator = iterator->nextNode;
    }
    return i;
}

float getMeanBalance(LinkedNode *startNode)
{
    LinkedNode *iterator = startNode;
    float sum = 0;
    int i = 0;
    while (iterator != NULL)
    {
        i++;
        sum += iterator->record->balance;
        iterator = iterator->nextNode;
    }
    return sum / (float)i;
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

void sort(Record **arr, int size, float m)
{
    for (int i = 0; i < size; i++)
    {
        int smallestElemIndex = i;
        for (int j = i; j < size; j++)
        {
            float cmp1 = (arr[smallestElemIndex]->balance - m) * (arr[smallestElemIndex]->balance - m);
            float cmp2 = (arr[j]->balance - m) * (arr[j]->balance - m);
            if (cmp2 < cmp1)
            {
                smallestElemIndex = j;
            }
        }
        Record *temp = arr[i];
        arr[i] = arr[smallestElemIndex];
        arr[smallestElemIndex] = temp;
    }
}

Record **getArray(LinkedNode *startNode)
{
    int sizeN = size(startNode);
    Record **records = calloc(sizeN, sizeof(Record));
    LinkedNode *iterator = startNode;
    int i = 0;
    while (iterator != NULL)
    {
        records[i++] = iterator->record;
        iterator = iterator->nextNode;
    }
    return records;
}

Record *readRecord()
{
    int id;
    float balance;
    char name[255];
    char surname[255];
    int output = scanf("%d %s %s %f", &id, name, surname, &balance);
    if (output == EOF || output < 4)
    {
        return NULL; // No more available records to read from stdin
    }
    Record *rec = calloc(1, sizeof(Record));
    char *cloned = calloc(strlen(name) + 1, sizeof(char));
    strcpy(cloned, name);

    char *cloned1 = calloc(strlen(surname) + 1, sizeof(char));
    strcpy(cloned1, surname);

    rec->id = id;
    rec->name = cloned;
    rec->surname = cloned1;
    rec->balance = balance;
    return rec;
}

LinkedNode *loadRecords()
{
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode));
    while (true)
    {
        Record *rec = readRecord();
        if (rec == NULL)
        {
            break;
        }
        append(startNode, rec); // 28 minutes
    }
    LinkedNode *temp = startNode;
    startNode = startNode->nextNode;
    free(temp);
    return startNode;
}

params decodeParameters(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Not enough arguments \n");
        exit(1);
    }
    char *filename = argv[1];
    int n = atoi(argv[2]);
    if (n < 3 || n > 5)
    {
        fprintf(stderr, "Number out of range \n");
        exit(1);
    }
    char *cloned = calloc(strlen(filename) + 1, sizeof(char));
    strcpy(cloned, filename);

    char *ext = strrchr(filename, '.');
    printf("extension %s\n", ext);
    if (ext == NULL || strcmp(ext, ".bin") != 0)
    {
        fprintf(stderr, "Wrong extension \n");
        exit(1);
    }

    params pam = {cloned, n};
    return pam;
}

void recursivelyClean(LinkedNode *node)
{
    if (node == NULL)
    {
        return;
    }
    recursivelyClean(node->nextNode);
    free(node);
}

int main(int argc, char *argv[])
{
    params pam = decodeParameters(argc, argv);
    printf("PUNTO A - valori dei parametri presi in input:\nfilename = %s\nn = %d\n", pam.filename, pam.n);
    LinkedNode *list = loadRecords();
    printf("PUNTO B - Contenuto di L: \n");

    LinkedNode *iterator = list;
    while (iterator != NULL)
    {
        // printf("%d", iterator->record->id);
        printf("%d %s %s %.2f \n", iterator->record->id, iterator->record->name, iterator->record->surname, iterator->record->balance);
        iterator = iterator->nextNode;
    }

    printf("PUNTO C - Contenuto di X dopo l'ordinamento: \n");
    int sizeN = size(list);
    Record **records = getArray(list);
    sort(records, sizeN, getMeanBalance(list));
    for (int i = 0; i < sizeN; i++)
    {
        printf("%d %s %s %.2f \n", records[i]->id, records[i]->name, records[i]->surname, records[i]->balance);
    }
    saveToFile(records, sizeN, pam.filename);
    for (int i = 0; i < sizeN; i++)
    {
        free(records[i]->name);
        free(records[i]->surname);
        free(records[i]);
    }
    free(records);
    recursivelyClean(list);
    printf("PUNTO D - Contenuto del file binario in ordine casuale: \n");
    showFileContent(pam.filename);
    free(pam.filename);
}