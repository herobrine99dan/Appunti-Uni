#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define true 1
#define false 0

int main()
{
    srand(time(NULL));
    int number = rand() % 100 + 1;
    while (true)
    {
        printf("Now guess my number... \n");
        int attempt;
        scanf("%d", &attempt);
        if (attempt == number)
        {
            printf("Indovinato, vuoi giocare ancora? y/n \n");
            char c;
            scanf(" %c", &c);
            if (c == 'n')
            {
                printf("Ciao ciao \n");
                return 0;
            }
            else
            {
                number = rand() % 100 + 1;
            }
        }
        else
        {
            char *outcome = attempt > number ? "grande" : "piccolo"; //l'array non me lo fa inizializzare, il pointer si
            printf("Troppo %s, riprova. \n", outcome);
        }
    }
}