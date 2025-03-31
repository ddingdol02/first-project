#include <stdio.h>
#include <stdlib.h>

// ===== 연결 리스트 정의 코드 =====
#define MAX_LIST_SIZE 100   // 리스트의 최대크기

typedef int element;        // 항목의 정의
typedef struct {
    element array[MAX_LIST_SIZE];   // 배열의 정의
    int size;                       // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 오류 처리 함수
void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 리스트 초기화 함수
void init(ArrayListType *L){
    L->size = 0;
}
// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(ArrayListType *L){
    return L->size == 0;
}
// 리스트가 가득 차 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_full(ArrayListType *L){
    return L->size == MAX_LIST_SIZE;
}
element get_entry(ArrayListType *L, int pos){
    if(pos<0 || pos>=L->size){
        error("위치 오류");
    }
    return L->array[pos];
}
// 리스트 출력
void print_list(ArrayListType *L){
    for(int i=0; i<L->size; i++){
        printf("%d->", L->array[i]);
    }
    printf("\n");
}
void insert_last(ArrayListType *L, element item){
    if(L->size >= MAX_LIST_SIZE){   // 리스트에 빈 공간 없으면 오류 발생
        error("리스트 오버플로우");
    }
    L->array[L->size++] = item;
}
void insert(ArrayListType *L, int pos, element item){
    if(!is_full(L) && (pos >=0) && (pos <= L->size)){
        for(int i=(L->size - 1); i>= pos; i--){
            L->array[i+1] = L->array[i];
        }
        L->array[pos] = item;
        L->size++;
    }
}
element delete(ArrayListType *L, int pos){
    element item;
    if(pos<0 || pos>=L->size){
        error("위치 오류");
    }
    item = L->array[pos];
    for(int i=pos; i<(L->size - 1); i++){
        L->array[i] = L->array[i+1];
    }
    L->size--;
    return item;
}
// 리스트의 모든 항목 제거
void clear(ArrayListType *L){
    if(L == NULL){
        error("리스트가 Null입니다. ");
    }
    L->size = 0;
    printf("모든 리스트가 초기화되었습니다. \n");
}
// 리스트의 항목 교체
void replace(ArrayListType *L, int pos, element item){
    if(pos<0 || pos>=L->size){
        error("위치 오류");
    }
    L->array[pos] = item;
}
int get_length(ArrayListType *L){
    return L->size;
}
// ===== 연결 리스트 코드 끝 =====

int main(void){
    // ArrayListType를 정적으로 생성하고 ArrayListType를 가리키는 포인터를 함수의 매개변수로 전달한다. 
    ArrayListType list;
    init(&list);
    insert(&list, 0, 10);   print_list(&list);  // 0번째 위치에 10 추가
    insert(&list, 0, 20);   print_list(&list);  // 0번째 위치에 20 추가
    insert(&list, 0, 30);   print_list(&list);  // 0번째 위치에 30 추가
    insert_last(&list, 40); print_list(&list);  // 맨 끝에 40 추가
    delete(&list, 0);       print_list(&list);  // 0번째 항목 삭제
    replace(&list, 1, 50);  print_list(&list);  // 1번째 항목 50으로 교체
    printf("리스트의 길이: %d개\n", get_length(&list));
    clear(&list);
    return 0;
}