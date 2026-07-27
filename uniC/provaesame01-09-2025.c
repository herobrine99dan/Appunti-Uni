#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record
{
    char *input_filename;
    char *output_filename;
} record;

typedef struct Prodotto
{
    int id;
    char *name; // max 100 chars
    int quantity;
    float price;
} Prodotto;

typedef struct LinkedNode
{
    Prodotto value;
    struct LinkedNode *nextNode;
} LinkedNode;

void push(LinkedNode **startNode, Prodotto value)
{
    LinkedNode *newNode = malloc(sizeof(LinkedNode));
    newNode->value.id = value.id;
    newNode->value.name = value.name;
    newNode->value.quantity = value.quantity;
    newNode->value.price = value.price;
    newNode->nextNode = *startNode;
    (*startNode) = newNode;
}

Prodotto pop(LinkedNode **startNode)
{
    LinkedNode *nextElem = (*startNode)->nextNode;
    LinkedNode *temp = (*startNode);
    (*startNode) = nextElem;
    Prodotto tempProdotto = temp->value;
    free(temp);
    return tempProdotto;
}

int printStack(LinkedNode **startNode)
{
    int contatore = 0;
    LinkedNode *iterator = (*startNode);
    while (iterator->nextNode != NULL)
    {
        printf("ID: %d, Nome: %s, Quantita: %d, Prezzo: %f \n", iterator->value.id, iterator->value.name, iterator->value.quantity, iterator->value.price);
        iterator = iterator->nextNode;
        contatore++;
    }
    return contatore;
}

/*
• writeOutput: scrive il contenuto dell'array sul file di output.*/

void sort(Prodotto *arr, int size)
{

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j].price > arr[j + 1].price)
            {
                Prodotto temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        printf("ID: %d, Nome: %s, Quantita: %d, Prezzo: %f \n", arr[i].id, arr[i].name, arr[i].quantity, arr[i].price);
    }
}

void readFileAndFillStack(char *fileName, LinkedNode **startNode)
{
    /*Assumere che il file di input input_filename contenga una serie di righe, ciascuna rappresentante
un prodotto. Ogni riga è formattata come segue, con valori separati da virgole:
ID_Prodotto (intero),Nome_Prodotto (stringa, max 100 char),Quantita (intero),Prezzo (float)
Il programma deve leggere tutti i record relativi ai prodotti dal file e inserirli in una pila (stack). Ogni
elemento della pila sarà una struttura Prodotto. L’inserimento deve avvenire nell’ordine in cui i
prodotti sono letti dal file (il primo prodotto nel file sarà il primo ad essere inserito, trovandosi quindi
in fondo alla pila).
Stampare a schermo il contenuto della pila, dalla cima al fondo.*/
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        fprintf(stderr, "impossibile leggere il file \n");
        exit(1);
    }

    while (!feof(filePtr))
    {
        int id;
        char name[101]; // max 100+1 chars
        char *permanent = calloc(101, sizeof(char));
        int quantity;
        float price;

        fscanf(filePtr, "%d, %99[^,],%d,%f", &id, name, &quantity, &price);
        // printf("ID: %d, Nome: %s, Quantita: %d, Prezzo: %f \n", id, name, quantity, price);
        strcpy(permanent, name);
        Prodotto prod = {};
        prod.id = id;
        prod.name = permanent;
        prod.quantity = quantity;
        prod.price = price;
        push(startNode, prod);
    }
    fclose(filePtr);
}

Prodotto *stackToArray(LinkedNode **startNode, int size)
{
    Prodotto *array = calloc(size, sizeof(Prodotto));
    for (int i = 0; i < size; i++)
    {
        Prodotto prod = pop(&startNode);
        array[i] = prod;
    }
    return array;
}

record decodeParameters()
{
    record result = {0};
    result.input_filename = "prodotti.csv";
    result.output_filename = "report.csv";
    char *ptr = strstr(result.input_filename, ".csv");
    if (ptr == NULL || strlen(result.input_filename) != (ptr - result.input_filename + 4))
    {
        fprintf(stderr, "Estensione non valida file di input \n");
        exit(1);
    }
    ptr = strstr(result.output_filename, ".csv");
    if (ptr == NULL || strlen(result.output_filename) != (ptr - result.output_filename + 4))
    {
        fprintf(stderr, "Estensione non valida file di output \n");
        exit(1);
    }
    return result;
}

void writeOutput(Prodotto *sortedArr, int size, char *output_filename)
{
    FILE *filePtr = fopen(output_filename, "w");
    if (filePtr == NULL)
    {
        fprintf(stderr, "Errore nello scrivere il file! \n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        Prodotto prod = sortedArr[i];
        fprintf(filePtr, "%d, %s, %d, %f \n", prod.id, prod.name, prod.price, prod.quantity);
    }
    fclose(filePtr);
}

void findMinMaxPrice(Prodotto *arr, int size, Prodotto *minPricePtr, Prodotto *maxPricePtr)
{
    Prodotto minPrice = arr[0];
    Prodotto maxPrice = arr[0];
    for (int i = 0; i < size; i++)
    {
        Prodotto current = arr[i];
        if (current.price > maxPrice.price)
        {
            maxPrice = current;
        }
        if (current.price < minPrice.price)
        {
            minPrice = current;
        }
    }
    (*minPricePtr) = minPrice;
    (*maxPricePtr) = maxPrice;
}

int main()
{
    record params = decodeParameters();
    printf("====== Punto 1: Parametri ====== \n");
    printf("File di input: %s \n", params.input_filename);
    printf("File di output: %s \n", params.output_filename);

    /* Prodotto test = {5, "ciao", 5, 0.4};
    Prodotto test1 = {2, "ciao", 5, 0.4};
    Prodotto test2 = {4, "ciao", 5, 0.4};
    push(&startNode, test);
    push(&startNode, test1);
    push(&startNode, test2); */
    printf("====== Punto 2: Lettura File e Caricamento su Pila====== \n");
    LinkedNode *startNode = calloc(sizeof(LinkedNode), 1); // useless first node
    readFileAndFillStack(params.input_filename, &startNode);
    //
    int size = printStack(&startNode);

    printf("====== Punto 3: Ricerca Min/Max Prezzo ====== \n");
    /* pop(&startNode);
    pop(&startNode);
    pop(&startNode);
    pop(&startNode);
    pop(&startNode);
    printStack(&startNode); */

    Prodotto *arr = stackToArray(startNode, size);
    Prodotto minPrice, maxPrice;
    findMinMaxPrice(arr, size, &minPrice, &maxPrice);
    printf("Prodotto con prezzo minimo ID: %d, Nome: %s, Quantita: %d, Prezzo: %f \n", minPrice.id, minPrice.name, minPrice.quantity, minPrice.price);
    printf("Prodotto con prezzo massimo ID: %d, Nome: %s, Quantita: %d, Prezzo: %f \n", maxPrice.id, maxPrice.name, maxPrice.quantity, maxPrice.price);
    printf("====== Punto 4: Array Ordinato per Prezzo ====== \n");
    sort(arr, size);
    printf("====== Punto 5:  Scrittura su File di Output ====== \n");
    writeOutput(arr, size, params.output_filename);
    printf("File scritto correttamente! \n");

    // Clean memory leaks
    for (int i = 0; i < size; i++)
    {
        Prodotto prod = arr[i];
        free(prod.name);
    }
    free(arr);
    printf("Cleaning startnode \n");
}