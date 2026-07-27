#include <iostream>
#include <cstring>

using namespace std;

void merge(int arr[], int start, int center, int end)
{
    int arrLength = end - start + 1;
    int *newArr = new int[arrLength];
    int sxIndex = start;
    int dxIndex = center + 1;
    int currPosNewArr = 0;
    // Choosing the lowest element among the two sub-sorted-arrays each time
    while (sxIndex <= center && dxIndex <= end)
    {
        newArr[currPosNewArr++] = arr[sxIndex] <= arr[dxIndex] ? arr[sxIndex++] : arr[dxIndex++];
    }
    // Now add all remaining elements
    while (sxIndex <= center)
    {
        newArr[currPosNewArr++] = arr[sxIndex++];
    }
    while (dxIndex <= end)
    {
        newArr[currPosNewArr++] = arr[dxIndex++];
    }
    // now copying, using a for loop but the compiler will probably optimize it to use memcpy
    for (int i = 0; i < arrLength; i++)
    {
        arr[i + start] = newArr[i];
    }

    delete[] newArr;
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        if (arr[j] <= pivot)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    // Place pivot in its correct position
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;
    return i;
}

void quickSort(int arr[], int start, int end)
{
    if (start >= end)
        return;
    int pivotIndex = partition(arr, start, end);
    quickSort(arr, start, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, end);
}

void mergeSort(int arr[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int center = (start + end) / 2;
    mergeSort(arr, start, center);
    mergeSort(arr, center + 1, end);
    merge(arr, start, center, end);
}

void printArr(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
}

int main()
{
    int arr[] = {6, 9, 2, 5, 3, 7, 8, 4, 1};
    // mergeSort(arr, 0, 8);
    quickSort(arr, 0, 8);
    printArr(arr, 9);
    cout << endl;
}