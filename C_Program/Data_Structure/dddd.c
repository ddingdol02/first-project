#include <stdio.h>

// 1. 배열에서 최댓값 찾기
int find_max(int arr[], int size)
{
    int result = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > result)
        {
            result = arr[i];
        }
    }
    return result;
}

// 2. 연결 리스트에서 특정 값 탐색
typedef struct ListNode
{
    int data;
    struct ListNode *link;
} ListNode;
ListNode *search_list(ListNode *head, int target)
{
    ListNode *p = head;
    while (p != NULL)
    {
        if (p->data == target)
        {
            return p;
        }
        p = p->link;
        return NULL;
    }
}

// 3. 배열 스택의 push() 구현 (isFull 포함)
#define MAX_STACK_SIZE 100

typedef struct
{
    int data[MAX_STACK_SIZE];
    int top;
} StackType;
int isFull(StackType *s)
{
    return s->top == MAX_STACK_SIZE - 1;
}
void push(StackType *s, int item)
{
    if(isFull(s)){
        printf("Stack is full\n");
        return;
    }
    s->data[++(s->top)] = item;
}

// 4. 큐 구조체에서 dequeue() 구현 (의사코드 기반)
#define MAX_QUEUE_SIZE 100
typedef struct{
    int data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;
int isEmpty(QueueType *q){
    return q->front == q->rear;
}
int dequeue(QueueType *q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

// 5. 후위 표기식 계산 함수 (eval_postfix) 핵심 로직
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int eval_postfix(char* expr){
    int stack[MAX_STACK_SIZE];
    int top = -1;
    char* token = strtok(expr, " ");
    while(token != NULL){
        if(isdigit(token[0])){
            stack[++top] = atoi(token);
        }else{
            int op2 = stack[top--];
            int op1 = stack[top--];
            switch(token[0]){
                case '+': stack[++top] = op1 + op2; break;
                case '-': stack[++top] = op1 - op2; break;
                case '*': stack[++top] = op1 * op2; break;
                case '/': stack[++top] = op1 / op2; break;
            }
        }
        token = strtok(NULL, " ");
    }
    return stack[top];
}

// // 1. 배열을 이용해 정수형 스택을 구현하고 pop() 함수를 작성하시오. (비었는지 검사 포함)
int pop(StackType* s){
    if(isEmpty(s)){
        printf("Stack is empty\n");
        return;
    }
    return s->data[(s->top)--];
}
// 2. 단순 연결 리스트에서 리스트를 역순으로 출력하는 함수를 구현하시오.(재귀 사용 금지)
void print_reverse(ListNode* head){
    ListNode* stack[100];
    int top = -1;

    ListNode* p = head;
    while(p!=NULL){
        stack[++top] = p;
        p = p->link;
    }
    while(top >= 0){
        printf("%d ", stack[top--]->data);
    }
    printf("\n");
}
// 3. 후위 표기식을 중위 표기식으로 변환하는 char *postfix_to_infix(char *expr) 함수의 로직 중 스택 활용 부분을 설명하는 코드를 작성하시오.
typedef struct{
    char* item[100];
    int top;
} Stack;

void push(Stack* s, char* str){
    s->item[++(s->top)] = strdup(str);
}

char* pop(Stack* s){
    return s->item[(s->top)--];
}



// 4. 원형 큐(Circular Queue) 에서 enqueue() 연산을 구현하시오.

// 5. 연결 리스트에서 주어진 노드를 기준으로 새 노드를 삽입하는 insert_after(ListNode *pre, int data) 함수를 작성하시오.