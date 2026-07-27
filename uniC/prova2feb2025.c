#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

typedef struct inputParams
{
    char *inputFile;
    char *outputFile;
} inputParams;

typedef struct user
{
    char *name;
    char *surname;
    int id;
    int startYear;
    float money;
} user;

typedef struct LinkedNode
{
    user *element;
    struct LinkedNode *nextNode;
} LinkedNode;

float getMax(LinkedNode *startNode)
{
    float max = -1;
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        if (iterator->element->money > max)
        {
            max = iterator->element->money;
        }
        iterator = iterator->nextNode;
    }
    return max;
}

float min(float x, float y)
{
    return x < y ? x : y;
}

void removeAccount(LinkedNode *startNode, float max)
{
    LinkedNode *iterator = startNode;
    LinkedNode *previous = startNode;

    LinkedNode *minXUser = startNode;
    LinkedNode *minXUserPrevious = startNode;
    float lastMinX = 100000;
    while (iterator != NULL)
    {
        float x = min((2023.0f - iterator->element->startYear) / 5.0f, 1) * (iterator->element->money / max);
        if (x < lastMinX && iterator->element->id != -1)
        {
            minXUserPrevious = previous;
            lastMinX = x;
            minXUser = iterator;
        }

        previous = iterator;
        iterator = iterator->nextNode;
    }
    minXUserPrevious->nextNode = minXUser->nextNode;
    free(minXUser);
}

user *decodeAndConvert(char *buf)
{
    int id, startYear;
    float money;

    char *token = strtok(buf, " ");
    char *nameClone = calloc(strlen(token) + 1, sizeof(char));
    strcpy(nameClone, token);
    token = strtok(NULL, " ");
    char *surnameClone = calloc(strlen(token) + 1, sizeof(char));
    strcpy(surnameClone, token);
    token = strtok(NULL, " ");
    id = atoi(token);
    token = strtok(NULL, " ");
    startYear = atoi(token);
    token = strtok(NULL, " ");
    money = (float)atof(token);

    user *var = calloc(1, sizeof(user));
    var->id = id;
    var->money = money;
    var->startYear = startYear;
    var->name = nameClone;
    var->surname = surnameClone;
    return var;
}

void append(LinkedNode *startNode, user *var)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->element = var;
    LinkedNode *previous = startNode;
    LinkedNode *iterator = startNode;
    while (iterator->nextNode != NULL)
    {
        /* if (var->startYear >= previous->element->startYear && var->startYear <= iterator->element->startYear)
        {
            break;
        } */
        previous = iterator;
        iterator = iterator->nextNode;
    }
    iterator->nextNode = newElem;
}

void insert(LinkedNode *startNode, user *var)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->element = var;
    LinkedNode *previous = startNode;
    LinkedNode *iterator = startNode;
    while (iterator->nextNode != NULL)
    {
        if (var->startYear >= previous->element->startYear)
        {
            break;
        }
        previous = iterator;
        iterator = iterator->nextNode;
    }
    previous->nextNode = newElem;
    newElem->nextNode = iterator;
}

int listLength(LinkedNode *startNode)
{
    int n = 0;
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        n++;
        iterator = iterator->nextNode;
    }
    return n;
}

void printList(LinkedNode *startNode)
{
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        printf("%d -->", iterator->element->startYear);
        iterator = iterator->nextNode;
    }
    printf("\n");
}

LinkedNode *readFile(char *inputFile)
{
    /*
     Legga il contenuto del file e salvi i dati relativi in una lista concatenata A.
    . I dati vanno inseriti nella lista in ordine di anno di apertura
    del conto.*/
    FILE *filePtr = fopen(inputFile, "r");
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode)); // dummy node
    startNode->element = calloc(1, sizeof(user));
    startNode->element->startYear = 0;
    startNode->element->id = -1;
    if (filePtr == NULL)
    {
        fprintf(stderr, "Impossibile accedere al file \n");
        exit(1);
    }
    char buf[1024];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        user *var = decodeAndConvert(buf);
        printf("elemento: %s \n", var->surname);
        append(startNode, var);
    }
    printList(startNode);
    fclose(filePtr);
    return startNode;
}

int checkExtension(char *str)
{
    char *cpy = calloc(strlen(str) + 1, sizeof(char));
    strcpy(cpy, str);
    char *token = strtok(cpy, ".");
    token = strtok(NULL, ".");
    int returnVal = strcmp(token, "txt");
    free(cpy);
    return returnVal;
}

inputParams *readInput(int argv, char *argc[])
{
    if (argv != 3)
    {
        fprintf(stderr, "Parametri mancanti \n");
        exit(1);
    }
    inputParams *returnVal = malloc(sizeof(inputParams));
    char *arr1 = calloc(strlen(argc[1]) + 1, sizeof(char));
    char *arr2 = calloc(strlen(argc[2]) + 1, sizeof(char));

    if (checkExtension(argc[1]) == 0 && checkExtension(argc[2]) == 0)
    {
        returnVal->inputFile = strcpy(arr1, argc[1]);
        returnVal->outputFile = strcpy(arr2, argc[2]);
        return returnVal;
    }
    fprintf(stderr, "File con estensione non valida \n");
    exit(1);
}

void writeFile(LinkedNode *startNode, char *outputFile)
{
    FILE *filePtr = fopen(outputFile, "w");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non scrivibile \n");
        exit(1);
    }
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        if (iterator->element->id == -1)
        {
            iterator = iterator->nextNode;
            continue;
        }
        char *name = iterator->element->name;
        char *surname = iterator->element->surname;
        int id = iterator->element->id;
        int startYear = iterator->element->startYear;
        float money = iterator->element->money;
        fprintf(filePtr, "%s %s %d %d %f \n", name, surname, id, startYear, money);
        iterator = iterator->nextNode;
    }
    fclose(filePtr);
}

void recursivelyClean(LinkedNode* startNode) {
    if(startNode->nextNode == NULL) {
        return;
    }
    recursivelyClean(startNode->nextNode);
    free(startNode->element->name);
    free(startNode->element->surname);
    free(startNode->element);
    free(startNode);
}

int main(int argv, char *argc[])
{
    printf("Punto A: Convalida parametri \n");
    inputParams *params = readInput(argv, argc);
    printf("Input: %s, Output %s \n", params->inputFile, params->outputFile);
    printf("Punto B: Lettura-Creazione lista \n");
    LinkedNode *list = readFile(params->inputFile);
    printf("Punto C: Cliente valore più alto X \n");
    removeAccount(list, getMax(list));
    printList(list);
    printf("Punto D: punto C eseguito n/2 volte X \n");
    for (int i = 0; i < (int)((listLength(list) + 1) / 2); i++)
    {
        removeAccount(list, getMax(list));
    }
    printList(list);
    printf("Punto E: Salvataggio \n");
    writeFile(list, params->outputFile);

    free(params->inputFile);
    free(params->outputFile);
    free(params);
    LinkedNode *iterator = list;
    recursivelyClean(list);
}