#include <stdio.h>

int findMinIndex(int arr[], int start, int end)
{
    if (start == end)
    {
        return start;
    }
    int minIndexInRest = findMinIndex(arr, start + 1, end);
    return (arr[start] < arr[minIndexInRest] ? start : minIndexInRest);
}

void recursiveSelectionSort(int arr[], int start, int size)
{
    if (start >= size - 1)
    {
        return;
    }
    int minIndex = findMinIndex(arr, start, size - 1);
    if (minIndex != start)
    {
        int temp = arr[start];
        arr[start] = arr[minIndex];
        arr[minIndex] = temp;
    }
    recursiveSelectionSort(arr, start + 1, size);
}