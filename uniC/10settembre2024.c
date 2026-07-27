#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct params
{
    char *in_filename;
    char *out_filename;
    char c;
} params;

typedef struct LinkedNode
{
    char c;
    struct LinkedNode *nextNode;
} LinkedNode;

void *safeCalloc(size_t __nmemb, size_t __size)
{
    void *returnVal = calloc(__nmemb, __size);
    if (returnVal == NULL)
    {
        perror("Allocazione non disponibile");
        exit(1);
    }
    return returnVal;
}

void addLast(LinkedNode *startNode, char c)
{
    LinkedNode *iterator = startNode;
    while (iterator->nextNode != NULL)
    {
        iterator = iterator->nextNode; // Get the tail of the list
    }
    LinkedNode *newNode = safeCalloc(1, sizeof(LinkedNode));
    newNode->c = c;
    iterator->nextNode = newNode;
}

int countOccurrences(LinkedNode *iterator, char c)
{
    int o = 0;
    while (iterator != NULL)
    {
        if (iterator->c == c)
        {
            o++;
        }
        iterator = iterator->nextNode;
    }
    return o;
}

LinkedNode *readFile(char *in_filename)
{
    /*Si assuma che il file di testo contenuto al percorso indicato da filename contenga un
numero non noto di righe, ciascuna contenente una lettera dell’alfabeto. Il programma legga
il contenuto del file e inserisca le lettere dell’alfabeto in una lista concatenata di caratteri L.
Si stampi a schermo il contenuto della lista L*/
    LinkedNode *startNode = NULL;
    FILE *filePtr = fopen(in_filename, "r");
    if (filePtr == NULL)
    {
        perror("File non accessibile \n");
        exit(1);
    }
    char buf[8];
    while (fgets(buf, sizeof buf, filePtr) != NULL)
    {
        if (startNode == NULL)
        {
            startNode = safeCalloc(1, sizeof(LinkedNode));
            startNode->c = buf[0];
        }
        else
        {
            addLast(startNode, buf[0]);
        }
    }

    fclose(filePtr);
    return startNode;
}

params *decodeParameters(int argc, char *argv[])
{
    /* Prenda in input da riga di comando un parametro stringa in_filename che contenga
    un nome di file di input (ad esempio “input”), un parametro stringa out_filename che contenga
    un nome di file di output (ad esempio “output”) e un parametro carattere c. Si assuma una
    lunghezza massima per i nomi dei file di 50 caratteri.
    Si stampino a schermo i valori dei parametri presi in input.*/
    if (argc != 4)
    {
        perror("Illegal number of arguments\n");
        exit(1);
    }
    char *in_filename = argv[1];
    char *out_filename = argv[2];
    if (strlen(in_filename) > 51 || strlen(out_filename) > 51)
    {
        perror("\n");
        exit(1);
    }
    char c = argv[3][0];
    char *in_filenameClone = safeCalloc(strlen(in_filename) + 1, sizeof(char));
    strcpy(in_filenameClone, in_filename);
    char *out_filenameClone = safeCalloc(strlen(out_filename) + 1, sizeof(char));
    strcpy(out_filenameClone, out_filename);
    params *pam = safeCalloc(1, sizeof(params));
    pam->c = c;
    pam->in_filename = in_filenameClone;
    pam->out_filename = out_filenameClone;
    return pam;
}

int detectAndRemove(LinkedNode **startNode, int o)
{
    LinkedNode *iterator = (*startNode);
    LinkedNode *previous = (*startNode);
    int index = 0;
    while (iterator != NULL)
    {
        int p = countOccurrences(*startNode, iterator->c);
        if (p >= o)
        {
            if(index == 0) { //primo elemento, aggiorna il puntatore startNode
                LinkedNode* temp = *startNode;
                *startNode = temp->nextNode;
                free(temp);
            } else {
                LinkedNode* temp = iterator;
                previous->nextNode = iterator->nextNode;
                free(temp);
            }
            // Cancella il carattere corrente e ricomincia a scorrere
            return 1;
        }
        previous = iterator;
        iterator = iterator->nextNode;
        index++;
    }
    return 0;
}

void processL(LinkedNode **startNode, int o)
{
    /*Scorra la lista L dalla testa alla coda. Per ciascun elemento e conti il suo numero
di occorrenze p all’interno della lista, nel suo stato corrente. Se il numero di occorrenze trovato
p è inferiore a o, continui a scorrere la lista, altrimenti cancelli il carattere corrente "e" e
ricominci a scorrere la lista dalla testa alla coda. Il processo termina quando la lista è stata
attraversata dalla testa alla coda senza nessuna cancellazione.*/
    while (detectAndRemove(startNode, o) != 0)
    {
    }
}

void writeToFile(LinkedNode *iterator, char *out_filename)
{
    FILE *filePtr = fopen(out_filename, "w");
    if (filePtr == NULL)
    {
        perror("File non accessibile \n");
        exit(1);
    }
    while (iterator != NULL)
    {
        fprintf(filePtr, "%c", iterator->c);
        iterator = iterator->nextNode;
    }
    fclose(filePtr);
}

void printList(LinkedNode *iterator)
{
    if (iterator == NULL || iterator->nextNode == NULL)
    {
        perror("Lista vuota \n");
        exit(1);
    }
    printf("Contenuto della lista:\n");
    while (iterator != NULL)
    {
        printf("%c", iterator->c);
        iterator = iterator->nextNode;
    }
    printf("\n");
}

void recursivelyClean(LinkedNode* startNode) {
    if(startNode != NULL) {
        recursivelyClean(startNode->nextNode);
    }
    free(startNode);
}

int main(int argc, char *argv[])
{
    params *pam = decodeParameters(argc, argv);
    printf("==========PUNTO A==========\nNome del file di input: %s\nNome del file %s: output\nValore di c: %c\n", pam->in_filename, pam->out_filename, pam->c);
    printf("\n==========PUNTO B==========\n");
    LinkedNode *startNode = readFile(pam->in_filename);
    printList(startNode);
    printf("==========PUNTO C========== \n");
    int o = countOccurrences(startNode, pam->c);
    printf("Occorrenze di A in L: %d\n", o);
    printf("==========PUNTO D==========\n");
    processL(&startNode, o);
    printList(startNode);

    
    // TODO Remove memory leaks
    writeToFile(startNode, pam->out_filename);

    recursivelyClean(startNode);
    free(pam->in_filename);
    free(pam->out_filename);
    free(pam);
}