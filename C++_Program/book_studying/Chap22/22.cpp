#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 22.1 한 점이 다른 점에 지배당하는지 확인하는 함수

// 현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다.
// coords[x] = y
map<int, int> coords;
// 새로운 점 (x, y)가 기존의 다른 점들에 지배당하는지 확인한다.
bool isDominated(int x, int y)
{
    // x보다 오른쪽에 있는 점 중 가장 왼쪽에 있는 점을 찾는다.
    map<int, int>::iterator it = coords.lower_bound(x);
    // 그런 점이 없으면 (x, y)는 지배당하지 않는다.
    if (it == coords.end())
        return false;
    // 이 점은 x보다 오른쪽에 있는 점 중 가장 위에 있는 점이므로,
    // (x, y)가 어느 점에 지배되려면 이 점에도 지배되어야 한다.
    return 7 < it->second;
}

// 22.2 지배되는 점들을 삭제하는 함수

// 새로운 점 (x, y)에 지배당하는 점들을 트리에서 지운다.
void removeDominated(int x, int y)
{
    map<int, int>::iterator it = coords.lower_bound(x);
    // (x, y)보다 왼쪽에 있는 점이 없다!
    if (it == coords.begin())
        return;
    --it;
    // 반복문 불변식: it는 (x, y)의 바로 왼쪽에 있는 점
    while (true)
    {
        // (x, y) 바로 왼쪽에 오는 점을 찾는다.
        // it가 표시하는 점이 (x, y)에 지배되지 않는다면 곧장 종료
        if (it->second > y)
            break;
        // 이전 점이 더 없으므로 it만 지우고 종료한다.
        if (it == coords.begin())
        {
            coords.erase(it);
            break;
        }
        // 이전 점으로 이터레이터를 하나 옮겨 놓고 it를 지운다.
        else
        {
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}
// 새 점 (x, y)가 추가되었을 때 coords를 갱신하고,
// 다른 점에 지배당하지 않는 점들의 개수를 반환한다.
int registered(int x, int y)
{
    // (x, y)가 이미 지배당하는 경우에는 그냥 (x, y)를 버린다.
    if (isDominated(x, y))
        return coords.size();
    // 기존에 있던 점 중 (x, y)에 지배당하는 점들을 지운다.
    removeDominated(x, y);
    coords[x] = y;
    return coords.size();
}

// 22.3 트립의 노드를 표현하는 객체의 구현

typedef int keyType;
// 트립의 한 노드를 저장한다.
struct Node
{
    // 노드에 저장된 원소
    keyType key;
    // 이 노드의 우선순위(priority)
    // 이 노드를 루트로 하는 서브트리의 크기(size)
    int priority, size;
    // 두 자식 노드의 포인터
    Node *left, *right;
    // 생성자에서 난수 우선순위를 생성하고, size와 left/right를 초기화한다.
    Node(const keyType &_key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
    void setLeft(Node *newLeft)
    {
        left = newLeft;
        calcSize();
    }
    void setRight(Node *newRight)
    {
        right = newRight;
        calcSize();
    }
    // size 멤버를 생신한다.
    void calcSize()
    {
        size = 1;
        if (left)
            size += left->size;
        if (right)
            size += right->size;
    }
};

// 22.4 트립에서의 노드 추가와 트립 쪼개기 연산의 구현

typedef pair<Node *, Node *> NodePair;
// root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는 두 개의 트립으로 분리한다.
NodePair split(Node *root, keyType key)
{
    if (root == NULL)
        return NodePair(NULL, NULL);
    // 루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
    if (root->key < key)
    {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    // 루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}
// root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의 루트를 반환한다.
Node *insert(Node *root, Node *node)
{
    if (root == NULL)
        return node;
    // node가 루트를 대체해야 한다. 해당 서브트리를 반으로 잘라 각각 자손으로 하낟.
    if (root->priority < node->priority)
    {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if (node->key < root->key)
        root->setLeft(insert(root->left, node));
    else
        root->setRight(insert(root->right, node));
    return root;
}

// 22.5 트립에서 노드의 삭제와 합치기 연산의 구현

// a와 b가 두 개의 트립이고, max(a) < min(b)일 때 이 둘을 합친다.
Node *merge(Node *a, Node *b)
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (a->priority < b->priority)
    {
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}
// root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환한다.
Node *erase(Node *root, keyType key)
{
    if (root == NULL)
        return root;
    // root를 지우고 양 서브트리를 합친 뒤 반환한다.
    if (root->key == key)
    {
        Node *ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if (key < root->key)
        root->setLeft(erase(root->left, key));
    else
        root->setRight(erase(root->right, key));
    return root;
}

// 22.6 트립에서 k번째 원소를 찾는 알고리즘의 구현

// root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node *kth(Node *root, int k)
{
    // 왼쪽 서브트리의 크기를 우선 계산한다.
    int leftSize = 0;
    if (root->left != NULL)
        leftSize = root->left->size;
    if (k <= leftSize)
        return kth(root->left, k);
    if (k == leftSize + 1)
        return root;
    return kth(root->right, k - leftSize - 1);
}

// 22.7 트립에서 X보다 작은 원소의 수를 찾는 알고리즘의 구현

// key보다 작은 키값의 수를 반환한다.
int countLessThan(Node *root, keyType key)
{
    if (root == NULL)
        return 0;
    if (root->key >= key)
        return countLessThan(root->left, key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}

void insertionSort(vector<int> &A)
{
    for (int i = 0; i < A.size(); ++i)
    {
        // A[0..i-1]에 A[i]를 끼워넣는다.
        int j = i;
        while (j > 0 && A[j - 1] > A[i])
        {
            // 불변식 a: A[j+1..i]의 모든 원소는 A[j]보다 크다.
            // 불변식 b: A[0..i] 구간은 A[i]를 제외하면 정렬되어 있다.
            swap(A[j - 1], A[j]);
            --j;
        }
    }
}

// 22.8 삽입 정렬 뒤집기 문제를 해결하는 알고리즘

// shifted[i] = A[i]가 외놎그올 몇 칸 움직이는가?
int n, shifted[50000];
int A[50000];
// n, shifted[]를 보고 A[]에 값을 저장한다.
void solve()
{
    // 1~N까지의 숫자를 모두 저장하는 트립을 만든다.
    Node *candicates = NULL;
    for (int i = 0; i < n; ++i)
        candicates = insert(candicates, new Node(i + 1));
    // 뒤에서부터 A[]를 채워나간다.
    for (int i = n - 1; i >= 0; --i)
    {
        // 후보 중 이 수보다 큰 수가 larger개 있다.
        int larger = shifted[i];
        Node *k = kth(candicates, i + 1 - larger);
        A[i] = k->key;
        candicates = erase(candicates, k->key);
    }
}

// 23.3 변화하는 중간 값 문제를 트립을 사용해서 풀기

// mg가 생성하는 첫 n개의 난수를 수열에 추가하며 중간 값을 구한다.
int runningMedian1(int n, RNG rng)
{
    Node *root = NULL;
    int ret = 0;
    for (int cnt = 1; cnt <= n; ++cnt)
    {
        root = insert(root, new Node(rng.next()));
        int median = kth(root, (cnt + 1) / 2)->key;
        ret = (ret + median) % 20090711;
    }
    return ret;
}

struct RNG
{
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next()
    {
        int ret = seed;
        seed = ((seed * (long long)a) + b) % 20090711;
        return ret;
    }
};