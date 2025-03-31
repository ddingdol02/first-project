// 개선된 순차탐색
int list[100];  // 임의로 설정(추후 변경)

int seq_search2(int key, int low, int high){
    int i;
    list[high + 1] = key;
    for(i=low; list[i] != key; i++) // 키값을 찾으면 종료
        ;
    if(i == (high+1))               // 탐색 실패
        return -1;
    else                            // 탐색 성공
        return i;                   
}