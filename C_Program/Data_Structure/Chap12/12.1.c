// 선택 정렬 함수
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void selection_sort(int list[], int n){
    int i, j, least, temp;
    for(i=0; i<n-1; i++){
        least = i;
        for(j=i+1; j<n-1; j++)
            if(list[j] < list[least])   // 최소값 탐색
                least = j;
        SWAP(list[i], list[least], temp);
    }
}