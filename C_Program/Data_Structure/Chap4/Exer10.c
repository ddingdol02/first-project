#include <stdio.h>
#include <stdlib.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ==== 스택 코드의 시작 =====
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct 
{
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType *s, element item)
{
    if(is_full(s)){
        fprintf(stderr, "스택 포화 에러\n");
        exit(1);
    }
    else s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType *s)
{
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

// 피크 함수
element peek(StackType *s)
{
    if(is_empty(s)){
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)];
}
// ===== 스택 코드의 끝 =====

int main(void)
{
    int num, value;
    StackType s;
    init_stack(&s);

    printf("정수 배열의 크기: ");
    scanf("%d", &num);

    printf("정수를 입력하시오: ");
    for(int i=0; i<num; i++){
        scanf("%d", &value);
        push(&s, value);
    }
    printf("반전된 정수 배열: ");
    for(int i=0; i<num; i++){
        printf("%d ", pop(&s));
    }
    return 0;
}