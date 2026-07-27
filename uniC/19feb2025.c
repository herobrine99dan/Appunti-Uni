#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct params
{
    char *alphabet;
    int n;
} params;

typedef struct String
{
    char *s;
} String;

typedef struct LinkedNode
{
    String *s;
    struct LinkedNode *nextNode;
} LinkedNode;

void push(LinkedNode **headNode, String *s)
{
    LinkedNode *newElem = calloc(1, sizeof(LinkedNode));
    newElem->nextNode = *headNode;
    newElem->s = s;
    (*headNode) = newElem;
}

String *pop(LinkedNode **headNode)
{
    LinkedNode *temp = (*headNode);
    (*headNode) = temp->nextNode;
    String *returnval = temp->s;
    free(temp);
    return returnval;
}

unsigned int get_random()
{
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

/* Se la stringa ha una dimensione superiore alla media, viene estratto un elemento dalla pila e
concatenato con la stringa corrente, quindi la stringa risultante viene inserita nella pila.*/
LinkedNode *getStack(String **arrStr, int n, float mean)
{
    LinkedNode *headNode = NULL;
    push(&headNode, arrStr[0]); // Eccezione primo inserimento
    for (int i = 1; i < n; i++)
    {
        if (strlen(arrStr[i]->s) > mean)
        {
            String *current = arrStr[i];
            String *popped = pop(&headNode);
            char *dest = calloc(strlen(current->s) + strlen(popped->s) + 1, sizeof(char));
            strcpy(dest, popped->s);
            strcat(dest, current->s);
            free(current->s);
            current->s = dest;
            push(&headNode, current);
        }
        else
        {
            push(&headNode, arrStr[i]);
        }
    }
    return headNode;
}

float computeAverageLength(String **arrStr, int n)
{
    int size = 0;
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += strlen(arrStr[i]->s);
        size++;
    }
    return sum / size;
}

void writeToFile(LinkedNode **headNode, char *file)
{
    /*Svuoti la pila conservandone il contenuto sul file di output il cui nome è stato
 indicato dall’utente.*/
    FILE *filePtr = fopen(file, "w");
    if (filePtr == NULL)
    {
        fprintf(stderr, "File non scrivibile \n");
        exit(1);
    }
    LinkedNode *iterator = (*headNode);
    while (iterator != NULL)
    {
        fprintf(filePtr, "%s\n", iterator->s->s);
        iterator = iterator->nextNode;
        pop(headNode);
    }
    fclose(filePtr);
}

String *sampleString(char *alphabet, int size)
{
    String *str = calloc(1, sizeof(String));
    str->s = calloc(size + 1, sizeof(char));
    for (int i = 0; i < size; i++)
    {
        str->s[i] = alphabet[get_random() % strlen(alphabet)];
    }
    str->s[size] = '\0';
    return str;
}

String **getStringArray(int *factArray, char *alphabet, int n)
{
    /*Costruisca un array di stringhe B di lunghezza n in cui l’i-esimo elemento sia una
stringa di lunghezza A[i] di caratteri casuali estratti dalla stringa alfabeto fornita in input. Si
calcoli dunque la lunghezza media delle stringhe in B.
Si stampi a schermo il contenuto dell’array B e la lunghezza medi calcolata*/
    String **strarr = calloc(n, sizeof(String));
    for (int i = 0; i < n; i++)
    {
        strarr[i] = sampleString(alphabet, factArray[i]);
    }
    return strarr;
}

int factorial(int i)
{
    if (i == 1 || i == 0)
    {
        return 1;
    }
    return i * factorial(i - 1);
}

int *factorialModArray(int n)
{
    /*Costruisca un array A di lunghezza n e inserisca al suo interno il resto della divisione
    per 101 del fattoriale dell’indice corrispondente: A[i]=i! % 101.
    Si stampi a schermo il contenuto dell’array.*/
    int *arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = factorial(i) % 101;
    }
    return arr;
}

params decodeInput(char *alphabet, int n)
{
    int length = strlen(alphabet);
    if (length < 8 || length > 12)
    {
        fprintf(stderr, "Stringa alfabeto non valida\n");
        exit(1);
    }
    if (n < 3 || n > 12)
    {
        fprintf(stderr, "intero n non valid\n");
        exit(1);
    }
    params p = {alphabet, n};
    return p;
}

int checkExtension(char *file)
{
    char *extension = strstr(file, ".txt");
    if (extension != NULL)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Argomenti mancanti\n");
        exit(1);
    }
    char *file = argv[1]; /*Prenda in input da riga di comando il nome di un file di output (es. output.txt). Il
 programma controlli che tale nome di file abbia estensione “.txt”.*/
    char *alphabet = argv[2];
    int n = atoi(argv[3]);
    params p = decodeInput(alphabet, n);
    alphabet = p.alphabet;
    n = p.n;
    if (checkExtension(file) == 0)
    {
        fprintf(stderr, "estensione non valida\n");
        exit(1);
    }

    printf("=========A======= \n File di output: %s \n Stringa alfabeto: %s , Intero n: %d\n", file, alphabet, n);

    printf("=========B======= \n");
    int *arr = factorialModArray(n);
    for (int i = 0; i < n; i++)
    {
        printf("A[%d] = %d \n", i, arr[i]);
    }
    printf("=========C======= \n");
    String **arrStr = getStringArray(arr, alphabet, n);
    for (int i = 0; i < n; i++)
    {
        printf("B[%d] = %s \n", i, arrStr[i]->s);
    }
    float mean = computeAverageLength(arrStr, n);
    printf("Lunghezza media: %.2f \n", mean);
    printf("=========D=======\n");
    LinkedNode *headNode = getStack(arrStr, n, mean);
    LinkedNode *iterator = headNode;
    while (iterator != NULL)
    {
        printf("%s\n", iterator->s->s);
        iterator = iterator->nextNode;
    }
    printf("=========E=======\n");
    writeToFile(&headNode, file);
    printf("File scritto con successo.\n");
    for (int i = 0; i < n; i++)
    {
        free(arrStr[i]->s);
        free(arrStr[i]);
    }
    free(arrStr);
    free(arr);
}