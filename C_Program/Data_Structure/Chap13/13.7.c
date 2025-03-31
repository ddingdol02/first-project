// 보간 탐색
int list[100];  // 임의로 설정(추후 변경)

int interpol_search(int key, int n){
    int low, high, j;
    low = 0;
    high = n-1;
    while((list[high] >= key) && (key > list[low])){
        j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
        if(key > list[j])
            low = j + 1;
        else if(key < list[j])
            high = j - 1;
        else
            low = j;
    }
    if(list[low] == key)    // 탐색 성공
        return(low);
    else                    // 탐색 실패
        return -1;
}