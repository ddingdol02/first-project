#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char *word;
    struct Node *left;
    struct Node *right;
} Node;
// 새 문자열 노드 생성
Node *createNode(const char *word)
{
    Node *node = malloc(sizeof(Node));
    if (!node)
    {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    node->word = malloc(strlen(word) + 1);
    if (!node->word)
    {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->word, word);
    node->left = node->right = NULL;
    return node;
}
// BST에 노드 삽입
Node *insert(Node *root, const char *word, int *inserted)
{
    if (root == NULL)
    {
        *inserted = 1;
        return createNode(word);
    }
    int cmp = strcmp(word, root->word);
    if (cmp < 0)
        root->left = insert(root->left, word, inserted);
    else if (cmp > 0)
        root->right = insert(root->right, word, inserted);
    else
        *inserted = 0;
    return root;
}
// 탐색 함수
Node *search(Node *root, const char *word)
{
    if (root == NULL)
        return NULL;
    int cmp = strcmp(word, root->word);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return search(root->left, word);
    else
        return search(root->right, word);
}
// 중위 순회 함수
void inorder(Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%s\n", root->word);
    inorder(root->right);
}
// 노드 개수 출력
int countNodes(Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}
// 트리에 할당 된 메모리 반환
void freeTree(Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->word);
    free(root);
}

int main()
{
    Node *root = NULL;
    int choice;
    char buffer[128];

    while (1)
    {
        printf("\n------ 사전 메뉴 ------\n");
        printf("1. 단어 삽입\n");
        printf("2. 단어 검색\n");
        printf("3. 사전 출력 (중위순회)\n");
        printf("4. 총 단어 수\n");
        printf("5. 종료\n");
        printf("선택(1-5): ");
        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "잘못된 입력입니다. 프로그램을 종료합니다.\n");
            break;
        }

        switch (choice)
        {
        case 1: // 삽입
            printf("삽입할 단어: ");
            scanf("%127s", buffer);
            int inserted;
            inserted = 0;
            root = insert(root, buffer, &inserted);
            if (inserted)
                printf("단어 \"%s\" 삽입 완료.\n", buffer);
            else
                printf("단어 \"%s\" 는 이미 존재합니다.\n", buffer);
            break;

        case 2: // 검색
            printf("검색할 단어: ");
            scanf("%127s", buffer);
            if (search(root, buffer))
                printf("단어 \"%s\" 가 사전에 존재합니다.\n", buffer);
            else
                printf("단어 \"%s\" 를 찾을 수 없습니다.\n", buffer);
            break;

        case 3: // 중위순회 출력
            if (root == NULL)
                printf("사전이 비어 있습니다.\n");
            else
            {
                printf("사전의 모든 단어 (알파벳 순):\n");
                inorder(root);
            }
            break;

        case 4: // 노드 수 출력
            printf("총 단어 수: %d\n", countNodes(root));
            break;

        case 5: // 종료
            printf("프로그램을 종료합니다.\n");
            freeTree(root);
            return 0;

        default:
            printf("1~5 사이의 번호를 입력하세요.\n");
        }
    }

    // 혹시 루프를 탈출했다면 메모리 해제
    freeTree(root);
    return 0;
}