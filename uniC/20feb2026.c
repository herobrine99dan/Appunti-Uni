#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record
{
    char *eventName;
    char *location;
    int maxAmount;
} Record;

typedef struct LinkedNode
{
    Record *record;
    struct LinkedNode *nextNode;
} LinkedNode;

void recursivelyDelete(LinkedNode *node)
{
    if (node == NULL)
    {
        return;
    }
    recursivelyDelete(node->nextNode);
    free(node->record->eventName);
    free(node->record->location);
    free(node->record);
    free(node);
}

void insert(LinkedNode *startNode, Record *record)
{
    // TODO Use lexicografic order with eventName, with strcmp
    LinkedNode *iterator = startNode;
    while (iterator->nextNode != NULL)
    {
        if (strcmp(record->eventName, iterator->nextNode->record->eventName) > 0)
        {
            iterator = iterator->nextNode;
        }
        else
        {
            break;
        }
    }
    LinkedNode *newNode = calloc(1, sizeof(LinkedNode));
    newNode->record = record;
    newNode->nextNode = iterator->nextNode;
    iterator->nextNode = newNode;
}

void printList(LinkedNode *iterator)
{
    while (iterator != NULL)
    {
        printf("%s  %s  %d \n", iterator->record->eventName, iterator->record->location, iterator->record->maxAmount);
        iterator = iterator->nextNode;
    }
}

LinkedNode *readFileAndBuildList(char *fileName)
{
    LinkedNode *startNode = calloc(1, sizeof(LinkedNode));
    Record rec;
    rec.eventName = "a";
    startNode->record = &rec;
    FILE *filePtr = fopen(fileName, "r");
    char buf[1024];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        char *token = strtok(buf, ";");
        char *eventName = calloc(strlen(token) + 1, sizeof(char));
        strcpy(eventName, token);
        token = strtok(NULL, ";");
        char *location = calloc(strlen(token) + 1, sizeof(char));
        strcpy(location, token);
        token = strtok(NULL, ";");
        int amount = atoi(token);
        Record *record = calloc(1, sizeof(Record));
        record->eventName = eventName;
        record->location = location;
        record->maxAmount = amount;

        insert(startNode, record);
        //  printf("%s\n", buf);
    }
    if (startNode->nextNode == NULL)
    {
        printf("List is empty \n");
        exit(1);
        return NULL;
    }
    LinkedNode *temp = startNode->nextNode;
    free(startNode);
    return temp;
}

int main()
{
    char fileName[] = "./feb2026input.txt";
    LinkedNode *startNode = readFileAndBuildList(fileName);
    printList(startNode);
    recursivelyDelete(startNode);
}