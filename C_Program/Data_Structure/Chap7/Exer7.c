#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode{   // 이중연결 노드 타입
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead){
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead){
    DListNode* p;
    for(p = phead->rlink; p != phead; p=p->rlink){
        printf("%d ", p->data);
    }
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입한다. 
void dinsert(DListNode *before, element data){
    DListNode *newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// 노드 removed를 삭제한다. 
void ddelete(DListNode* head, DListNode* removed){
    if(head == removed) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

DListNode* search(DListNode* L, element data){
    DListNode* p;
    for(p = L->rlink; p != L; p = p->rlink){
        if(p->data == data)
            return p;
    }
    return NULL;
}

// 이중 연결 리스트 테스트 프로그램 
int main(void){
    DListNode* head = (DListNode*) malloc(sizeof(DListNode));
    init(head);
    printf("데이터의 개수를 입력하시오 : ");
    int n;
    scanf("%d", &n);
    printf("\n");
    for(int i=0; i<n; i++){
        printf("노드 #%d의 데이터를 입력하시오: ", i+1);
        int k;
        scanf("%d", &k);
        dinsert(head, k);
    }
    printf("\n");
    printf("데이터를 역순으로 출력: ");
    print_dlist(head);
    free(head);
    return 0;
}