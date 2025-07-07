#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void selection_sort(int list[], int n)
{
    int i, j, least, temp;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[least])
                least = j;
        }
        SWAP(list[i], list[least], temp);
    }
}

void insertion_sort(int list[], int n){
    int i, j, key;
    for(i = 1; i < n; i++){
        key = list[i];
        for(j = i - 1; j >= 0 && list[j] > key; j--){
            list[j+1] = list[j];
        }
        list[j+1] = key;
    }
}

