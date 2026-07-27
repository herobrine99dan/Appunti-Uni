#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> //For bool return type
#include <time.h>
const int RADIUS = 100;

bool isPointInCircle(int x, int y)
{
    // assume radius=100
    float dist = pow((x - RADIUS / 2), 2) + pow((y - RADIUS / 2), 2);
    return dist < 2500;
}

float computePi(int iterations)
{
    // Using Montecarlo approximation
    float pointsInCircle = 0;
    for (int i = 0; i < iterations; i++)
    {
        if (isPointInCircle(rand() % RADIUS, rand() % RADIUS))
        {
            pointsInCircle++;
        }
    }
    // Derivazione formula: SuperficieCerchio=pi*r², Superficie quadrato in funzione del raggi=4r²
    // pongo r²=Acerchio/pi ed agisco per sostituzione, Superficiequadrato=4*Superficiecerchio/pi
    return (4.0f * pointsInCircle) / iterations;
}

int main()
{
    srand(time(NULL));
    float mean = 0;
    int totWeights = 0;
    for (int i = 1; i < 1000; i += 10)
    {
        float approximation = computePi(i);
        printf("Con %d iterazioni il pi greco è %f\n", i, approximation);
        mean += approximation* i;
        totWeights += i;
    }
    mean /= totWeights;
    printf("Media del pigreco: %f \n", mean);
}