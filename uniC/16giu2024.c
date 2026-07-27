#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct param
{
    char *input_file;
    char *output_file;
} param;

typedef struct Persona
{
    char *name;
    char *surname;
    int age;
    int weight;
    int height;
    char gender;
} Persona;

typedef struct LinkedNode
{
    Persona *person;
    struct LinkedNode *nextNode;
} LinkedNode;

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

float imc(Persona *obj)
{
    float heightConverted = obj->height / 100.0f;
    return (float)obj->weight / (heightConverted * heightConverted);
}

/*
- writeFile: funzione per la scrittura del contenuto di una lista su file come specificato nel punto
E.*/

Persona *getMax(LinkedNode *startNode)
{
    LinkedNode *iterator = startNode;
    Persona *max = iterator->person;
    while (iterator != NULL)
    {
        // printf("Iterating, current is %s whose imc is %f\n", iterator->person->name, imc(iterator->person));
        if (imc(iterator->person) > imc(max))
        {
            max = iterator->person;
        }
        iterator = iterator->nextNode;
    }
    return max;
}

void insert(LinkedNode *startNode, Persona *obj)
{
    LinkedNode *newElem = safeCalloc(1, sizeof(LinkedNode));
    newElem->person = obj;
    LinkedNode *iterator = startNode;
    LinkedNode *previous = iterator;
    while (iterator != NULL)
    {
        if (newElem->person->age > iterator->person->age)
        {
            previous = iterator;
        }
        iterator = iterator->nextNode;
    }
    newElem->nextNode = previous->nextNode;
    previous->nextNode = newElem;
}

param *readInput(int argc, char *argv[])
{
    param *pam = safeCalloc(1, sizeof(param));
    if (argc != 3)
    {
        perror("Illegal number of arguments \n");
        exit(1);
    }
    char *clonedInput = safeCalloc(strlen(argv[1]) + 1, sizeof(char));
    char *clonedOutput = safeCalloc(strlen(argv[2]) + 1, sizeof(char));
    strcpy(clonedInput, argv[1]);
    strcpy(clonedOutput, argv[2]);
    if (strcmp(strrchr(argv[1], '.'), ".txt") != 0 || strcmp(strrchr(argv[2], '.'), ".txt") != 0)
    {
        perror("Invalid extension \n");
        exit(1);
    }
    pam->input_file = clonedInput;
    pam->output_file = clonedOutput;
    return pam;
}

void printObject(Persona *obj, FILE *stream)
{
    if (stream == stdout)
    {
        fprintf(stream, "\t %s %s %d %d %d %c \n", obj->name, obj->surname, obj->age, obj->weight, obj->height, obj->gender);
        return;
    }
    fprintf(stream, "%s %s %d %d %d %c \n", obj->name, obj->surname, obj->age, obj->weight, obj->height, obj->gender);
}

void printList(LinkedNode *headNode, FILE *stream)
{
    LinkedNode *iterator = headNode;
    while (iterator != NULL)
    {
        printObject(iterator->person, stream);
        iterator = iterator->nextNode;
    }
}

LinkedNode *readFile(char *inputFile)
{
    Persona *persona = safeCalloc(1, sizeof(Persona));
    LinkedNode *startNode = safeCalloc(1, sizeof(LinkedNode)); // Dummy node
    startNode->person = persona;
    FILE *filePtr = fopen(inputFile, "r");
    if (filePtr == NULL)
    {
        perror("File not available \n");
        exit(1);
    }
    char buf[1024];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        Persona *p = safeCalloc(1, sizeof(Persona));

        char *token = strtok(buf, " "); // Strtok supports also string with multiple spaces, using sscanf we would have to use strange escaping syntax
        if (strlen(token) > 255)
        {
            perror("Name too large \n");
            exit(1);
        }
        char *name = safeCalloc(strlen(token) + 1, sizeof(char));
        strcpy(name, token);
        token = strtok(NULL, " ");
        if (strlen(token) > 255)
        {
            perror("Surname too large \n");
            exit(1);
        }
        char *surname = safeCalloc(strlen(token) + 1, sizeof(char));
        strcpy(surname, token);
        int age, weight, height;

        token = strtok(NULL, " ");
        age = atoi(token);

        token = strtok(NULL, " ");
        weight = atoi(token);

        token = strtok(NULL, " ");
        height = atoi(token);

        token = strtok(NULL, " ");
        char gender = token[0];

        p->name = name;
        p->surname = surname;
        p->age = age;
        p->weight = weight;
        p->height = height;
        p->gender = gender;
        insert(startNode, p);
    }
    fclose(filePtr);
    LinkedNode *next = startNode->nextNode;
    free(startNode->person); // Remove dummy node
    free(startNode);
    return next;
}

void push(LinkedNode **headNode, Persona *obj)
{
    LinkedNode *newNode = safeCalloc(1, sizeof(LinkedNode));
    newNode->person = obj;
    newNode->nextNode = (*headNode);
    *(headNode) = newNode;
}

LinkedNode *removeFromList(LinkedNode *headNode, Persona *obj)
{
    if (headNode->person == obj)
    {
        LinkedNode *returnVal = headNode->nextNode;
        free(headNode);
        return returnVal;
    }
    // Not the first object
    LinkedNode *iterator = headNode;
    LinkedNode *previous = iterator;
    while (iterator != NULL)
    {
        if (iterator->person == obj)
        {
            break;
        }
        previous = iterator;
        iterator = iterator->nextNode;
    }
    LinkedNode *temp = iterator->nextNode;
    previous->nextNode = temp;
    free(iterator);
    return headNode;
}

LinkedNode *processList(LinkedNode **headNodeA)
{
    /*Sposti i tre elementi con più alto indice di
    massa corporea dalla lista A alla lista B.
    Suggerimento: lo spostamento può essere effettuato ripetendo per tre volte le operazioni di
    ricerca dell’elemento con più alto indice di massa corporea, inserimento di copia
    dell’elemento in B e cancellazione dell’elemento da A.*/
    LinkedNode *headNodeB = NULL;
    for (int i = 0; i < 3; i++)
    {
        Persona *max = getMax(*headNodeA);
        *headNodeA = removeFromList(*headNodeA, max);
        push(&headNodeB, max);
    }
    return headNodeB;
}

void recursivelyClean(LinkedNode *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->person->name);
    free(node->person->surname);
    free(node->person);
    recursivelyClean(node->nextNode);
    free(node);
}

void writeFile(char *output_file, LinkedNode *headNode)
{
    FILE *filePtr = fopen(output_file, "w");
    if (filePtr == NULL)
    {
        perror("Unavailable file \n");
        exit(1);
    }
    printList(headNode, filePtr);
    fclose(filePtr);
}

int main(int argc, char *argv[])
{
    param *pam = readInput(argc, argv);
    printf("=======PUNTO A=======\ninput = %s, output = %s\n", pam->input_file, pam->output_file);
    printf("\n=======PUNTO B======= \n");
    LinkedNode *headNode = readFile(pam->input_file);
    printList(headNode, stdout);
    printf("\n=======PUNTO C======= \n");
    printObject(getMax(headNode), stdout);
    printf("\n=======PUNTO D======= \n");
    LinkedNode *headNodeB = processList(&headNode);
    printf("A: \n");
    printList(headNode, stdout);
    printf("B: \n");
    printList(headNodeB, stdout);
    writeFile(pam->output_file, headNodeB);
    recursivelyClean(headNode);
    recursivelyClean(headNodeB);

    free(pam->input_file);
    free(pam->output_file);
    free(pam);
}