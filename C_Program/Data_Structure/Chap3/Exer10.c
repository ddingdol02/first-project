/*
array[]: 원소가 저장된 배열.
n: 배열의 최대 크기.
*items: 현재 배열에 들어있는 원소 개수(포인터로 전달하여 업데이트 가능).
loc: 삭제할 위치(0부터 시작).
*/

void delete(int array[], int n, int *items, int loc) {
    // 배열이 비어있는 경우 예외 처리
    if (*items <= 0) {
        printf("배열이 비어있습니다.\n");
        return;
    }
    // loc이 유효한 범위가 아닌 경우 예외 처리
    if (loc < 0 || loc >= *items) {
        printf("삭제 위치가 잘못되었습니다.\n");
        return;
    }
    // loc 이후의 원소들을 한 칸 앞으로 이동
    for (int i = loc; i < *items - 1; i++) {
        array[i] = array[i + 1];
    }
    // 원소 개수 감소
    (*items)--;
}