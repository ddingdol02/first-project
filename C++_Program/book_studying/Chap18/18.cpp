#include <iostream>
#include <list>
using namespace std;

struct ListNode
{
    int element;           // 담고 있는 원소
    ListNode *prev, *next; // 이전 노드, 다음 노드의 포인터
};

// 18.1 연결 리스트에서 노드를 삭제하고 다시 추가하기

// node 이전/이후 노드의 포인터를 바꿔서 node를 리스트에서 삭제한다
void deleteNode(ListNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
// node 이전/이후 노드의 포인터를 바꿔서 자기 자신을 다시 리스트에 삽입한다.
void recoverNode(ListNode *node)
{
    node->prev->next = node;
    node->next->prev = node;
}

// 18.2 연결 리스트를 이용한 조세푸스 문제의 구현

void josephus(int n, int k)
{
    // 리스트를 준비한다.
    list<int> survivors;
    for (int i = 1; i <= n; ++i)
        survivors.push_back(i);
    // 이번에 죽을 사람을 나타내는 포인터
    list<int>::iterator kill = survivors.begin();
    while (n > 2)
    {
        // 첫 번째 사람이 자살한다. erase()는 지운 원소의 다음 원소를 반환한다.
        kill = survivors.erase(kill);
        if (kill == survivors.end())
            kill = survivors.begin();
        --n;
        // k-1번 다음 사람으로 옮긴다.
        for (int i = 0; i < k - 1; ++i)
        {
            ++kill;
            if (kill == survivors.end())
                kill = survivors.begin();
        }
    }
    cout << survivors.front() << " " << survivors.back() << endl;
}