// 순환 호출을 이용한 이진탐색
int list[100];  // 임의로 설정(추후 변경)

int search_binary(int key, int low, int high){
    int middle;
    if(low<=high){
        middle = (low + high) / 2;
        if(key == list[middle])     // 탐색 성공
            return middle;  
        else if(key<list[middle])   // 왼쪽 부분리스트 탐색
            return search_binary(key, low, middle - 1); 
        else                        // 오른쪽 부분리스트 탐색
            return search_binary(key, middle + 1, high);
    }
    return -1;                      // 탐색 실패
}