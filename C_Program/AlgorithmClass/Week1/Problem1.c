#include <stdio.h>

int findMin(int arr[], int index, int size)
{
    if (index == size - 1)
    {
        return arr[index];
    }
    int minInRest = findMin(arr, index + 1, size);
    return (arr[index] < minInRest) ? arr[index] : minInRest;
}