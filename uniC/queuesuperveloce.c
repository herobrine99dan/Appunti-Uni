#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    int val;
    struct LinkedNode *nextNode;
} LinkedNode;

typedef struct Queue
{
    LinkedNode *headNode;
    LinkedNode *tailNode;
} Queue;

/* void enqueue(Queue *queue, int var) 
{Complexity→O(n)
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->val = var;
    if (queue->headNode == NULL)
    {
        queue->headNode = newElem;
        return;
    }
    LinkedNode *lastElement = queue->headNode;
    while (lastElement->nextNode != NULL)
    {
        lastElement = lastElement->nextNode;
    }
    lastElement->nextNode = newElem;
} */

void enqueue(Queue *queue, int var)
{//Complexity O(1)
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->val = var;
    if (queue->headNode == NULL)
    {
        queue->headNode = newElem;
        queue->tailNode = newElem;
        return;
    }
    LinkedNode *lastElement = queue->tailNode;
    lastElement->nextNode = newElem;
    queue->tailNode = newElem;
}

void printQueue(Queue *queue)
{
    LinkedNode *iterator = queue->headNode;
    if (iterator == NULL)
    {
        return;
    }
    while (iterator != NULL)
    {
        printf("%d --> ", iterator->val);
        iterator = iterator->nextNode;
    }
    printf("NULL \n");
}

void recursivelyDelete(LinkedNode* node) {
    if(node == NULL) {
        return;
    }
    recursivelyDelete(node->nextNode);
    free(node);
}

void clean(Queue* q) {
    recursivelyDelete(q->headNode);
}

int main()
{
    Queue *queue = calloc(1, sizeof(Queue));
    for (int i = 1; i < 6; i++)
    {
        enqueue(queue, i);
    }
    printQueue(queue);
    clean(queue);
    free(queue);
}