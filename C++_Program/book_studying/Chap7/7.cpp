#include <vector>
#include <cmath>
#include <string>
using namespace std;

// 7.1 1부터 n까지의 합을 구하는 분할 정복 알고리즘

// 필수 조건: n은 자연수
// 1+2+3+...+n을 반환한다.
int fastSum(int n)
{
    // 기저 사례
    if (n == 1)
        return 1;
    if (n % 2 == 1)
        return fastSum(n - 1) + n;
    return 2 * fastSum(n / 2) + (n / 2) * (n / 2);
}

// 7.2 행렬의 거듭제곱을 구하는 분할 정복 알고리즘

// 정방행렬을 표현하는 SquareMatrix 클래스가 있다고 가정하자.
class SuqareMatrix;
// n*n 크기의 항등행렬(identity matrix)을 반환하는 함수
SuqareMatrix identity(int n);
// A^m을 반환한다.
SuqareMatrix pow(const SuqareMatrix &A, int m)
{
    // 기저 사례: A^0 = I
    if (m == 0)
        return identity(A.size());
    if (m % 2 > 0)
        return pow(A, m - 1) * A;
    SuqareMatrix half = pow(A, m / 2);
    // A^m = (A^(m/2)) * (A^(m/2))
    return half * half;
}

// 7.3 두 큰 수를 곱하는 O(n^2) 시간 알고리즘

// num[]의 자릿수 올림을 처리한다.
void normalize(vector<int> &num)
{
    num.push_back(0);
    // 자릿수 올림을 처리한다.
    for (int i = 0; i + 1 < num.size(); ++i)
    {
        if (num[i] < 0)
        {
            int borrow = (abs(num[i]) + 9) / 10;
            num[i + 1] -= borrow;
            num[i] += borrow * 10;
        }
        else
        {
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while (num.size() > 1 && num.back() == 0)
        num.pop_back();
}
// 두 긴 자연수의 곱을 반환한다.
// 각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다.
// 예: mutiply({3, 2, 1}, {6, 5, 4}) = 123 * 456 = 56088 = {8, 8, 0, 6, 5}
vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
    vector<int> c(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size(); ++j)
            c[i + j] += a[i] * b[j];
    normalize(c);
    return c;
}

// 7.4 카라츠바의 빠른 정수 곱셈 알고리즘

// a += b * (10^k); 를 구현한다.
void addTo(vector<int> &a, const vector<int> &b, int k);
// a -= b;를 구현한다. a >= b를 가정한다.
void subFrom(vector<int> &a, const vector<int> &b);
// 두 긴 정수의 곱을 반환한다.
vector<int> karatsuba(const vector<int> &a, const vector<int> &b)
{
    int an = a.size(), bn = b.size();
    // a가 b보다 짧을 경우 둘을 바꾼다.
    if (an < bn)
        return karatsuba(b, a);
    // 기저 사례: a나 b가 비어 있는 경우
    if (an == 0 || bn == 0)
        return vector<int>();
    // 기저 사례: a가 비교적 짧은 경우 O(n^2) 곱셈으로 변경한다.
    if (an <= 50)
        return multiply(a, b);
    int half = an / 2;
    // a와 b를 밑에서 half 자리와 나머지로 분리한다.
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    // z2 = a1 * b1
    vector<int> z2 = karatsuba(a1, b1);
    // z0 = a0 * b0
    vector<int> z0 = karatsuba(a0, b0);
    // a0 = a0 + a1; b0 = b0 + b1
    addTo(a0, a1, 0);
    addTo(b0, b1, 0);
    // z1 = (a0 * b0) - z0 - z2
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    // ret = z0 + z1 * 10^half + z2 * (half*2)
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}

// 7.5 쿼드 트리 압축을 해제하는 재귀 호출 알고리즘
const int MAX_SIZE = 20;

char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator &it, int y, int x, int size)
{
    // 한 글자를 검사할 때마다 반복자를 한 칸 앞으로 옮긴다.
    char head = *(it++);
    // 기저 사례: 첫 글자가 b 또는 w인 경우
    if (head == 'b' || head == 'w')
    {
        for (int dy = 0; dy < size; ++dy)
            for (int dx = 0; dx < size; ++dx)
                decompressed[y + dy][x + dx] = head;
    }
    else
    {
        // 네 부분으로 각각 순서대로 압축 해제한다.
        int half = size / 2;
        decompress(it, y, x, half);
        decompress(it, y, x + half, half);
        decompress(it, y + half, x, half);
        decompress(it, y + half, x + half, half);
    }
}

// 7.6 쿼드 트리 뒤집기 문제를 해결하는 분할 정복 알고리즘

string reverse(string::iterator &it)
{
    char head = *it;
    ++it;
    if (head == 'b' || head == 'w')
        return string(1, head);
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    // 각각 위와 아래 조각들의 위치를 바꾼다.
    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

// 7.7 울타리 잘라내기 문제를 해결하는 O(n^2) 알고리즘

// 판자의 높이를 담은 배열 h[]가 주어질 때 사각형의 최대 너비를 반환한다.
int bruteForce(const vector<int> &h)
{
    int ret = 0;
    int N = h.size();
    // 가능한 모든 left, right 조합을 순회한다.
    for (int left = 0; left < N; ++left)
    {
        int minHeight = h[left];
        for (int right = left; right < N; ++right)
        {
            minHeight = min(minHeight, h[right]);
            ret = max(ret, (right - left + 1) * minHeight);
        }
    }
    return ret;
}

// 7.8 울타리 잘라내기 문제를 해결하는 분할 정복 알고리즘

// 각 판자의 높이를 저장하는 배열
vector<int> h;
// h[left..right] 구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이를 반환한다.
int solve(int left, int right)
{
    // 기저 사례: 판자가 하나 밖에 없는 경우
    if (left == right)
        return h[left];
    // [left, mid], [mid+1, right]의 두 구간으로 문제를 분할한다.
    int mid = (left + right) / 2;
    // 분할한 문제를 각개격파
    int ret = max(solve(left, mid), solve(mid + 1, right));
    // 부분 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
    int lo = mid, hi = mid + 1;
    int height = min(h[lo], h[hi]);
    // [mid, mid+1]만 포함하는 너비 2인 사각형을 고려한다.
    ret = max(ret, height * 2);
    // 사각형이 입력 전체를 덮을 때가지 확장해 나간다.
    while (left < lo || hi < right)
    {
        // 항상 높이가 더 높은 쪽으로 확장한다.
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1]))
        {
            ++hi;
            height = min(height, h[hi]);
        }
        else
        {
            --lo;
            height = min(height, h[lo]);
        }
        // 확장한 후 사각형의 넓이
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}

// 7.9 카라츠바의 빠른 곱셈을 이용해 팬미팅 문제를 해결하는 함수

int hugs(const string &members, const string &fans)
{
    int N = members.size(), M = fans.size();
    vector<int> A(N), B(M);
    for (int i = 0; i < N; ++i)
        A[i] = (members[i] == 'M');
    for (int i = 0; i < M; ++i)
        B[M - i - 1] = (fans[i] == 'M');
    // karatsuba 알고리즘에서 자리 올림은 생략한다.
    vector<int> C = karatsuba(A, B);
    int allHugs = 0;
    for (int i = N - 1; i < M; ++i)
        if (C[i] == 0)
            ++allHugs;
    return allHugs;
}