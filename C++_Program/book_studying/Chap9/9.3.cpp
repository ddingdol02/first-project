#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 9.2 여행 짐 싸기 문제를 해결하는 동적 계획법 알고리즘

int n, capacity;
int volume[100], need[100];
int cache[1001][100];
string name[100];
// 캐리어에 남은 용량이 capacity일 때, item 이후의 물건들을
// 담아 얻을 수 있는 최대 절박도의 합을 반환한다.
int pack(int capacity, int item)
{
    // 기저 사례: 더 담을 물건이 없으 때
    if (item == n)
        return 0;
    int &ret = cache[capacity][item];
    if (ret != -1)
        return ret;
    // 이 물건을 담지 않을 경우
    ret = pack(capacity, item + 1);
    // 이 물건을 담을 경우
    if (capacity >= volume[item])
        ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
    return ret;
}

// 9.3 여행 짐 싸기 문제의 답 역추적하는 재귀 호출 알고리즘

// pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장한다.
void reconstruct(int capacity, int item, vector<string> &picked)
{
    // 기저 사례: 모든 물건을 다 고려했음
    if (item == n)
        return;
    if (pack(capacity, item) == pack(capacity, item + 1))
        reconstruct(capacity, item + 1, picked);
    else
    {
        picked.push_back(name[item]);
        reconstruct(capacity - volume[item], item + 1, picked);
    }
}