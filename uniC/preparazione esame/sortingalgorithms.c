#include <stdio.h>

void printArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int *arr, int len)
{
    // fa risalire come le bolle il numero più piccolo
    for (int step = 0; step < len - 1; step++)
    {
        for (int current = 0; current < len - 1 - step; current++)
        {
            if (arr[current] > arr[current + 1])
            {
                int temp = arr[current];
                arr[current] = arr[current + 1];
                arr[current + 1] = temp;
            }
        }
    }
}

void icantbelieveicansort(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

//https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif
void insertionSort(int *arr, int len) {
    for (int step = 0; step < len; step++) {
        // Partiamo dall'elemento i e lo portiamo indietro finché è minore del precedente
        for (int j = step; j > 0 && arr[j] < arr[j - 1]; j--) {
            // Scambio (Swap)
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void selectionSort(int *arr, int len)
{
    //https://upload.wikimedia.org/wikipedia/commons/9/94/Selection-Sort-Animation.gif
    // Select each time the smallest element available and place it
    for (int step = 0; step < len - 1; step++)
    {
        // Search the smallest number
        int smallestNow = arr[step]; // Assume current is smallest
        int smallestIndex = step;
        for (int j = step; j < len; j++)
        {
            if (arr[j] < smallestNow)
            {
                smallestNow = arr[j];
                smallestIndex = j;
            }
        }
        // Now swap this element with the smallest element
        arr[smallestIndex] = arr[step];
        arr[step] = smallestNow;
    }
}

int main()
{
    int arr[] = {4,8, 9, 2, 3, 1, 6, 7, 5};
    int size = 8;
    bubbleSort(arr, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}