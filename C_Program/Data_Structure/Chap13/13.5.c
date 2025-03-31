// 반복을 이용한 이진탐색
int list[100];  // 임의로 설정(추후 변경)

int search_binary2(int key, int low, int high){
    int middle;
    while(low <= high){     // 아직 순자들이 남아 있다면
        middle = (low + high) / 2;
        if(key == list[middle])
            return middle;
        else if(key > list[middle])
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;              // 발견되지 않음
}