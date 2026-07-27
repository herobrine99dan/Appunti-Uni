#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct String
{
    char *s; // max 100 chars
} String;

typedef struct LinkedNode
{
    int val;
    struct LinkedNode *nextNode;
} LinkedNode;

void push(LinkedNode **startNode, int elem)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->val = elem;
    newElem->nextNode = (*startNode);
    (*startNode) = newElem;
}

int pop(LinkedNode **startNode)
{
    LinkedNode *tempNode = *startNode;
    int val = tempNode->val;
    (*startNode) = tempNode->nextNode;
    free(tempNode);
    return val;
}

int sizeOfStack(LinkedNode *iterator)
{
    int size = 0;
    while (iterator != NULL)
    {
        size++;
        iterator = iterator->nextNode;
    }
    return size;
}

/*
- transferP: funzione che trasferisce il contenuto della pila P su un array
- sort: funzione che ordina l’array*/

int *transferP(int size, LinkedNode **startNode)
{
    /*Si trasferisca il contenuto di P in un array A di opportuna dimensione*/
    int *newArr = calloc(size, sizeof(int));
    int s = sizeOfStack(*startNode);
    for (int i = 0; i < s; i++)
    {
        newArr[i] = pop(startNode);
        i++;
    }
    return newArr;
}

void sort(int superLength, int *arr)
{
    /* e si ordini A
con un algoritmo di ordinamento a scelta.*/
    for (int i = 0; i < superLength - 1; i++)
    {
        for (int j = 0; j < superLength - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void fillP(char *fileName, LinkedNode **startNode, float mean)
{
    /*Il primo valore letto viene inserito
nella pila P. Dal secondo valore in poi (sia esso x), se il valore letto 𝑥 > 𝑚, esso viene inserito
nella pila, altrimenti viene estratto l’elemento in cima a P (sia esso y) e viene inserito nella
pila il valore:*/
    FILE *fileHandler = fopen(fileName, "r");
    if (fileHandler == NULL)
    {
        fprintf(stderr, "Beep beep, file non leggibile. \n");
        exit(1);
    }
    int digit;
    bool firstDigit = true;
    while (fscanf(fileHandler, " %d ", &digit) != EOF)
    {
        if (firstDigit)
        {
            push(startNode, digit);
            firstDigit = false;
            continue;
        }
        if (digit > mean)
        {
            push(startNode, digit);
        }
        else
        {
            int otherDigit = pop(startNode);
            push(startNode, (float)(otherDigit + digit) / 2.0f);
        }
    }
    fclose(fileHandler);
}

float getMean(LinkedNode **startNode)
{
    float mean = 0;
    int size = 0;
    LinkedNode *iterator = *startNode;
    while (iterator != NULL)
    {
        size++;
        mean += (float)iterator->val;
        iterator = iterator->nextNode;
        pop(startNode);
    }
    if (size == 0)
    {
        fprintf(stderr, "Beep beep, nessun elemento nel file. \n");
        exit(1);
    }
    return mean / size;
}

String decodeParameters()
{
    char arr[] = "input.txt";
    char *newArr = calloc(strlen(arr) + 1, sizeof(char));
    if (newArr == NULL)
    {
        fprintf(stderr, "Beep beep, memoria non disponibile. \n");
        exit(1);
    }
    strcpy(newArr, arr);

    char *token = strtok(arr, ".");
    token = strtok(NULL, ".");
    if (strcmp(token, "txt") != 0)
    {
        fprintf(stderr, "Formato file non corretto. \n");
        exit(1);
    }
    String string = {newArr};
    return string;
}

void readFile(char *fileName, LinkedNode **startNode)
{
    FILE *fileHandler = fopen(fileName, "r");
    if (fileHandler == NULL)
    {
        fprintf(stderr, "Beep beep, file non leggibile. \n");
        exit(1);
    }
    int digit;
    while (fscanf(fileHandler, " %d ", &digit) != EOF)
    {
        push(startNode, digit);
    }
    fclose(fileHandler);
}

int main()
{
    printf("==========PUNTO A========== \n");
    String filename = decodeParameters();
    printf("Nome del file: %s \n", filename.s);
    printf("==========PUNTO B========== \n");
    printf("Contenuto della pila: \n");
    LinkedNode *startNode = NULL;
    readFile(filename.s, &startNode);
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        printf("%d \n", iterator->val);
        iterator = iterator->nextNode;
    }
    printf("==========PUNTO C========== \n");
    float mean = getMean(&startNode);
    printf("Media dei valori in P: %.2f\n", mean);
    printf("==========PUNTO D========== \n");
    fillP(filename.s, &startNode, mean);
    printf("Contenuto della pila: \n");
    iterator = startNode;
    while (iterator != NULL)
    {
        printf("%d \n", iterator->val);
        iterator = iterator->nextNode;
    }
    printf("==========PUNTO E========== \n");
    int length = sizeOfStack(startNode);
    int *arr = transferP(length, &startNode);
    sort(length, arr);
    for (int i = 0; i < length; i++)
    {
        printf("%d\n", arr[i]);
    }
    free(arr);
}