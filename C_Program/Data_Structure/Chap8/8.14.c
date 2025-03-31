#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

// 데이터 형식
typedef struct {
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
} element;

// 노드의 구조
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// 비교 함수
int compare(element e1, element e2) {
    return strcmp(e1.word, e2.word);
}

// 트리 출력 함수
void display(TreeNode* p) {
    if (p != NULL) {
        printf("(");
        display(p->left);
        printf("%s: %s", p->key.word, p->key.meaning);
        display(p->right);
        printf(")");
    }
}

// 트리 탐색 함수
TreeNode* search(TreeNode* root, element key) {
    TreeNode* p = root;
    while (p != NULL) {
        int cmp = compare(key, p->key);
        if (cmp == 0) 
            return p;
        else if (cmp < 0)
            p = p->left;
        else
            p = p->right;
    }
    return NULL;
}

// 새 노드 생성 함수
TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    // 깊은 복사
    strcpy(temp->key.word, item.word);
    strcpy(temp->key.meaning, item.meaning);
    temp->left = temp->right = NULL;
    return temp;
}

// 노드 삽입 함수
TreeNode* insert_node(TreeNode* node, element key) {
    if (node == NULL)
        return new_node(key);
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    return node;
}

// 트리 삭제 함수
TreeNode* delete_node(TreeNode* root, element key) {
    if (root == NULL)
        return root;
    int cmp = compare(key, root->key);
    if (cmp < 0)
        root->left = delete_node(root->left, key);
    else if (cmp > 0)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

// 트리 해제 함수
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// 도움말 출력
void help() {
    printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****\n");
}

// 메인 함수
int main(void) {
    char command;
    element e;
    TreeNode* root = NULL;
    TreeNode* tmp;

    do {
        help();
        printf("명령어 입력: ");
        scanf("%c", &command);
        while (getchar() != '\n'); // 입력 버퍼 정리

        switch (command) {
            case 'i': 
                printf("단어: ");
                fgets(e.word, MAX_WORD_SIZE, stdin);
                e.word[strcspn(e.word, "\n")] = '\0';
                printf("의미: ");
                fgets(e.meaning, MAX_MEANING_SIZE, stdin);
                e.meaning[strcspn(e.meaning, "\n")] = '\0';
                root = insert_node(root, e);
                break;
            case 'd':
                printf("단어: ");
                fgets(e.word, MAX_WORD_SIZE, stdin);
                e.word[strcspn(e.word, "\n")] = '\0';
                root = delete_node(root, e);
                break;
            case 'p':
                display(root);
                printf("\n");
                break;
            case 's':
                printf("단어: ");
                fgets(e.word, MAX_WORD_SIZE, stdin);
                e.word[strcspn(e.word, "\n")] = '\0';
                tmp = search(root, e);
                if (tmp != NULL)
                    printf("의미: %s\n", tmp->key.meaning);
                else
                    printf("단어를 찾을 수 없습니다.\n");
                break;
            case 'q':
                printf("프로그램 종료.\n");
                free_tree(root);
                break;
            default:
                printf("알 수 없는 명령입니다.\n");
                break;
        }
    } while (command != 'q');

    return 0;
}