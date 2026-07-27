#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct params
{
    char *input_file;
    char *output_file;
} params;

typedef struct LinkedNode
{
    char *str;
    struct LinkedNode *nextNode;
} LinkedNode;

void *safeCalloc(int i, int k)
{
    void *rb = calloc(i, k);
    if (rb == NULL)
    {
        perror("Not enough memory \n");
        exit(1);
    }
    return rb;
}

void writeToFile(char *output, LinkedNode *startNode)
{
    FILE *filePtr = fopen(output, "w");
    if (filePtr == NULL)
    {
        perror("File non leggibile \n");
        exit(1);
    }
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        fprintf(filePtr, "%s\n", iterator->str);
        iterator = iterator->nextNode;
    }
    fclose(filePtr);
}

params *decodeParameters(int argc, char *argv[])
{

    if (argc != 3)
    {
        perror("Illegal number of arguments \n");
        exit(1);
    }
    char *input_filename = argv[1];
    char *output_filename = argv[2];
    char *inputClone = safeCalloc(strlen(input_filename) + 1, sizeof(char));
    strcpy(inputClone, input_filename);
    char *outputClone = safeCalloc(strlen(output_filename) + 1, sizeof(char));
    strcpy(outputClone, output_filename);
    if (strcmp(strrchr(input_filename, '.'), ".text") != 0 || strcmp(strrchr(output_filename, '.'), ".output") != 0)
    {
        perror("Invalid extension \n");
        exit(1);
    }
    params *pam = safeCalloc(1, sizeof(params));
    pam->input_file = inputClone;
    pam->output_file = outputClone;
    return pam;
}

void removeWhiteLine(char *str)
{
    char c = *str;
    int index = 0;
    while (c != '\0')
    {
        if ((int)c == 10)
        {
            c = '\0';
            str[index - 1] = '\0';
            return;
        }
        c = str[index++];
    }
}

int sizeList(LinkedNode *startNode)
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

int countVowels(char *str)
{
    int i = 0;
    char c = str[0];
    int index = 0;
    while (c != '\0')
    {
        c = str[index];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            //            printf("vowel: %c\n", c);
            i++;
        }
        index++;
    }
    // printf("Vowels in %s are %d \n", str, i);
    return i;
}

short *getArray(LinkedNode *startNode, int size)
{
    short *arr = safeCalloc(size, sizeof(short));
    for (int i = 0; i < size; i++)
    {
        arr[i] = countVowels(startNode->str);
        startNode = startNode->nextNode;
    }
    return arr;
}

void printList(LinkedNode *startNode)
{
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        printf("%s\n", iterator->str);
        iterator = iterator->nextNode;
    }
}

LinkedNode *removeFromList(LinkedNode **startNode, LinkedNode *object)
{
    LinkedNode *iterator = *startNode;
    LinkedNode *previous = NULL;
    while (iterator != NULL)
    {
        if (iterator == object)
        {
            break;
        }
        previous = iterator;
        iterator = iterator->nextNode;
    }
    LinkedNode *nextNode = iterator->nextNode;
    if (previous == NULL)
    {
        // Remove the first node, the head node
        free(iterator->str);
        free(iterator);
        *startNode = nextNode;
        return nextNode;
    }
    free(iterator->str);
    free(iterator);
    previous->nextNode = nextNode;
    return nextNode;
}

void filterList(LinkedNode **startNode, short *arr, float mean)
{
    LinkedNode *iterator = *startNode;
    int indexStr = 0;
    while (iterator != NULL)
    {
        if (arr[indexStr] > mean)
        {
            // printf("%s Should be removed\n", iterator->str);
            indexStr++;
            iterator = removeFromList(startNode, iterator);
            continue;
        }
        indexStr++;
        iterator = iterator->nextNode;
    }
}

void insert(LinkedNode *startNode, char *str)
{
    int len = strlen(str);
    LinkedNode *newElem = safeCalloc(1, sizeof(LinkedNode));
    newElem->str = str;
    // Instead of searching the last element, we search the last element whose string's length is lower than the current
    LinkedNode *iterator = startNode;
    LinkedNode *previous = iterator;
    while (iterator != NULL)
    {
        if (len > (int)strlen(iterator->str))
        {
            previous = iterator;
        }
        iterator = iterator->nextNode;
    }
    newElem->nextNode = previous->nextNode;
    previous->nextNode = newElem;
}

LinkedNode *readFile(char *file)
{
    /*Il programma
legge queste stringhe e le inserisce in una lista concatenata X in ordine di lunghezza crescente.
Si stampi a schermo il contenuto della lista X.*/
    LinkedNode *startNode = safeCalloc(1, sizeof(LinkedNode)); // Using a dummy node
    startNode->str = "";                                       // Empty string, it is on the stack
    FILE *filePtr = fopen(file, "r");
    if (filePtr == NULL)
    {
        perror("File unaccessible \n");
        exit(1);
    }
    char buf[1024];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        char *clonedStr = safeCalloc(strlen(buf) + 1, sizeof(char));
        strcpy(clonedStr, buf);
        removeWhiteLine(clonedStr);
        insert(startNode, clonedStr);
    }
    fclose(filePtr);
    // Replace dummy node
    LinkedNode *dummyNode = startNode;
    startNode = startNode->nextNode;
    free(dummyNode);
    return startNode;
}

float getMean(short *arr, int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum / (float)size;
}

void recursivelyClean(LinkedNode *startNode)
{
    if (startNode == NULL)
    {
        return;
    }
    recursivelyClean(startNode->nextNode);
    free(startNode->str);
    free(startNode);
}

int main(int argc, char *argv[])
{
    params *pam = decodeParameters(argc, argv);
    printf("====== A Stampa Parametri ====== \ninput_filename = %s\noutput_filename = %s\n", pam->input_file, pam->output_file);
    printf("====== B Lista ordinata per lunghezza ====== \n");
    LinkedNode *startNode = readFile(pam->input_file);
    printList(startNode);
    printf("====== C Array Y (numero di vocali) ====== \n");
    int size = sizeList(startNode);
    short *arr = getArray(startNode, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    float mean = getMean(arr, size);
    printf("====== D Media di Y e lista dopo filtro ======\nMedia di Y: %.1f\nContenuto di X:\n", mean);
    filterList(&startNode, arr, mean);
    printList(startNode);

    writeToFile(pam->output_file, startNode);
    recursivelyClean(startNode);
    free(arr);
    free(pam->input_file);
    free(pam->output_file);
    free(pam);
}