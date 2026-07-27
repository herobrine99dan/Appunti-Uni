#include <iostream>
using namespace std;

void printArr(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
}

int partition(int arr[], int start, int end) {
int i = start;
int pivot = arr[end];
for(int j = start; j < end; j++) {
if(arr[j]<=pivot){
int temp = arr[j];
arr[j] = arr[i];
arr[i] = temp;
i++;
}
}
int temp = arr[end];
arr[end] = arr[i];
arr[i] = temp;
return i;
}

void quickSort(int arr[], int start, int end) {
if(start>=end) return;
int pivotIndex = partition(arr,start,end);
quickSort(arr, start, pivotIndex-1);
quickSort(arr, pivotIndex+1,end);
}

void merge(int arr[], int start, int center, int end) {
int arrLength = end-start+1;
int* newArr = new int[arrLength];
int sxIndex = start;
int dxIndex = center+1;
int currNewArrPos = 0;
while(sxIndex <= center && dxIndex <= end) {
newArr[currNewArrPos++] = arr[sxIndex] <= arr[dxIndex] ? arr[sxIndex++]: arr[dxIndex++];
}
while(sxIndex <= center) {
newArr[currNewArrPos++] = arr[sxIndex++];
}
while(dxIndex<=end) {
newArr[currNewArrPos++] = arr[dxIndex++];
}
for(int i = 0; i < arrLength; i++) {
arr[start+i] = newArr[i];
}
delete[] newArr;
}

void mergeSort(int arr[], int start, int end) {
if(start >= end) return;
int center = (end + start) / 2;
mergeSort(arr, start, center);
mergeSort(arr, center + 1, end);
merge(arr, start, center, end);
}

void insertionSort(int arr[], int length) {
for(int curr = 0; curr < length; curr++) {
for(int j = curr; j > 0 && arr[j] < arr[j-1]; j--) {
int temp = arr[j-1];
arr[j-1]=arr[j];
arr[j]=temp;
}
}
}

int main()
{
    int arr[] = {6, 9, 2, 5, 3, 7, 8, 4, 1};
    //mergeSort(arr, 0, 8);
insertionSort(arr,9);    
printArr(arr, 9);
    cout << endl;
}
