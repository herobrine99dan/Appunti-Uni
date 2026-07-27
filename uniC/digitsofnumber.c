#include <stdio.h>
#include <stdlib.h>

char *computeDigits(int n)
{
    int nElements = sizeof(int) * 8 + 1;
    char *arr = (char *)calloc(sizeof(int) * 8 + 1, sizeof(char)); // we want to put \0 at the end
    for (int i = 0; i < nElements; i++)
    {
        arr[i] = '0';
    }
    int i = 0;
    while (n > 0)
    {
        int r = n % 2;
        n /= 2;
        arr[i++] = r == 0 ? '0' : '1';
    }
    for (i = 0; i < (nElements - 1) / 2; i++) //when reversing, divide by two
    { // excluding \0
        char temp = arr[i];
        arr[i] = arr[nElements - 2 - i];
        arr[nElements - 2 - i] = temp;
    }
    for (i = 0; i < nElements - 1; i++)
    {
    }
    arr[32] = '\0';
    return arr;
}

int main()
{
    char* digits = computeDigits(1252);
    printf("digits: %s\n", digits);
    free(digits);
}