#include <iostream>

using namespace std;

void insertionSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            // Swapping
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void selectionSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        int lowestIndex = i;
        for (int j = i; j < length; j++)
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

void printArr(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << ",";
    }
}

int main()
{
    int arr[] = {1, 5, 2, 4, 3};
    mergeSort(arr, 0, 5 - 1);
    printArr(arr, 5);
    cout << endl;
}