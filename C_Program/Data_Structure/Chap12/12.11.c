#include <stdio.h>
#include <string.h>

#define SWAP(x, y)   do { element t = (x); (x) = (y); (y) = t; } while(0)  // temp를 매크로 내부에서 정의

#define MAX_WORD_SIZE 50
#define MAX_MEANING_SIZE 500
#define SIZE 5

typedef struct {
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
} element;

element list[SIZE]; // 구조체 배열의 선언

int main(void) {
    int i, j;

    printf("5개의 단어와 의미를 입력하시오\n");

    for (i = 0; i < SIZE; i++) {
        scanf("%s", list[i].word);     // 엔터키남을 제외하고 받는다.
        scanf(" %[^\n]", list[i].meaning); // 의미를 공백을 포함하여 받기 위해 수정
    }

    // 버블 정렬
    for (i = 0; i < SIZE - 1; ++i) {
        for (j = i + 1; j < SIZE; ++j) {
            if (strcmp(list[i].word, list[j].word) > 0) {
                SWAP(list[i], list[j]);  // 매크로 사용
            }
        }
    }

    printf("\n정렬 후 사전의 내용: \n");
    for (i = 0; i < SIZE; i++) {
        printf("%s: %s \n", list[i].word, list[i].meaning);
    }
    return 0;
}
