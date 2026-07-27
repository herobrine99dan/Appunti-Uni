#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    int n;
    struct LinkedNode *nextNode;
} LinkedNode;

int size(LinkedNode *iterator)
{
    int s = 0;
    while (iterator != NULL)
    {
        s++;
        iterator = iterator->nextNode;
    }
    return s;
}

int get(LinkedNode *iterator, int index)
{
    int s = 0;
    while (iterator != NULL)
    {
        if (s == index)
        {
            return iterator->n;
        }
        s++;
        iterator = iterator->nextNode;
    }
    fprintf(stderr, " Valore non trovato\n");
    exit(1);
}

void set(LinkedNode *iterator, int index, int integer)
{
    int s = 0;
    while (iterator != NULL)
    {
        if (s == index)
        {
            iterator->n = integer;
            return;
        }
        s++;
        iterator = iterator->nextNode;
    }
    fprintf(stderr, " Valore non trovato\n");
    exit(1);
}

void selectionSortLinkedListSlowest(LinkedNode *startNode)
{
    for (int i = 0; i < size(startNode); i++)
    {
        int smallIndex = i;
        for (int curr = i; curr < size(startNode); curr++)
        {
            if (get(startNode, curr) < get(startNode, smallIndex))
            {
                smallIndex = curr;
            }
        }
        int temp = get(startNode, i);
        set(startNode, i, get(startNode, smallIndex));
        set(startNode, smallIndex, temp);
    }
}

void selectionSortLinkedListMedium(LinkedNode *startNode)
{
    int sizeN = size(startNode);
    LinkedNode *iterator = startNode;
    for (int i = 0; i < sizeN; i++)
    {
        LinkedNode *smallestElement = iterator;
        LinkedNode *currIterator = iterator;
        for (int curr = i; curr < sizeN; curr++)
        {
            if (currIterator->n < smallestElement->n)
            {
                smallestElement = currIterator;
            }
            currIterator = currIterator->nextNode;
        }
        // Swap
        int temp = iterator->n;
        iterator->n = smallestElement->n;
        smallestElement->n = temp;

        iterator = iterator->nextNode;
    }
}

void bubbleSortLinkedList(LinkedNode *startNode)
{
    int sizeN = size(startNode);
    for (int i = 0; i < sizeN - 1; i++)
    {
        LinkedNode *innerIterator = startNode;
        for (int j = 0; j < sizeN - 1 - i; j++)
        {
            if (innerIterator->n > innerIterator->nextNode->n)
            {
                int temp = innerIterator->n;
                innerIterator->n = innerIterator->nextNode->n;
                innerIterator->nextNode->n = temp;
            }
            innerIterator = innerIterator->nextNode;
        }
    }
}

void insertInOrder(LinkedNode *startNode, int element)
{
    LinkedNode *previous = NULL;
    LinkedNode *iterator = startNode;
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    while (iterator != NULL)
    {
        if (element < iterator->n)
        {
            break;
        }
        previous = iterator;
        iterator = iterator->nextNode;
    }
    newElem->n = element;
    newElem->nextNode = iterator;
    previous->nextNode = newElem;
}

void printList(LinkedNode *iterator)
{
    while (iterator != NULL)
    {
        printf("%d ---> ", iterator->n);
        iterator = iterator->nextNode;
    }
    printf("NULL \n");
}

void recursivelyClean(LinkedNode *startNode)
{
    if (startNode->nextNode == NULL)
    {
        return;
    }
    recursivelyClean(startNode->nextNode);
    free(startNode->nextNode);
}

void insertionSortLinkedList(LinkedNode *startNode)
{
    int sizeN = size(startNode);
    for (int i = 0; i < sizeN; i++)
    {
        for (int j = i; j > 0 && get(startNode, j) < get(startNode, j - 1); j--)
        {
            int temp = get(startNode, j);
            set(startNode, j, get(startNode, j - 1));
            set(startNode, j - 1, temp);
        }
    }
}

int main()
{
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode));
    startNode->n = -10000;
    insertInOrder(startNode, 1);
    insertInOrder(startNode, 7);
    insertInOrder(startNode, 2);
    insertInOrder(startNode, 3);
    insertInOrder(startNode, 5);
    insertInOrder(startNode, 6);
    insertInOrder(startNode, 4);
    insertInOrder(startNode, 8);
    insertInOrder(startNode, 9);

    LinkedNode *temp = startNode->nextNode;
    free(startNode);
    startNode = temp;

    printf("List normally sorted: ");
    printList(startNode);

    printf("List Manually sorted: ");
    insertionSortLinkedList(startNode);
    printList(startNode);

    recursivelyClean(startNode);
    free(startNode);
}