#include <iostream>
using namespace std;

void printArr(int arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int partition(int arr[], int start, int end)
{
    int i = start;
    int pivot = arr[end];
    for (int j = start; j < end; j++)
    {
        if (arr[j] <= pivot)
        {
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
        }
    }

    int temp = arr[end];
    arr[end] = arr[i];
    arr[i] = temp;
    cout << "Partioning ended with pivot " << pivot << endl;
    printArr(arr, 9);
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

void insertionSort(int arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void selectionSort(int arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        int lowestIndex = i;
        for (int j = i; j < arrLength; j++)
        {
            if (arr[j] < arr[lowestIndex])
            {
                lowestIndex = j;
            }
        }
        int temp = arr[lowestIndex];
        arr[lowestIndex] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        bool swapped = false;
        for (int j = 0; j < arrLength; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}

void merge(int arr[], int start, int center, int end)
{
    int arrLength = end - start + 1;
    int *newArr = new int[arrLength];
    int sxIndex = start;
    int dxIndex = center + 1;
    int currNewArrPos = 0;
    while(sxIndex <= center && dxIndex <= end) {
        newArr[currNewArrPos++] = arr[sxIndex] <= arr[dxIndex] ? arr[sxIndex++] : arr[dxIndex++];
    }
    while(sxIndex <= center) {
        newArr[currNewArrPos++] = arr[sxIndex++];
    }
    while(dxIndex <= end) {
        newArr[currNewArrPos++] = arr[dxIndex++];
    }
    for (int i = 0; i < arrLength; i++)
    {
        arr[i + start] = newArr[i];
    }
    delete[] newArr;
}

void mergeSort(int arr[], int start, int end)
{
    if (start >= end)
        return;
    int center = (start + end) / 2;
    mergeSort(arr, start, center);
    mergeSort(arr, center + 1, end);
    merge(arr, start, center, end);
}

int main()
{
    int arr[] = {3, 9, 1, 5, 6, 7, 8, 2, 4};
    mergeSort(arr, 0, 8);
    //selectionSort(arr, 9);
    printArr(arr, 9);
}