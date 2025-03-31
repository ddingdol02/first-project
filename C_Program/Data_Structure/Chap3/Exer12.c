#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 정의: 정수와 문자열을 저장
typedef struct {
    int number;            // 정수
    char str[20];          // 최대 크기 20인 문자열
} Data;

int main() {
    // 동적 메모리 할당: Data 구조체 크기만큼 메모리 할당
    Data *data = (Data *)malloc(sizeof(Data));
    
    // 메모리 할당 실패 처리
    if (data == NULL) {
        fprintf(stderr, "메모리 할당에 실패했습니다.\n");
        return 1;
    }

    // 값 저장
    data->number = 100;                          // 정수 값 100 저장
    strncpy(data->str, "just testing", 19);      // 문자열 "just testing" 저장 (널 문자 포함)

    // 저장된 값 출력
    printf("정수: %d\n", data->number);
    printf("문자열: %s\n", data->str);

    // 동적 메모리 반납
    free(data);

    return 0;
}