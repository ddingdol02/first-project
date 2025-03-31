#include <iostream>
#include <vector>
#include <memory.h>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// 8.1 재귀 호출을 이용한 이항 계수의 계산

int bino(int n, int r)
{
    // 기저 사례: n=r(모든 원소를 다 고르는 경우) 혹은 r=0(고를 원소가 없는 경우)
    if (r == 0 || r == n)
        return 1;
    return bino(n - 1, r - 1) + bino(n - 1, r);
}

// 8.2 메모이제이션을 이용한 이항 계수의 계산

// -1로 초기화해 둔다.
int cache2[30][30];
int bino2(int n, int r)
{
    // 기저 사례
    if (r == 0 || r == n)
        return 1;
    // -1이 아니라면 한 번 계산했던 값이니 곧장 반환
    if (cache2[n][r] != -1)
        return cache2[n][r];
    // 직접 계산한 뒤 배열에 저장
    return cache2[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);
}

// // 8.3 메모이제이션의 사용 예

// // 전부 -1로 초기화해 둔다.
// int cache3[2500][2500];
// // a와 b는 각각[0, 2500) 구간 안의 정수
// // 반환 값은 항상 int형 안에 들어가는 음이 아닌 정수
// int someObscureFunction(int a, int b)
// {
//     // 기저 사례를 처음에 처리한다.
//     if (...)
//         return ...;
//     // (a, b)에 대한 답을 구한 적이 있으면 곧장 반환
//     int &ret = cache3[a][b];
//     if (ret != -1)
//         return ret;
//     // 여기에서 답을 계산한다.
//     ... return ret;
// }
// int main()
// {
//     // memset()을 이용해 cache 배열을 초기화한다.
//     memset(cache3, -1, sizeof(cache3));
// }

// 8.4 외발 뛰기 문제를 해결하는 재귀 호출 알고리즘

int n4, board4[100][100];
bool jump(int y, int x)
{
    // 기저 사례: 게임판 밖을 벗어난 경우
    if (y >= n4 || x >= n4)
        return false;
    // 기서 사례: 마지막 칸에 도착한 경우
    if (y == n4 - 1 && x == n4 - 1)
        return true;
    int jumpSize = board4[y][x];
    return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

// 8.5 외발 뛰기 문제를 해결하는 동적 계획법 알고리즘

int n5, board5[100][100];
int cache5[100][100];
int jump2(int y, int x)
{
    // 기저 사례 처리
    if (y >= n5 || x >= n5)
        return 0;
    if (y == n5 - 1 && x == n5 - 1)
        return 1;
    // 메모이제이션
    int &ret = cache5[y][x];
    if (ret != -1)
        return ret;
    int jumpSize = board5[y][x];
    return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}

// 8.6 와일드카드 문제를 해결하는 완전 탐색 알고리즘

// 와일드 카드 패턴 w가 문자열 s에 대응되는지 여부를 반환한다.
bool match(const string &w, const string &s)
{
    // w[pos]와 s[pos]를 맞춰나간다.
    int pos = 0;
    while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
        ++pos;
    // 더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다.
    // 2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 대응됨
    if (pos == w.size())
        return pos == s.size();
    // 4. *를 만나서 끝난 경우: *에 몇 글자를 대응해야 할 지 재귀 호출하면서 확인한다.
    if (w[pos] == '*')
        for (int skip = 0; pos + skip <= s.size(); ++skip)
            if (match(w.substr(pos + 1), s.substr(pos + skip)))
                return true;
    // 이 외의 경우에는 모두 대응되지 않는다.
    return false;
}

// 8.7 와일드카드 문제를 해결하는 동적 계획법 알고리즘

// -1은 아직 답이 계산되지 않았음을 의미한다.
// 1은 해당 입력들이 서로 대응됨을 의미한다.
// 0은 해당 입력들이 서로 대응되지 않음을 의미한다.
int cache7[101][101];
// 패턴과 문자열
string W, S;
// 와일드 카드 패턴 W[w..]가 문자열 S[s..]에 대응되는지 여부를 반환한다.
bool matchMemoized(int w, int s)
{
    // 메모이제이션
    int &ret = cache7[w][s];
    if (ret != -1)
        return ret;
    // W[w]와 S[s]를 맞춰나간다.
    while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s]))
    {
        ++w;
        ++s;
    }
    // 더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다.
    // 2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
    if (w == W.size())
        return ret = (s == S.size());
    // 4. *를 만나서 끝난 경우: *에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다.
    if (W[w] == '*')
        for (int skip = 0; skip + s <= S.size(); ++skip)
            if (matchMemoized(w + 1, s + skip))
                return ret = 1;
    // 3. 이 외의 경우에는 모두 대응되지 않는다.
    return ret = 0;
}

