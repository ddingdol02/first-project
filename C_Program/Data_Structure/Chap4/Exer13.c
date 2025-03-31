#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        exit(1);
    } else {
        s->data[++(s->top)] = item;
    }
}

// 삭제 함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[(s->top)--];
    }
}

// 피크 함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[s->top];
    }
}

// 중복 제거 함수
void remove_duplicates(char str[]) {
    StackType s;
    init_stack(&s);

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        // 스택이 비어 있거나 현재 문자가 스택의 최상위 문자와 다르면 스택에 추가
        if (is_empty(&s) || peek(&s) != str[i]) {
            push(&s, str[i]);
        }
    }

    // 스택에 저장된 고유한 숫자를 역순으로 출력
    char result[MAX_STACK_SIZE];
    int idx = 0;

    while (!is_empty(&s)) {
        result[idx++] = pop(&s);
    }
    result[idx] = '\0';

    // 역순으로 저장된 결과를 다시 뒤집어 원래 순서로 출력
    for (int i = idx - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main() {
    char input[100];
    printf("정수를 입력하시오: ");
    scanf("%s", input);

    printf("출력: ");
    remove_duplicates(input);

    return 0;
}