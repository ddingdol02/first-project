#include <stdio.h>

int recursizeSum(int arr[], int index, int size)
{
    if (index == size)
    {
        return 0;
    }
    return arr[index] + recursizeSum(arr, index + 1, size);
}