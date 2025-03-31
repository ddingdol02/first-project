#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode{    // 노드 타입
    element data;
    struct ListNode *link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode *head){
    ListNode* p;
    if(head == NULL)    return;
    p = head->link;
    do{
        printf("%d->", p->data);
        p = p->link;
    } while (p != head->link);
}

ListNode* insert_first(ListNode* head, element data){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    if(head == NULL){
        head = node;
        node->link = head;
    }else{
        node->link = head->link;
        head->link = node;
    }
    return head;    // 변경된 헤드 포인터를 반환한다. 
}

ListNode* insert_last(ListNode* head, element data){
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->data = data;
    if(head == NULL){
        head = node;
        node->link = head;
    }else{
        node->link = head->link;
        head->link = node;
        head = node;
    }
    return head;
}

ListNode* search(ListNode* L, element data){
    ListNode* p = L;
    do{
        if(p->data == data)
            return p;
        p = p->link;
    }while(p != L);
    return NULL;
}

int get_size(ListNode* L){
    ListNode* p = L;
    int count = 0;
    do{
        count++;
        p = p->link;
    }while(p != L);
    return count;
}