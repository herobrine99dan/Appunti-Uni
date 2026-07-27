#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char *caratteri;
} Stringa;

typedef struct
{
    Stringa **elementi;
    size_t righe;
    size_t colonne;
} Matrice;

Stringa StringaRandom(const short);
void InizializzaMatrice(Matrice, const short);
void printMatrix(Matrice);

int main(void)
{
    srand(time(NULL));
    short k, N, M;
    char w;

    printf("%s", "Inserisci k in [10, 15]: ");
    scanf("%hd", &k);

    printf("%s", "Inserisci w in ['a', 'z']: ");
    scanf(" %c", &w);

    printf("%s", "Inserisci N in [4, 8]: ");
    scanf("%hd", &N);

    printf("%s", "Inserisci M in [4, 8]: ");
    scanf("%hd", &M);

    if (!(k <= 15 && k >= 10) || !(w <= 'z' && w >= 'a') || !(N <= 8 && N >= 4) || !(M <= 8 && M >= 4))
    {
        fprintf(stderr, "%s", "E' stato inserito uno o piu' valori invalidi.");
        return -1;
    }

    Stringa **matriceTemp = malloc(N * sizeof(Stringa *));

    for (size_t i = 0; i < N; i++)
        matriceTemp[i] = malloc(M * sizeof(Stringa));

    Matrice matrice = {matriceTemp, N, M};
    InizializzaMatrice(matrice, k);

    printMatrix(matrice);
    
     for(size_t i = 0; i < matrice.righe; i++) {
        for(size_t j = 0; j < matrice.colonne; j++)
            free(matrice.elementi[i][j].caratteri);
    } 

    // Inizio liberazione memoria
     for (size_t i = 0; i < N; i++)
        free(matrice.elementi[i]);
    free(matrice.elementi); 


    // Fine liberazione memoria
    return 0;
}

void InizializzaMatrice(Matrice matrice, const short lunghezza)
{
    for (size_t i = 0; i < matrice.righe; i++)
    {
        for (size_t j = 0; j < matrice.colonne; j++)
        {
            matrice.elementi[i][j] = StringaRandom(lunghezza);
        }
    }
}

Stringa StringaRandom(const short lunghezza)
{
    Stringa stringa = {calloc(lunghezza + 1, sizeof(char))};
    stringa.caratteri[lunghezza] = '\0';

    for (size_t i = 0; i < lunghezza; i++)
        stringa.caratteri[i] = rand() % 26 + 97;

    return stringa;
}

void printMatrix(Matrice matrice)
{
    for (size_t i = 0; i < matrice.righe; i++)
    {
        for (size_t j = 0; j < matrice.colonne; j++)
        {
            printf("%s ", matrice.elementi[i][j].caratteri);
        }
        puts("");
    }
}