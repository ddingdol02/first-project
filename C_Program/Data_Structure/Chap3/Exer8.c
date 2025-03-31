/* 
array[]: 데이터가 저장된 배열.
n: 배열의 최대 크기.
*items: 현재 배열에 들어있는 원소 개수(포인터로 전달하여 업데이트 가능).
loc: 삽입할 위치(0부터 시작).
value: 삽입할 정수 값.
*/

void insert(int array[], int n, int *items, int loc, int value) {
    // 배열이 꽉 찬 경우 예외 처리
    if (*items >= n) {
        printf("배열이 가득 찼습니다.\n");
        return;
    }
    // loc이 유효한 범위가 아닌 경우 예외 처리
    if (loc < 0 || loc > *items) {
        printf("삽입 위치가 잘못되었습니다.\n");
        return;
    }
    // 뒤에서부터 데이터를 한 칸씩 이동하여 공간 확보
    for (int i = *items; i > loc; i--) {
        array[i] = array[i - 1];
    }
    // 지정된 위치에 value 삽입
    array[loc] = value;
    // 원소 개수 증가
    (*items)++;
}