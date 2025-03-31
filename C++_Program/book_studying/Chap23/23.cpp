#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 23.1 정수 원소를 갖는 최대 힙에 새 원소 삽입하기

// 정수를 담는 최대 힙 heap에 새 원소 newValue를 삽입한다.
void push_heap(vector<int> &heap, int newValue)
{
    // 힙의 맨 끝에 newValue를 삽입한다.
    heap.push_back(newValue);
    // 현재 newValue의 위치
    int idx = heap.size() - 1;
    // 루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날 때까지
    while (idx > 0 && heap[(idx - 1) / 2] < heap[idx])
    {
        swap(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// 23.2 정수 원소를 갖는 최대 힙에서 최대 원소 삭제하기

// 정수를 답는 최대 힙 heap에서 heap[0]를 제거한다.
void pop_heap(vector<int> &heap)
{
    // 힙의 맨 끝에서 값을 가져와 루트에 덮어씌운다.
    heap[0] = heap.back();
    heap.pop_back();
    int here = 0;
    while (true)
    {
        int left = here * 2 + 1, right = here * 2 + 2;
        // 리프에 도달한 경우
        if (left >= heap.size())
            break;
        // heap[here]가 내려갈 위치를 찾는다.
        int next = here;
        if (heap[next] < heap[left])
            next = right;
        if (right < heap.size() && heap[next] < heap[right])
            next = right;
        if (next == here)
            break;
        swap(heap[here], heap[next]);
        here = next;
    }
}

// 23.4 힙을 이용해 변화하는 중간 값 문제를 해결하는 함수의 구현

int runningMedian(int n, RNG rng)
{
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int ret = 0;
    // 반복문 불변식:
    // 1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
    // 2. maxHeap.top() <= minHeap.top()
    for (int cnt = 1; cnt <= n; ++cnt)
    {
        // 우선 1번 불변식부터 만족시킨다.
        if (maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        // 2번 불변싣이 깨졌을 경우 복구하자.
        if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top())
        {
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop();
            minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}

// 23.5 변화하는 중간 값 문제의 입력 생성하기

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