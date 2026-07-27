#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct params
{
    char *inputFile;
    char *outputFile;
} params;

typedef struct String
{
    char *string;
} String;

typedef struct LinkedNode
{

    char *string;
    struct LinkedNode *nextNode;
} LinkedNode;

void append(LinkedNode *headNode, char *string)
{
    LinkedNode *iterator = headNode;
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->string = string;
    while (iterator->nextNode != NULL)
    {
        iterator = iterator->nextNode;
    }
    iterator->nextNode = newElem;
}

char *pop(LinkedNode **headNode)
{
    LinkedNode *temp = (*headNode)->nextNode;
    char *temp1 = (*headNode)->string;
    free((*headNode));
    (*headNode) = temp;
    return temp1;
}

/*
- writeToFile: funzione che scrive il contenuto dell'array R sul file di output.*/

void writeToFile(String **arr, char *file, int size)
{
    /*Scriva il contenuto dell'array R su un file di testo indicato da output_filename, una
    stringa per riga. Nota: gestire opportunamente i casi in cui i file non possono essere
    correttamente aperti in lettura o scrittura stampando un errore sullo standard error e
    terminando l'esecuzione del programma.*/
    FILE *filePtr = fopen(file, "w");
    if (filePtr == NULL)
    {
        fprintf(stderr, "Impossibile accedere al file \n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(filePtr, "%s\n", arr[i]->string);
    }
    fclose(filePtr);
}

char* removeNewLineChars(char* string) {
    int size = strlen(string);
    for (int i = 0; i < size; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
    return string;
}

char *invertString(char *string)
{
    int size = strlen(string);
    int j = size - 1;
    for (int i = 0; i < size / 2; i++)
    {
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
        j--;
    }
    return string;
}

int sizeN(LinkedNode *startNode)
{
    int i = 0;
    LinkedNode *iterator = startNode;
    // printf("popping %s\n", pop(&headNode));
    while (iterator != NULL)
    {
        i++;
        iterator = iterator->nextNode;
    }
    return i;
}

void recursivelyDelete(LinkedNode *iterator)
{
    if (iterator == NULL)
    {
        return;
    }
    recursivelyDelete(iterator->nextNode);
    free(iterator);
}

String **sortQueueToArray(LinkedNode **headNode)
{
    int size = sizeN(*headNode);
    String **arr = calloc(size, sizeof(String));
    LinkedNode *iterator = *headNode;
    /*[7 punti] Svuoti la coda Q, inserendo le stringhe in un nuovo array di stringhe R. Le stringhe
    devono essere ordinate in ordine lessicografico ascendente all'interno dell'array R. Utilizzi
    l'algoritmo bubble sort per l'ordinamento.
    Si stampi a schermo il contenuto dell'array R.*/
    int i = 0;
    while (iterator != NULL)
    {
        String *s = calloc(1, sizeof(String));
        s->string = iterator->string;
        arr[i++] = s;
        iterator = iterator->nextNode;
    }
    recursivelyDelete(iterator);
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (strcmp(arr[j]->string, arr[j + 1]->string) > 0)
            {
                String *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return arr;
}

int stringLength(char *arr)
{
    int i = 0;
    while (arr[i] != '\0' && arr[i] != 10)
    {
        i++;
    }
    return i;
}

void processQueue(LinkedNode **headNode)
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
        LinkedNode *tempNext = iterator->nextNode;
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

LinkedNode *readFileToQueue(char *inputFile)
{
    LinkedNode *headNode = NULL;
    FILE *filePtr = fopen(inputFile, "r");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non leggibile \n");
        exit(1);
    }
    char buf[50];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        char *cloned = calloc(51, sizeof(char));
        strcpy(cloned, buf);
        if (headNode == NULL)
        {
            headNode = calloc(1, sizeof(LinkedNode));
            removeNewLineChars(cloned);
            headNode->string = cloned;
            continue;
        }
        append(headNode, removeNewLineChars(cloned));
    }

    fclose(filePtr);
    return headNode;
}

params decodeParameters(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong number of arguments \n");
        exit(1);
    }
    char *clonedInputF = calloc(strlen(argv[1]) + 1, sizeof(char)); // Necessary because strrchr edits the string
    strcpy(clonedInputF, argv[1]);

    char *clonedOutputF = calloc(strlen(argv[2]) + 1, sizeof(char));
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

int main(int argc, char *argv[])
{
    params pam = decodeParameters(argc, argv);
    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n", pam.inputFile, pam.outputFile);

    printf("======B Contenuto della Coda Q (iniziale)====== \n");
    LinkedNode *headNode = readFileToQueue(pam.inputFile);

    LinkedNode *iterator = headNode;
    // printf("popping %s\n", pop(&headNode));
    while (iterator != NULL)
    {
        printf("%s\n", iterator->string);
        iterator = iterator->nextNode;
    }
    printf("======C Contenuto della Coda Q (dopo manipolazione)====== \n");
    processQueue(&headNode);
    iterator = headNode;
    while (iterator != NULL)
    {
        printf("%s\n", iterator->string);
        iterator = iterator->nextNode;
    }
    printf("======D Contenuto dell'array R (ordinato)====== \n");
    int size = sizeN(headNode);
    String **arr = sortQueueToArray(&headNode);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", arr[i]->string);
    }
    printf("======E Scrittura file output (risultato.txt)======\n");
    writeToFile(arr, pam.outputFile, size);
    printf("File scritto correttamente.\n");
    recursivelyDelete(headNode);
    for (int i = 0; i < size; i++)
    {
        free(arr[i]->string);
        free(arr[i]);
    }
    free(arr);
    free(pam.inputFile);
    free(pam.outputFile);
}