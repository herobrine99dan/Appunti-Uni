#include <stdio.h>
#include <math.h>

#define length(arr) (sizeof(arr) / sizeof(arr[0]))

void printArray(float arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main()
{
    // customized sort
    int arr[] = {9, 2, 6, 4, 3, 5, 8, 1, 0, 7};
    int n = length(arr);
    float result[10] = {9, 2, 6, 4, 3, 5, 8, 1, 0, 7};
    if(5.0f==5.0f) {
        printf("miao");
    }
    for (int i = 0; i < n; i++)
    {
        // For every element inside the loop, search the smaller element in that index
        float lastMinimum = INFINITY;
        int indexLastMinimum = 0;
        for (int j = 0; j < n; j++)
        {
            if (isnan(result[j]))
            {
                continue;
            }
            float element = result[j];
            if (element < lastMinimum)
            {
                indexLastMinimum = j;
                lastMinimum = element;
            }
        }

        arr[i] = (int)lastMinimum;
        result[indexLastMinimum] = NAN;

    }
    printf("Finished \n");
    for(int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
    // printArray(arr, (int)length(arr));
}