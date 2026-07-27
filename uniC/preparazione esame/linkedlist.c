#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    int n;
    struct LinkedNode *nextNode;
} LinkedNode;

void addLast(LinkedNode *startNode, int element)
{
    // we need to search the last element in the list
    LinkedNode *lastElement = startNode;
    while (lastElement->nextNode != NULL)
    {
        lastElement = lastElement->nextNode;
    }

    printf("Pointer: %p \n", (void *)lastElement);
    // I've found the last element
    LinkedNode *newElement = malloc(sizeof(LinkedNode));
    newElement->n = element;
    newElement->nextNode = NULL;
    lastElement->nextNode = newElement;
}

// QUEUE Functions:

void offer(LinkedNode *startNode, int element)
{
    addLast(startNode, element);
}

int peek(LinkedNode *startNode)
{
    return startNode->n;
}

int poll(LinkedNode **startNode)
{
    int returnValue = (*startNode)->n;
    LinkedNode *tempNext = (*startNode)->nextNode;
    free(*startNode);      // Cancello il primo elemento dalla memoria
    *startNode = tempNext; // E lo sostituisco con quello dopo
    return returnValue;
}

// STACK Functions:

// Peek is implemented later

int pop(LinkedNode **startNode)
{ // Pops the first element, it's equal to poll
    return poll(startNode);
}

//TODO Eventualmente add(int index) e remove(int index)

void push(LinkedNode **startNode, int element)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->n = element;
    newElem->nextNode = *startNode;
    //update the startNode
    *startNode = newElem;
}

// Clean functions

void removeAll(LinkedNode *startNode)
{
    if (startNode->nextNode != NULL)
    {
        removeAll(startNode->nextNode);
        printf("Freeing: %p \n", (void *)startNode->nextNode);
        free(startNode->nextNode);
    }
}

int size(LinkedNode *startNode)
{
    int counter = 0;
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        counter++;
        iterator = iterator->nextNode;
    }
    return counter;
}

void stackTest() {
    printf("Now working as a stack. \n");
    LinkedNode* startNode = malloc(sizeof(LinkedNode));
    startNode->nextNode = NULL;
    startNode->n = 5;
    for (int i = 0; i < 10; i++)
    {
        push(&startNode, i);
    }
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        printf("Iterating again: %d\n", iterator->n);
        iterator = iterator->nextNode;
    }
    removeAll(startNode);
    free(startNode);
}

void queueTest() {
    // Create a linkedlist and use it as a queue
    LinkedNode *startNode = malloc(sizeof(LinkedNode));
    startNode->nextNode = NULL;
    startNode->n = 5;
    for (int i = 0; i < 10; i++)
    {
        offer(startNode, i);
    }
    printf("Size is: %d \n", size(startNode));
    printf("Polling I get: %d \n", poll(&startNode));
    printf("(ora non printo il valore 5, non c'è più) \n");

    // Iterating through the linked list without knowing the length
    LinkedNode *iterator = startNode;
    while (iterator != NULL)
    {
        printf("Iterating again: %d\n", iterator->n);
        iterator = iterator->nextNode;
    }
    // cleanMemory
    removeAll(startNode);
    free(startNode);
}

int main()
{
   // queueTest();
    stackTest();
}