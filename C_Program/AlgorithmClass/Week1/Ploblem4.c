#include <stdio.h>
#include <stdlib.h>

void flip(int arr[], int k){
    if (k <= 1)
        return;
    int temp = arr[0];
    arr[0] = arr[k - 1];
    arr[k - 1] = temp;
    if (k > 2)
        flip(arr + 1, k - 2);
}
int findMaxIndex(int arr[], int n, int idx, int currMaxIdx){
    if (idx >= n)
        return currMaxIdx;
    if (arr[idx] > arr[currMaxIdx])
        currMaxIdx = idx;
    return findMaxIndex(arr, n, idx + 1, currMaxIdx);
}
void pancakeSort(int arr[], int n)
{
    if (n <= 1)
        return;
    int maxIdx = findMaxIndex(arr, n, 1, 0);
    if (maxIdx != n - 1){
        if (maxIdx != 0)
            flip(arr, maxIdx + 1);
        flip(arr, n);
    }
    pancakeSort(arr, n - 1);
}