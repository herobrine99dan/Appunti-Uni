#include <stdio.h>

#define LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

int main()
{
    // int arr[] = {0}; // Array con un solo elemento

    // int arr[5] = {0}; // Array con 5 elementi tutti a zero

    // int arr[] = {1, 2, 3, 4, 5}; // Array con 5 elementi

    int voti[] = {1, 4, 2, 3, 5, 1, 2, 5, 4, 3, 2, 1, 2, 3, 5, 3, 1, 2, 4, 5}; // 20 voti da 1 a 5
    int frequenza[5] = {0};
    for (size_t i = 0; i < LENGTH(voti); i++) //Two ways to do the for loop
    {
        frequenza[voti[i] - 1]++;
    }
    // now show them
    for (int i = 0; i < (int) LENGTH(frequenza); i++)
    {
        printf("Il voto %d è stato trovato %d volte. \n", 0 + 1, frequenza[i]);
    }
}