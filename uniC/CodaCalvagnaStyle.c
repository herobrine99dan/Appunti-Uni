#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *nextPtr;
} Node;

typedef struct Queue
{
    Node *headNode;
    Node *lastNode;
} Queue;

void *customCalloc(size_t __nmemb, size_t __size) {
    void *ptr = calloc(__nmemb, __size);
    if(ptr == NULL) {
        perror("Errore nell'allocazione di memoria \n");
        exit(1);
    }
    return ptr;
}

int poll(Queue* queue) {
    if (queue->headNode == NULL) {
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }

    Node *tempNode = queue->headNode;  // Save the current head
    int val = tempNode->value;         // Save the value to return
    
    queue->headNode = tempNode->nextPtr; // Move head to the next node

    // If the queue is now empty, we must also nullify lastNode
    if (queue->headNode == NULL) {
        queue->lastNode = NULL;
    }

    free(tempNode); // Free the OLD head
    return val;
}

void offer(Queue* queue, int elem) {
    Node *newElem = customCalloc(1, sizeof(Node));
    if (newElem == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    newElem->value = elem;
    newElem->nextPtr = NULL;

    if (queue->lastNode == NULL) {
        // Queue is empty: both head and last point to the new node
        queue->headNode = newElem;
        queue->lastNode = newElem;
    } else {
        // Link the current last node to the new node, then update lastNode
        queue->lastNode->nextPtr = newElem;
        queue->lastNode = newElem;
    }
}

void recursivelyClean(Node* ptr) {
    if(ptr == NULL) {
        return;
    }
    recursivelyClean(ptr->nextPtr);
    free(ptr);
}

void clean(Queue* queue) {
    recursivelyClean(queue->headNode);
}

int main()
{
    Queue* queue = customCalloc(1, sizeof(Queue));
    for(int i = 0; i < 5; i++) {
        offer(queue, i);
    }
    Node* iterator = queue->headNode;
    while(iterator->nextPtr != NULL) {
        printf("Nodo %d\n", iterator->value);
        iterator = iterator->nextPtr;
    }
    clean(queue);
    free(queue);
}