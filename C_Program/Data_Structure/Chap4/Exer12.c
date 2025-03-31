#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

// 런길이 압축 함수
void run_length_compression(char str[]) {
    StackType s;
    init_stack(&s);

    int len = strlen(str);
    int count = 1; // 동일한 문자의 개수를 세는 변수

    for (int i = 0; i < len; i++) {
        char current_char = tolower(str[i]); // 대소문자 구분 없이 처리 (소문자로 변환)
        
        // 스택이 비어있지 않고, 현재 문자가 스택의 맨 위 문자와 다르면
        if (!is_empty(&s) && peek(&s) != current_char) {
            printf("%d%c", count, peek(&s)); // 이전 문자와 개수 출력
            pop(&s); // 이전 문자 제거
            count = 1; // 카운트 초기화
        } else if (!is_empty(&s) && peek(&s) == current_char) {
            count++; // 동일 문자일 경우 개수 증가
        }

        // 스택에 현재 문자 삽입
        if (is_empty(&s) || peek(&s) != current_char) {
            push(&s, current_char);
        }
    }

    // 마지막 문자와 개수 출력
    if (!is_empty(&s)) {
        printf("%d%c", count, peek(&s));
        pop(&s);
    }

    printf("\n"); // 압축된 문자열 출력 후 줄바꿈
}

int main() {
    char input[100];

    printf("문자열을 입력하시오: ");
    scanf("%s", input); // 공백 없는 문자열 입력
    printf("압축된 문자열: ");
    run_length_compression(input);

    return 0;
}