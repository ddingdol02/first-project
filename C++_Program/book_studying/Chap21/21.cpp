#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 21.1 트리의 노드를 표현하는 객체의 구현

struct TreeNode
{
    string label;                // 저장할 자료 (물론 꼭 문자열일 필요는 없다.)
    TreeNode *parent;            // 부모 노드를 가리키는 포인터
    vector<TreeNode *> children; // 자손 노드들을 가리키는 포인터의 배열
};

// 21.2 트리를 순회하며 모든 노드에 포함된 값을 출력하기

// 주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels(TreeNode *root)
{
    // 루트에 저장된 값을 출력한다.
    cout << root->label << endl;
    // 각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력한다.
    for (int i = 0; i < root->children.size(); ++i)
        printLabels(root->children[i]);
}

// 21.3 순회를 이용해 트리의 높이를 계산하기

// root를 루트로 하는 트리의 높이를 구한다.
int height(TreeNode *root)
{
    int h = 0;
    for (int i = 0; i < root->children.size(); ++i)
        h = max(h, 1 + height(root->children[i]));
    return h;
}

// 21.4 트리 순회 순서 변경 문제를 해결하는 재귀 호출 코드

vector<int> slice(const vector<int> &v, int a, int b)
{
    return vector<int>(v.begin() + a, v.begin() + b);
}
// 트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다.
void printPostOrder(const vector<int> &preorder, const vector<int> &inorder)
{
    // 트리에 포함된 노드의 수
    const int N = preorder.size();
    // 기서 사례: 텅 빈 트리면 곧장 종료
    if (preorder.empty())
        return;
    // 이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다.
    const int root = preorder[0];
    // 이 트리의 왼쪽 서브 트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다.
    const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
    // 오른쪽 서브트리의 크기는 N에서 왼쪽 서브트리와 루트를 빼면 알 수 있다.
    const int R = N - 1 - L;
    // 왼쪽과 오른쪽 서브트리의 순회 결과를 출력
    printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
    printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
    // 후위 순회이므로 루트를 가장 마지막에 출력한다.
    cout << root << ' ';
}