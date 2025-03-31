#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 9.10 k번째 LIS 구하기: LIS의 개수 세기

const int MAX = 2000000000 + 1;
int n;
int cacheLen[501], cacheCnt[501], S[500];
// S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis(int start)
{
    // 메모이제이션
    int &ret = cacheLen[start + 1];
    if (ret != -1)
        return ret;
    // 항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for (int next = start + 1; next < n; ++next)
        if (start == -1 || S[start] < S[next])
            ret = max(ret, lis(next) + 1);
    return ret;
}
// S[start]에서 시작하는 최대 증가 부분 수열의 수를 반환한다.
int count(int start)
{
    // 기저 사례: LIS의 길이가 1인 경우
    if (lis(start) == 1)
        return 1;
    // 메모이제이션
    int &ret = cacheCnt[start + 1];
    if (ret != -1)
        return ret;
    ret = 0;
    for (int next = start + 1; next < n; ++next)
    {
        if ((start == -1 || S[start] < S[next]) && lis(start) == lis(next) + 1)
            ret = min<long long>(MAX, (long long)ret + count(next));
    }
    return ret;
}

// 9.11 k번째 LIS 구하기: K번째 LIS 계산하기

// S[start]에서 시작하는 LIS 중 사전순으로 skip개 건너뛴 수열을 lis에 저장한다.
void reconstruct(int start, int skip, vector<int> &lis)
{
    // 1. S[start]는 항상 LIS에 포함된다.
    if (start != -1)
        lis.push_back(S[start]);
    // 2. 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다.
    // (숫자, 숫자의 위치)의 목록이 된다.
    vector<pair<int, int>> followers;
    for (int next = start + 1; next < n; ++next)
        if ((start == -1 || S[start] < S[next]) && lis3(start) == lis3(next) + 1)
            followers.push_back(make_pair(S[next], next));
    sort(followers.begin(), followers.end());
    // 3. k번째 LIS의 다음 숫자를 찾는다.
    for (int i = 0; i < followers.size(); ++i)
    {
        int idx = followers[i].second;
        int cnt = count(idx);
        if (cnt <= skip)
            skip -= cnt;
        else
        {
            // 다음 숫자는 S[idx]임을 알았다.
            // 4. 재귀 호출을 통해
            reconstruct(idx, skip, lis);
            break;
        }
    }
}

// 8.12 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘 (2)

int n12;
int cache12[101], S12[100];
// S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis3(int start)
{
    int &ret = cache12[start + 1];
    if (ret != -1)
        return ret;
    // 항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for (int next = start + 1; next < n12; ++next)
        if (start == -1 || S12[start] < S12[next])
            ret = max(ret, lis3(next) + 1);
    return ret;
}