#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[])
{
    int size = 5;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[])
{
    int size = 5;
    for (int i = 0; i < size; i++)
    {
        int minimumIndex = i;
        for (int j = i; j < size; j++)
        {
            if (arr[j] < arr[minimumIndex])
            {
                minimumIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minimumIndex];
        arr[minimumIndex] = temp;
    }
}

void insertionSort(int arr[])
{
    int size = 5;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void printArr(int arr[])
{
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {1, 5, 2, 3, 4};
    printArr(arr);
    selectionSort(arr);
    printArr(arr);
}