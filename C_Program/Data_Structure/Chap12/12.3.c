// 삽입 정렬 함수
void insertion_sort(int list[], int n){
    int i, j, key;
    for(i=0; i<n; i++){
        key = list[i];
        for(j=i-1; j>=0 && list[i]>key; j--)
            list[j+1] = list[j];    // 레코드의 오른쪽 이동
        list[j+1] = key;
    }
}