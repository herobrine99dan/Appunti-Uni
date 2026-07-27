#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>

typedef struct LinkedNode
{
    float n;
    struct LinkedNode *nextNode;
} LinkedNode;

void filtraLista(LinkedNode **testa, float min, float max)
{
    LinkedNode *lastNode = NULL;
    LinkedNode *iterator = *testa;
    while (iterator != NULL)
    {
        //[min_val + 1.0, max_val - 1.0]
        if (iterator->n <= min + 1 || iterator->n >= max - 1) //!(iterator->n >= min + 1 && iterator->n <= max - 1)
        {
            //printf("Valore non bello %f \n", iterator->n);
            if (lastNode != NULL)
            {
                lastNode->nextNode = iterator->nextNode;
            }
            else
            {
                // update start node
                (*testa) = iterator->nextNode;
            }
            LinkedNode* nextNode = iterator->nextNode;
            free(iterator);
            iterator = nextNode;
        } else {
            lastNode = iterator;
            iterator = iterator->nextNode;
        }
        
    }
}

void scriviSuFile(LinkedNode *startNode, const char *nome_file)
{
    FILE *fileHandler = fopen(nome_file, "w");
    if (fileHandler == NULL)
    {
        fprintf(stderr, "Impossibile aprire il file \n");
        exit(1);
    }
    while (startNode != NULL)
    {
        fprintf(fileHandler, "%.2f\n", startNode->n);
        startNode = startNode->nextNode;
    }
    fclose(fileHandler);
}

void insert(LinkedNode **startNode, float val)
{
    LinkedNode *newNode = calloc(1, sizeof(LinkedNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "not enough memory \n");
        exit(1);
    }
    newNode->n = val;
    if (*startNode == NULL)
    {
        (*startNode) = newNode;
        return;
    }
    LinkedNode *lastNonNullNode = *startNode;
    LinkedNode *iterator = *startNode;
    while (1)
    {
        lastNonNullNode = iterator;
        iterator = iterator->nextNode;
        if (iterator == NULL || iterator->n < val)
        {
            break;
        }
    }
    //printf("Mi sono fermato a %f\n", lastNonNullNode->n);
    lastNonNullNode->nextNode = newNode;
    newNode->nextNode = iterator;
}

void trovaMinMax(LinkedNode *startNode, float *min, float *max)
{
    float minVal = FLT_MAX; //TODO Use FLT_MAX
    float maxVal = -FLT_MAX;
    LinkedNode *iterator = startNode;
    while (1)
    {
        if (iterator->n > maxVal)
        {
            maxVal = iterator->n;
        }
        if (iterator->n < minVal)
        {
            minVal = iterator->n;
        }
        iterator = iterator->nextNode;
        if (iterator == NULL)
        {
            break;
        }
    }
    *min = minVal;
    *max = maxVal;
}

void printList(LinkedNode *startNode)
{
    while (startNode != NULL)
    {
        printf("%.2f --> ", startNode->n);
        startNode = startNode->nextNode;
    }
    printf(" NULL \n");
}

LinkedNode *leggiDatiCreaLista(int n)
{
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode)); // using a dummy node
    startNode->n = __builtin_inff();
    for (int i = 0; i < n; i++)
    {
        float val;
        scanf("%f", &val);
        insert(&startNode, val);
    }
    // remove first node;
    LinkedNode *returnValue = startNode->nextNode;
    free(startNode);
    return returnValue;
}

char *gestisciInput(int argc, char *argv[], int *N)
{
    char *filenameCopy = calloc(strlen(argv[1]) + 1, sizeof(char));
    strcpy(filenameCopy, argv[1]);
    char *token = strtok(argv[1], ".");
    token = strtok(NULL, ".");
    if (strcmp(token, "txt") != 0)
    {
        fprintf(stderr, "File non valido \n");
        exit(1);
    }
    scanf("%d", N);
    if ((*N) <= 0)
    {
        fprintf(stderr, "Numero elementi non valido\n");
        exit(1);
    }
    return filenameCopy;
}

void recursiveClean(LinkedNode *startNode)
{
    if (startNode->nextNode != NULL)
    {
        recursiveClean(startNode->nextNode);
    }
    free(startNode);
}

int main(int argc, char *argv[])
{
    printf("argc: %d\n", argc);
    printf("firstarg: %s \n", argv[0]);
    printf("secondarg: %s \n", argv[1]);
    printf("====== PUNTO A: Parametri ====== \n");
    int nElements = 0;
    char *outputFile = gestisciInput(argc, argv, &nElements);
    printf("File di output: %s \n", outputFile);
    printf("====== PUNTO B: Lista Iniziale Ordinata ====== \n");
    LinkedNode *startNode = leggiDatiCreaLista(nElements);
    printList(startNode);
    float min, max;
    trovaMinMax(startNode, &min, &max);
    printf("====== PUNTO C: Valori Minimo e Massimo ======\n");
    printf("Valore minimo: %.2f \n", min);
    printf("Valore massimo: %.2f \n", max);
    printf("====== PUNTO D: Lista Filtrata ====== \n");
    filtraLista(&startNode, min, max);
    printList(startNode);
    printf("====== PUNTO E: Scrittura su File ====== \n");
    scriviSuFile(startNode, outputFile);
    printf("Scrittura su file '%s' completata con successo. \n", outputFile);
    free(outputFile);
    recursiveClean(startNode);
}