#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;
ListNode *initList()
{
    return NULL;
}
int isEmpty(ListNode *head)
{
    return head == NULL;
}
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
ListNode *freeList(ListNode *head)
{
    if (isEmpty(head))
        return NULL;
    ListNode *cur = head->link, *next;
    while (cur != head)
    {
        next = cur->link;
        free(cur);
        cur = next;
    }
    free(head);
    return NULL;
}
ListNode *insertFirst(ListNode *head, element data)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (!p)
        error("메모리 할당 오류");
    p->data = data;
    if (isEmpty(head))
    {
        p->link = p;
        return p;
    }
    else
    {
        p->link = head->link;
        head->link = p;
    }
    return head;
}
ListNode *insert(ListNode *head, ListNode *pre, element data)
{
    if (isEmpty(head) || pre == NULL)
        error("삽입 위치가 유효하지 않습니다. ");
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (!p)
        error("메모리 할당 오류");
    p->data = data;
    p->link = pre->link;
    pre->link = p;
    return head;
}
ListNode *insertLast(ListNode *head, element data)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (!p)
        error("메모리 할당 오류");
    p->data = data;
    if (isEmpty(head))
    {
        head = p;
        p->link = head;
    }
    else
    {
        p->link = head->link;
        head->link = p;
        head = p;
    }
    return head;
}
ListNode *deleteFirst(ListNode *head)
{
    if (isEmpty(head))
        error("리스트가 비어 있습니다. ");
    ListNode *removed = head->link;
    if (head == removed)
    {
        free(removed);
        head = NULL;
    }
    else
    {
        head->link = removed->link;
        free(removed);
    }
    return head;
}
ListNode *delete(ListNode *head, ListNode *pre)
{
    if (isEmpty(head) || pre == NULL || pre->link == NULL)
        error("삭제 위치가 유효하지 않습니다. ");
    ListNode *removed = pre->link;
    pre->link = removed->link;
    if (removed == head)
        head = pre;
    free(removed);
    return head;
}
ListNode *deleteLast(ListNode *head)
{
    if (isEmpty(head))
        error("리스트가 비어 있습니다. ");
    ListNode *first = head->link;
    if (head == first)
    {
        free(head);
        return NULL;
    }
    ListNode *pre = first;
    while (pre->link != head)
    {
        pre = pre->link;
    }
    pre->link = first;
    free(head);
    head = pre;
    return head;
}
void printList(ListNode *head)
{
    if (isEmpty(head))
    {
        printf("리스트가 비어 있습니다. \n");
        return;
    }
    ListNode *p = head->link;
    do
    {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head->link);
    printf("(head)\n");
}

////////// 스택 //////////

typedef struct
{
    ListNode *head;
} Stack;

Stack *initStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (!s)
        error("스택 구조체 할당 오류");
    s->head = initList();
    return s;
}
int isEmptyStack(Stack *s)
{
    return isEmpty(s->head);
}
void freeStack(Stack *s)
{
    s->head = freeList(s->head);
    free(s);
}
void push(Stack *s, element item)
{
    s->head = insertFirst(s->head, item);
}
element pop(Stack *s)
{
    if (isEmptyStack(s))
    {
        error("스택이 공백상태입니다. ");
    }
    element item = s->head->link->data;
    s->head = deleteFirst(s->head);
    return item;
}
void printStack(Stack *s)
{
    printf("Stack: ");
    printList(s->head);
}

////////// 큐 //////////

typedef struct
{
    ListNode *head;
} Queue;
Queue *initQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
        error("큐 구조체 할당 오류");
    q->head = initList();
    return q;
}
int isEmptyQueue(Queue *q)
{
    return isEmpty(q->head);
}
void freeQueue(Queue *q)
{
    q->head = freeList(q->head);
    free(q);
}
void enqueue(Queue *q, element item)
{
    q->head = insertLast(q->head, item);
}
element dequeue(Queue *q)
{
    if (isEmptyQueue(q))
        error("큐가 공백상태입니다. ");
    element item = q->head->link->data;
    q->head = deleteFirst(q->head);
    return item;
}
void printQueue(Queue *q)
{
    printf("Queue: ");
    printList(q->head);
}

////////// 메인 //////////

int main()
{
    printf("===== 스택 테스트 =====\n");
    Stack *s = initStack();
    printf("Push: 10\n");
    printf("Push: 20\n");
    printf("Push: 30\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);
    printStack(s); // 출력: Stack: 30->20->10->NULL

    printf("pop: %d\n", pop(s)); // 출력: 30
    printStack(s);               // 출력: Stack: 20->10->NULL

    printf("pop: %d\n", pop(s)); // 출력: 20
    printf("pop: %d\n", pop(s)); // 출력: 10

    if (isEmptyStack(s))
    {
        printf("스택이 비어 있습니다.\n");
    }
    freeStack(s);

    printf("\n===== 큐 테스트 =====\n");
    Queue *q = initQueue();
    printf("enqueue: 1\n");
    printf("enqueue: 2\n");
    printf("enqueue: 3\n");
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    printQueue(q); // 출력: Queue: 1->2->3->NULL

    printf("dequeue: %d\n", dequeue(q)); // 출력: 1
    printQueue(q);                       // 출력: Queue: 2->3->NULL

    printf("dequeue: %d\n", dequeue(q)); // 출력: 2
    printf("dequeue: %d\n", dequeue(q)); // 출력: 3

    if (isEmptyQueue(q))
    {
        printf("큐가 비어 있습니다.\n");
    }
    freeQueue(q);

    return 0;
}