// 8.8 삼각형 위의 최대 경로 문제를 푸는 메모이제이션 코드(1)

// MAX_NUMBER: 한 칸에 들어갈 숫자의 최대치
const int MAX_NUMBER = 100;
int n8, triangle8[100][100];
int cache8[100][100][MAX_NUMBER * 100 + 1];
// (y, x) 위치까지 내려오기 전에 만난 숫자들의 합이 sum일 때
// 맨 아래줄까지 내려가면 얻을 수 있는 최대 경로를 반환한다.
int path1(int y, int x, int sum)
{
    // 기저 사례: 맨 아래 줄까지 도달했을 경우
    if (y == n8 - 1)
        return sum + triangle8[y][x];
    // 메모이제이션
    int &ret = cache8[y][x][sum];
    if (ret != -1)
        return ret;
    sum += triangle8[y][x];
    return ret = max(path1(y + 1, x + 1, sum), path1(y + 1, x, sum));
}

// 8.9 삼각형 위의 최대 경로 문제를 푸는 동적 계획법 알고리즘 (2)

int n9, triangle9[100][100];
int cache9[100][100];
// (y, x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x)
{
    // 기저 사례
    if (y == n9 - 1)
        return triangle9[y][x];
    // 메모이제이션
    int &ret = cache9[y][x];
    if (ret != -1)
        return ret;
    return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle9[y][x];
}

// 8.10 쵀대 증가 부분 수열 문제를 해결하는 완전 탐색 알고리즘

int lis(const vector<int> &A)
{
    // 기서 사례: A가 텅 비어있을 때
    if (A.empty())
        return 0;
    int ret = 0;
    for (int i = 0; i < A.size(); ++i)
    {
        vector<int> B;
        for (int j = i + 1; j < A.size(); ++j)
            if (A[i] < A[j])
                B.push_back(A[j]);
        ret = max(ret, 1 + lis(B));
    }
    return ret;
}

// 8.11 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘 (1)

