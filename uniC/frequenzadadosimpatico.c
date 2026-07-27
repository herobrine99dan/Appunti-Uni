#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ATTEMPS 3600

int lancioDadi()
{
    return (1 + rand() % 6) + (1 + rand() % 6);
}

int main()
{
    srand(time(NULL));
    // possibile somme: 2,3,4,5,6,7,8,9,10,11,12
    int freq[11] = {0};
    for (int i = 0; i < ATTEMPS; i++)
    {
        freq[lancioDadi() - 2]++; // problema: il nostro array va da 0 a 10, le somme vanno da 2 a 12
    }

    for (int i = 0; i < 11; i++)
    {
        printf("somma: %d, percentuale: %f \n", i + 2, (float)freq[i] / ATTEMPS * 100.0f);
    }
}