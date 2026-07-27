#include <iostream>
using namespace std;

void bubbleSort(int *arr, int length)
{
    bool swapped = false;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (arr[j] > arr[i])
            {
                // swapping
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

void selectionSort(int *arr, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        int lowestElemIndex = i;
        for (int j = i; j < lenght; j++)
        {
            if (arr[j] < arr[lowestElemIndex])
            {
                // Swapping
                int temp = arr[j];
                arr[j] = arr[lowestElemIndex];
                arr[lowestElemIndex] = temp;
            }
        }
    }
}

void insertionSort(int *arr, int length)
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

void merge(int *arr, int start, int center, int end)
{
    // Merging di due array ordinati in un array ordinato
    /*Tre cose da fare:
        - seleziono man mano l'elemento più piccolo tra i due array
        - inserisco tutti gli elementi rimanenti della parte sx
        - inserisco tutti gli elementi della parte dx
    */
    int arrLength = end - start + 1;
    int newArr[arrLength];
    int sxIndex = start;
    int dxIndex = center + 1;
    int currPosNewArr = 0;
    // Merging
    while (sxIndex <= center && dxIndex <= end)
    {
        newArr[currPosNewArr++] = arr[sxIndex] <= arr[dxIndex] ? arr[sxIndex++] : arr[dxIndex++];
    }
    // Inserisco gli elementi rimanenti
    while (sxIndex <= center)
    {
        newArr[currPosNewArr++] = arr[sxIndex++];
    }
    while (dxIndex <= end)
    {
        newArr[currPosNewArr++] = arr[dxIndex++];
    }
    for (int i = 0; i < arrLength; i++)
    {
        arr[start + i] = newArr[i];
    }
}

void mergeSort(int *arr, int posStart, int posEnd)
{
    if (posStart >= posEnd)
    {
        return;
    }
    int center = (posStart + posEnd) / 2;
    mergeSort(arr, posStart, center);
    mergeSort(arr, center + 1, posEnd);
    merge(arr, posStart, center, posEnd);
}

void mergeSort(int *arr, int length)
{
    mergeSort(arr, 0, length - 1);
}

int partitionHoare(int *arr, int start, int end) {
    int pivot = arr[start]; // Scegliamo il primo elemento come pivot
    int i = start - 1;
    int j = end + 1;

    while (true) {
        // Muovi i verso destra finché trovi elementi minori del pivot
        do {
            i++;
        } while (arr[i] < pivot);

        // Muovi j verso sinistra finché trovi elementi maggiori del pivot
        do {
            j--;
        } while (arr[j] > pivot);

        // Se gli indici si sono incrociati, abbiamo finito
        if (i >= j) {
            return j; // j sarà il punto di divisione
        }

        // Altrimenti, scambia l'elemento grande a sinistra con quello piccolo a destra
        //swap(&arr[i], &arr[j]); Swapping
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void quickSort(int *arr, int start, int end) {
    if (start < end) {
        int p = partitionHoare(arr, start, end);

        // Attenzione: con Hoare la divisione include il punto 'p'
        quickSort(arr, start, p);
        quickSort(arr, p + 1, end);
    }
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
    // mergeSort(arr, 9);
    quickSort(arr, 0, 8);
    printArr(arr, 9);
    cout << endl;
}