int n11;
int cache11[100], S11[100];
// S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis2(int start)
{
    int &ret = cache11[start];
    if (ret != -1)
        return ret;
    // 항상 S[start]는 있기 때문에 길이는 최하 1
    ret = 1;
    for (int next = start + 1; next < n11; ++next)
        if (S11[start] < S11[next])
            ret = max(ret, lis2(next) + 1);
    return ret;
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

// 8.13 합친 LIS 문제를 해결하는 동적 계획법 알고리즘

// 입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
// 인위적인 최소치는 64비트여야 한다.
const long long NEGINF = numeric_limits<long long>::min();
int n13, m13, A13[100], B13[100];
int cache13[101][101];
// min(A[indexA], B[indexB]), max(A[indexA], B[indexB])로 시작하는
// 합친 증가 부분 수열의 최대 길이를 반환한다.
// 단 indexA == indexB == -1 혹인 A[indexA] != B[indexB]라고 가정한다.
int jlis(int indexA, int indexB)
{
    // 메모이제이션
    int &ret = cache13[indexA + 1][indexB + 1];
    if (ret != -1)
        return ret;
    // A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있다.
    ret = 2;
    long long a = (indexA == -1 ? NEGINF : A13[indexA]);
    long long b = (indexB == -1 ? NEGINF : B13[indexB]);
    long long maxElement = max(a, b);
    // 다음 원소를 찾는다.
    for (int nextA = indexA + 1; nextA < n13; ++nextA)
        if (maxElement < A13[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for (int nextB = indexB + 1; nextB < m13; ++nextB)
        if (maxElement < B13[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    return ret;
}

// 8.14 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘

const int INF = 987654321;
string N14;
// N[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b)
{
    // 숫자 조각을 가져온다.
    string M = N14.substr(a, b - a + 1);
    // 첫 글자만으로 이루어진 문자열과 같으면 난이도는 1
    if (M == string(M.size(), M[0]))
        return 1;
    // 등자수열인지 검사한다.
    bool progressive = true;
    for (int i = 0; i < M.size(); ++i)
        if (M[i + 1] - M[i] != M[1] - M[0])
            progressive = false;
    // 등차수열이고 공차가 1 혹은 -1이면 난이도는 2
    if (progressive && abs(M[1] - M[0]) == 1)
        return 2;
    // 두 수가 번갈아 등장하는지 확인한다.
    bool alternating = true;
    for (int i = 0; i < M.size(); ++i)
        if (M[i] != M[i % 2])
            alternating = false;
    // 두 수가 번갈아 등장하면 난이도는 4
    if (alternating)
        return 4;
    // 공차가 1 아닌 등차수열의 난이도는 5
    if (progressive)
        return 5;
    // 이 외는 모두 난이도 10
    return 10;
}
int cache14[10002];
// 수열 N[begin..]를 외우는 방법 중 난이도의 최소 합을 출력한다.
int memorize(int begin)
{
    // 기서 사례: 수열의 끝에 도달했을 경우
    if (begin == N14.size())
        return 0;
    // 메모이제이션
    int &ret = cache14[begin];
    if (ret != -1)
        return ret;
    ret = INF;
    for (int L = 3; L <= 5; ++L)
        if (begin + L <= N14.size())
            ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
    return ret;
}

// 8.15 Quantization 문제의 구현

const int INF = 987654321;
// A[]: 양자화해야 할 수열, 정렬한 상태
// pSum[]: A[]의 부분합을 저장한다. pSum[i]는 A[0]..A[i]의 합
// pSqSum[]: A[]제곱의 부분합을 저장한다. pSqSum[i]는 A[0]^2..A[i]^2의 합
int n15;
int A15[101], pSum15[101], pSqSum15[101];
// A를 정렬하고 각 부분합을 계산한다.
void precalc()
{
    sort(A15, A15 + n15);
    pSum15[0] = A15[0];
    pSqSum15[0] = A15[0] * A15[0];
    for (int i = 1; i < n15; ++i)
    {
        pSum15[i] = pSum15[i - 1] + A15[i];
        pSqSum15[i] = pSqSum15[i - 1] + A15[i] * A15[i];
    }
}
// A[lo]..A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산한다.
int minError(int lo, int hi)
{
    // 부분합을 이용해 A[lo] ~ A[hi]까지의 합을 구한다.
    int sum = pSum15[hi] - (lo == 0 ? 0 : pSum15[lo - 1]);
    int sqSum = pSqSum15[hi] - (lo == 0 ? 0 : pSqSum15[lo - 1]);
    // 평균을 반올림한 값으로 이 수들을 표현한다.
    int m = int(0.5 + (double)sum / (hi - lo + 1));
    // sum(A[i] -m)^2를 전개한 결과로 부분 합으로 표현
    int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
    return ret;
}
int cache15[101][11];
int quantize(int from, int parts)
{
    // 기저 사례: 모든 숫자를 다 양지화했을 때
    if (from == n15)
        return 0;
    // 기저 사례: 숫자는 아직 남았는데 더 묶을 수 없을 대 아주 큰 값을 반환한다.
    if (parts == 0)
        return INF;
    int &ret = cache15[from][parts];
    if (ret != -1)
        return ret;
    ret = INF;
    // 조각의 길이를 변화시켜 가며 최소치를 찾는다.
    for (int partSize = 1; from + partSize <= n15; ++partSize)
        ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
    return ret;
}

// 8.16 타일링의 수를 세는 동적 계획법 알고리즘

const int MOD = 1000000007;
int cache16[101];
// 2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width)
{
    // 기저 사례: width가 1 이하일 때
    if (width <= 1)
        return 1;
    // 메모이제이션
    int &ret = cache16[width];
    if (ret != -1)
        return ret;
    return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

// 8.17 삼각형 위의 최대 경로의 수를 찾는 동적 계획법 알고리즘

// 8.9 코드의 변수와 함수를 재사용
int countCache[100][100];
// (y, x)에서 시작햇 맨 아래줄까지 내려가는 경로 중 최대 경로의 개수를 반환한다.
int count(int y, int x)
{
    // 기저사례: 맨 아래줄에 도달한 경우
    if (y == n9 - 1)
        return 1;
    // 메모이제이션
    int &ret = countCache[y][x];
    if (ret == -1)
        return ret;
    ret = 0;
    if (path2(y + 1, x + 1) >= path2(y + 1, x))
        ret += count(y + 1, x + 1);
    if (path2(y + 1, x + 1) <= path2(y + 1, x))
        ret += count(y + 1, x);
    return ret;
}

// 8.18 우물을 기어오르는 달팽이 문제를 해결하는 동적계획법 알고리즘

int n18, m18;
const int MAX_N = 1000;
int cache18[MAX_N][2 * MAX_N + 1];
// 달팽이가 days일 동안 climbed미터를 기어올라 왔다고 할 때,
// m일 전까지 n미터를 기어올라갈 수 있는 경우의 수
int climb(int days, int climbed)
{
    // 기저 사례: m일이 모두 지난 경우
    if (days == m18)
        return climbed >= n18 ? 1 : 0;
    // 메모이제이션
    int &ret = cache18[days][climbed];
    if (ret != -1)
        return ret;
    return ret = climb(days + 1, climbed + 1) + climb(days + 1, climbed + 2);
}

// 8.19 비대칭 타일링 문제를 해결하는 동적 계획법 알고리즘

// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric(int width)
{
    if (width % 2 == 1)
        return (tiling(width) - tiling(width / 2) + MOD) % MOD;
    int ret = tiling(width);
    ret = (ret - tiling(width / 2) + MOD) % MOD;
    ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
    return ret;
}

// 8.20 직접 비대칭 타일링의 수를 세는 동적 계획법 알고리즘

int cache20[101];
// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric2(int width)
{
    // 기저 사례: 너비가 2 이하인 경우
    if (width <= 2)
        return 0;
    // 메모이제이션
    int &ret = cache20[width];
    if (ret != -1)
        return ret;
    ret = asymmetric2(width - 2) % MOD;
    ret = (ret + asymmetric2(width - 4)) % MOD;
    ret = (ret + tiling(width - 3)) % MOD;
    ret = (ret + tiling(width - 3)) % MOD;
}

// 8.21 폴이오미노의 수 구하기

const int MOD2 = 10 * 1000 * 1000;
int cache21[101][101];
// n개의 정사각형으로 이루어졌고, 맨 위 가로줄에 first개의 정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first)
{
    // 기저 사례: n==first
    if (n == first)
        return 1;
    // 메모이제이션
    int &ret = cache21[n][first];
    if (ret != -1)
        return ret;
    ret = 0;
    for (int second = 1; second <= n - first; ++second)
    {
        int add = second + first - 1;
        add *= poly(n - first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
    }
    return ret;
}

// 8.22 두니발 박사의 탈옥 문제를 해결하는 완전 탐색 알고리즘

int n22, d22, p22, q22;
// connected[i][j] = 마을 i, j가 열결되어 있나 여부
// deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];
double search(vector<int> &path)
{
    // 기저 사례: d일이 지난 경우
    if (path.size() == d22 + 1)
    {
        // 이 시나리오가 q에서 끝나지 않는다면 무효
        if (path.back() != q22)
            return 0.0;
        // path의 출현 확률을 계산한다.
        double ret = 1.0;
        for (int i = 0; i + 1 < path.size(); ++i)
            ret /= deg[path[i]];
        return ret;
    }
    double ret = 0;
    // 경로의 다음 위치를 결정한다.
    for (int there = 0; there < n22; ++there)
        if (connected[path.back()][there])
        {
            path.push_back(there);
            ret += search(path);
            path.pop_back();
        }
    return ret;
}

// 8.23 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

int n23, d23, p23, q23;
// cache[][]는 -1로 초기화해 둔다.
double cache23[51][101];
// connected[i][j]=마을 i, j가 연결되어 있나 여부
// deg[i]=마을 i와 연결된 마을의 개수
int connected2[51][51], deg2[51];
// days일째에 here번 마을에 숨어 있다고 가정하고, 마지막 날에 q번 마을에 숨어 있을 조건부 확률을 반환한다.
double search2(int here, int days)
{
    // 기저 사례: d일이 지난 경우
    if (days == d23)
        return (here == q23 ? 1.0 : 0.0);
    // 메모이제이션
    double &ret = cache23[here][days];
    if (ret > -0.5)
        return ret;
    ret = 0.0;
    for (int there = 0; there < n23; ++there)
        if (connected2[here][there])
            ret += search2(there, days + 1) / deg[here];
    return ret;
}

// 8.24 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

int n24, d24, p24, q24;
double cache24[51][101];
// connected[i][j]=마을 i, j가 연결되어 있나 여부
// deg[i]=마을 i와 연결된 마을의 개수
int connected3[51][51], deg3[51];
double search3(int here, int days)
{
    // 기저 사례: 0 일째
    if (days == 0)
        return (here == p24 ? 1.0 : 0.0);
    // 메모이제이션
    double &ret = cache24[here][days];
    if (ret > -0.5)
        return ret;
    for (int there = 0; there < n24; ++there)
        if (connected3[here][there])
            ret += search3(there, days - 2) / deg[there];
    return ret;
}