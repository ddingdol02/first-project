#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    StackType s;
    init_stack(&s);

    char str[100];
    int c = 1;
    printf("수식: ");
    fgets(str, sizeof(str), stdin);
    int len = strlen(str);
    printf("괄호 수: ");
    for(int i=0; i<len; i++){
        char ch = str[i];
        if(ch == '('){
            printf("%d ", c);
            push(&s, c++);
        }
        if(ch == ')'){
            printf("%d ", pop(&s));
        }
    }
}