#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ==== 스택 코드의 시작 =====
#define MAX_STACK_SIZE 100

typedef struct{
    short r;
    short c;
} element;
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

element here = {1,0}, entry = {1, 0};
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'}, 
    {'1', '0', '0', '0', '1', '1'}, 
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};
// 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c)
{
    if(r<0 || c<0) return;
    if(maze[r][c] != '1' && maze[r][c] != '.'){
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

// 미로를 화면에 출력한다. 
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for(int r=0; r<MAZE_SIZE; r++){
        for(int c=0; c<MAZE_SIZE; c++){
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    int success = 0; // 성공 여부를 확인하는 변수
    StackType s;

    init_stack(&s);
    here = entry;
    while(1){
        r=here.r;
        c=here.c;

        // 목표 지점 'x'에 도달한 경우
        if (maze[r][c] == 'x') {
            success = 1;
            break;
        }

        maze[r][c] = '.';   // 현재 위치를 방문 표시
        maze_print(maze);

        // 인접 위치를 스택에 추가
        push_loc(&s, r-1, c);
        push_loc(&s, r+1, c);
        push_loc(&s, r, c-1);
        push_loc(&s, r, c+1);

        // 스택이 비어 있으면 실패
        if (is_empty(&s)) {
            break;
        }

        // 다음 위치로 이동
        here = pop(&s);
    }

    // 결과 출력
    if (success) {
        printf("성공\n");
    } else {
        printf("실패\n");
    }
    return 0;
}