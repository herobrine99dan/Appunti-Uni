#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int caseOne = 0;
    int caseTwo = 0;
    int caseThree = 0;
    int caseFour = 0;
    int caseFive = 0;
    int caseSix = 0;
    int rolls = 1000000;
    // Mapping parameters→ min(0,1) max(RandMax,6); per problemi di arrotondamento, devo aggiungere 1 nel deltaOrdinate
    double slope = (float)(6 - 1 + 1) / (RAND_MAX - 0);
    double addendum = 1.0f;
    printf("Conversion rate: %.15f\n", slope);
    for (int i = 0; i < rolls; i++)
    {
        int randomRoll = (slope * rand() + addendum); // Alternativa mille volte più efficiente: rand() % max + min
        if (randomRoll == 1)
        {
            caseOne++;
        }
        if (randomRoll == 2)
        {
            caseTwo++;
        }
        if (randomRoll == 3)
        {
            caseThree++;
        }
        if (randomRoll == 4)
        {
            caseFour++;
        }
        if (randomRoll == 5)
        {
            caseFive++;
        }
        if (randomRoll == 6)
        {
            caseSix++;
        }
    }
    printf("Caso uno: %d \n", caseOne);
    printf("Caso due: %d \n", caseTwo);
    printf("Caso tre: %d \n", caseThree);
    printf("Caso quattro: %d \n", caseFour);
    printf("Caso cinque: %d \n", caseFive);
    printf("Caso sei: %d\n ", caseSix);
}