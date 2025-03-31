#include <iostream>
#include <vector>

using namespace std;

// 17.1 부분합을 계산하는 함수와 이를 이용해 구간합을 계산하는 함수의 구현

// 주어진 벡터 a의 부분합을 계산한다.
vector<int> partialSum(const vector<int> &a)
{
    vector<int> ret(a.size());
    ret[0] = a[0];
    for (int i = 1; i < a.size(); ++i)
        ret[i] = a[i - 1] + a[i];
    return ret;
}
// 어떤 벡터의 부분합 psum[]이 주어질 때, 원래 벡터의 a부터 b까지의 합을 구한다.
int rangeSum(const vector<int> &psum, int a, int b)
{
    if (a == 0)
        return psum[b];
    return psum[b] - psum[a - 1];
}

// 17.2 배열의 부분합과 제곱의 부분합을 입력받고 특정 구간의 분산을 계산하는 함수의 구현

// A[]의 제곱의 부분 합 벡터 sqpsum, A[]의 부분 합 벡터 psum이 주어질 때
// A[a..b]의 분산을 반환한다.
double variance(const vector<int> &sqpsum, const vector<int> &psum, int a, int b)
{
    // 우선 해당 구간의 평균을 계산한다.
    double mean = rangeSum(psum, a, b) / double(b - a + 1);
    double ret = rangeSum(sqpsum, a, b) - 2 * mean * rangeSum(psum, a, b) + (b - a + 1) * mean * mean;
    return ret / (b - a + a);
}

// 17.3 부분 합을 이용해 2차원 배열긔 구간 합을 구하는 함수의 구현

// 어떤 2차원 배열 A[][]의 부분합 psum[][]이 주어질 때,
// A[y1, x1]과 A[y2, x2]를 양 끝으로 갖는 부분 배열의 합을 반환한다.
int gridSum(const vector<vector<int>> &psum, int y1, int x1, int y2, int x2)
{
    int ret = psum[y2][x2];
    if (y1 > 0)
        ret -= psum[y1 - 1][x2];
    if (x1 > 0)
        ret -= psum[y2][x1 - 1];
    if (y1 > 0 && x1 > 0)
        ret += psum[y1 - 1][x1 - 1];
    return ret;
}

// 17.4 부분 합을 이용해 크리스마스 인형 문제를 해결하는 두 함수의 구현

// D[]의 부분 합 배열 psum[]과 k가 주어질 때, 몇 가지 방법으로 살 수 있는지 반환한다.
// psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int waysToBuy(const vector<int> &psum, int k)
{
    const int MOD = 20091101;
    int ret = 0;
    vector<long long> count(k, 0);
    for (int i = 0; i < psum.size(); ++i)
        count[psum[i]]++;
    // 두 번 이상 본 적 있다면 이 값 중 두 개를 선택하는 방법의 수를 더한다.
    for (int i = 0; i < k; ++i)
        if (count[i] >= 2)
            ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
    return ret;
}
// D[]의 부분 합 배열 psum[]과 k가 주어질 때, 겹치지 않게 몇 번이나 살 수 있는지 반환한다.
// psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int maxBuys(const vector<int> &psum, int k)
{
    // ret[i]=첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
    vector<int> ret(psum.size(), 0);
    // prev[s]=psum[]이 s였던 마지막 위치
    vector<int> prev(k, -1);
    for (int i = 0; i < psum.size(); ++i)
    {
        // i번째 상자를 아예 고려하지 않는 경우
        if (i > 0)
            ret[i] = ret[i - 1];
        else
            ret[i] = 0;
        // psum[i]를 전에도 본 적이 있으면, prev[psum[i]]+1부터 여기까지 쭉 사 본다.
        int loc = prev[psum[i]];
        if (loc != -1)
            ret[i] = max(ret[i], ret[loc] + 1);
        // prev[]에 현재 위치를 기록한다.
        prev[psum[i]] = i;
    }
    return ret.back();
}