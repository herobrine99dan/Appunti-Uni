#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct params
{
    char *inputFile;
    char *outputFile;
    char sensor;
} params;

typedef struct
{
    int id_sensore;
    long int timestamp;
    double valore;
    char tipo;
    int anomalia; // Flag per marcare le anomalie (0 o 1)
} Rilevazione;

typedef struct LinkedNode
{
    Rilevazione *element;
    struct LinkedNode *nextNode;
} LinkedNode;

void push(LinkedNode **startNode, Rilevazione *element)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->element = element;
    newElem->nextNode = (*startNode);
    (*startNode) = newElem;
}

/*
• writeAnomaliesToFile: salva su file solo i nodi della lista marcati come anomali.*/

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

int checkExtension(char *filename, char *extension)
{
    char *token = strtok(filename, ".");
    token = strtok(NULL, ".");
    return strcmp(token, extension);
}
/*markAnomalies: riceve la testa della lista, la media e il tipo di sensore, e imposta il flag per
ogni nodo che rappresenta un'anomalia.*/
void markAnomalies(LinkedNode *list, float mean, char sensorType)
{
    while (list->nextNode != NULL)
    {
        if (list->element->tipo == sensorType && list->element->valore > mean * 1.5f)
        {
            list->element->anomalia = 1;
        }
        list = list->nextNode;
    }
}

float calculateAverage(LinkedNode *list, char sensorType)
{
    float sum = 0;
    int size = 0;
    while (list->nextNode != NULL)
    {
        if (list->element->tipo == sensorType)
        {
            size++;
            sum += (float) list->element->valore;
        }
        list = list->nextNode;
    }
    return sum / (float) size;
}

void printList(LinkedNode *list)
{
    while (list->nextNode != NULL)
    {
        char flagStr[24] = "";
        if (list->element->anomalia == 1)
        {
            strcpy(flagStr, "**ANOMALIA**");
        }
        printf("[ID: %d, TS: %ld, Val: %.2f, Tipo: %c] %s -> \n", list->element->id_sensore, list->element->timestamp, list->element->valore, list->element->tipo, flagStr);
        list = list->nextNode;
    }
    printf("NULL \n");
}

void writeAnomaliesToFile(char *outputFile, LinkedNode *list)
{
    FILE *filePtr = fopen(outputFile, "w");
    if (filePtr == NULL)
    {
        fprintf(stderr, "Impossibile aprire il file \n");
    }
    while (list->nextNode != NULL)
    {
        if(list->element->anomalia==1) {
            fprintf(filePtr, "%d,%ld,%.2f,%c\n", list->element->id_sensore, list->element->timestamp, list->element->valore, list->element->tipo);
        }
        list = list->nextNode;
    }
    fclose(filePtr);
}

params *decodeParameters(int argc, const char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Parametri errati \n");
        exit(1);
    }
    char *sensor = argv[3];
    if (sensor[0] != 'T' && sensor[0] != 'U' && sensor[0] != 'P')
    {
        fprintf(stderr, "Sensore non valido %c\n", sensor[0]);
        exit(1);
    }
    params *returnVal = malloc(sizeof(params));
    returnVal->sensor = sensor[0];

    char *inputFile = argv[1];
    char *outputFile = argv[2];
    char *arr1 = calloc(strlen(inputFile) + 1, sizeof(char));
    char *arr2 = calloc(strlen(outputFile) + 1, sizeof(char));
    strcpy(arr1, inputFile);
    strcpy(arr2, outputFile);
    returnVal->inputFile = arr1;
    returnVal->outputFile = arr2;
    if (checkExtension(inputFile, "tsv") != 0 || checkExtension(outputFile, "txt") != 0)
    {
        fprintf(stderr, "Estensione non valida \n");
        exit(1);
    }
    return returnVal;
}

void recursivelyCleanStack(LinkedNode* iterator) {
    if(iterator->nextNode == NULL) {
        return;
    }
    recursivelyCleanStack(iterator->nextNode);
    free(iterator->element);
    free(iterator->nextNode);
}

int main(int argc, char *argv[])
{
    printf("========== PUNTO A: PARAMETRI ========== \n");
    params *pam = decodeParameters(argc, argv);
    printf("File di input: %s \nFile di output: %s \nTipo di sensore da analizzare: %c \n", pam->inputFile, pam->outputFile, pam->sensor);
    printf("========== PUNTO B: LISTA CREATA ========== \n");
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode));
    readDataAndCreateList(pam->inputFile, &startNode);
    printList(startNode);
    float mean = calculateAverage(startNode, pam->sensor);
    printf("========== PUNTO C: CALCOLO MEDIA ==========\nMedia dei valori per il sensore di tipo '%c': %.2f\n", pam->sensor, mean);
    printf("========== PUNTO D: MARCATURA ANOMALIE ========== \nLista con anomalie evidenziate: \n");
    markAnomalies(startNode, mean, pam->sensor);
    printList(startNode);
    printf("========== PUNTO E: SCRITTURA FILE ==========\nFile report_anomalie.txt scritto correttamente.\n");
    writeAnomaliesToFile(pam->outputFile, startNode);
    free(pam->inputFile);
    free(pam->outputFile);
    free(pam);
    recursivelyCleanStack(startNode);
    free(startNode);
}