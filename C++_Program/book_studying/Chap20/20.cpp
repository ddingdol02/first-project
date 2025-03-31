#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

// 20.1 단순한 문자열 검색 알고리즘의 구현

// '짚더미' H의 부분 문자열로 '바늘'N이 출현하는 시작 위치들을 모두 반환한다.
vector<int> naiveSearch(const string &H, const string &N)
{
    vector<int> ret;
    // 모든 시작 위치를 다 시도해본다.
    for (int begin = 0; begin + N.size() <= H.size(); ++begin)
    {
        bool matched = true;
        for (int i = 0; i < N.size(); ++i)
            if (H[begin + i] != N[i])
            {
                matched = false;
                break;
            }
        if (matched)
            ret.push_back(begin);
    }
    return ret;
}

// 20.2 커누스-모리스-프랫(KMP) 문자열 검색 알고리즘의 구현

// '짚더미' H의 부분 문자열로 '바늘'N이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string &H, const string &N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    // pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
    vector<int> pi = getPartialMatch(N);
    // begin=matched=0에서부터 시작하자.
    int begin = 0, matched = 0;
    while (begin <= n - m)
    {
        // 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
        if (matched < m && H[begin + matched] == N[matched])
        {
            ++matched;
            // 결과적으로 m글자가 모두 일치했다면 답에 추가한다.
            if (matched == m)
                ret.push_back(begin);
        }
        else
        {
            // 예외: matched가 0인 경우에는 다음 칸에서부터 계속
            if (matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched - 1];
                // begin을 옮겼다고 처음부터 다시 비교할 필요가 없다.
                // 옮긴 후에도 pi[matched-1]만큼은 항상 일치하기 때문이다.
                matched = pi[matched - 1];
            }
        }
    }
}

// 20.3 단순한 문자열 알고리즘을 이용해 부분 일치 테이블 계산하기

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산한다.
// pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatchNaive(const string &N)
{
    int m = N.size();
    vector<int> pi(m, 0);
    // 단순한 문자열 검색 알고리즘을 구현한다.
    for (int begin = 1; begin < m; ++begin)
    {
        for (int i = 0; i + begin < m; ++i)
        {
            if (N[begin + i] != N[i])
                break;
            // i+1 글자가 서로 되응되었다.
            pi[begin + i] = max(pi[begin + i], i + 1);
        }
    }
    return pi;
}

// 20.4 KMP 알고리즘을 이용해 부분 일치 테이블을 생성하기

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산한다.
// pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatch(const string &N)
{
    int m = N.size();
    vector<int> pi(m, 0);
    // KMP로 자기 자신을 찾는다.
    // N을 N에서 찾는다. begin=0이면 자기 자신을 찾아버리니까 안됨.
    int begin = 1, matched = 0;
    // 비교할 문자가 N의 끝에 도달했을 때까지 찾으면서 부분 일치로 모두 기록한다.
    while (begin + matched < m)
    {
        if (N[begin + matched] == N[matched])
        {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else
        {
            if (matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

// 20.5 S의 접두사도 되고 접미사도 되는 모둔 문자열의 길이를 계산하기

// s의 접두사도 되고 접미사도 되는 문자열들의 길이를 반환한다.
vector<int> getPrefixSuffix(const string &s)
{
    vector<int> ret, pi = getPartialMatch(s);
    int k = s.size();
    while (k > 0)
    {
        // s[..k-1]는 답이다.
        ret.push_back(k);
        // s[..k-1]의 접미사도 되고 접두사도 되는 문자열도 답이다.
        k = pi[k - 1];
    }
    return ret;
}

// 20.6 팰린드롬 만들기 문제를 해결하는 KMP 알고리즘의 변형

// a의 접미사이면서 b의 접두사인 문자열의 최대 길이를 구한다.
int maxOverlap(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
    // begin = matched = 0에서부터 시작하자.
    int begin = 0, matched = 0;
    while (begin < n)
    {
        // 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
        if (matched < m && a[begin + matched] == b[matched])
        {
            ++matched;
            if (begin + matched == n)
                return matched;
        }
        else
        {
            if (matched == 0)
                ++begin;
            else
            {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return 0;
}

// 20.7 KMP 알고리즘의 다른 구현

vector<int> kmpSearch2(const string &H, const string &N)
{
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    // 현재 대응된 글자의 수
    int matched = 0;
    // 짚더미의 각 글자를 순회한다.
    for (int i = 0; i < n; ++i)
    {
        // matched번 글자와 짚더미의 해당 글자가 불일치할 경우, 현재 대응된 글자의 수를 pi[matched-1]로 줄인다.
        while (matched > 0 && H[i] != N[matched])
            matched = pi[matched - 1];
        // 글자가 대응될 경우
        if (H[i] == N[matched])
        {
            ++matched;
            if (matched == m)
            {
                ret.push_back(i - m + 1);
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}

// 20.8 접미사 배열을 계산하는 단순한 알고리즘

// 두 접미사의 시작 위치 i, j가 주어질 때 두 접미사 중 어느 쪽이 앞에 와야 할지 비교한다.
struct SuffixComparator
{
    const string &s;
    SuffixComparator(const string &s) : s(s) {}
    bool operator()(int i, int j)
    {
        // s.substr() 대신에 strcmp()를 쓰면 임시 객체를 만드는 비용이 절약된다.
        return strcmp(s.c_str() + i, s.c_str() + j) < 0;
    }
};
// s의 접미사 배열을 계산한다.
vector<int> getSuffixArrayNaive(const string &s)
{
    // 접미사 시작 위치를 담은 배열을 만든다.
    vector<int> perm;
    for (int i = 0; i < s.size(); ++i)
        perm.push_back(i);
    // 접미사를 비교하는 비교자를 이용해 정렬하면 완성!
    sort(perm.begin(), perm.end(), SuffixComparator(s));
    return perm;
}

// 20.9 첫 t글자로 묶인 그룹 정보를 이용해 첫 2t글자를 비교하는 비교자의 구현

// 각 접미사들의 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
// 주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다.
// group[]은 길이가 0인 접미사도 포함한다.
struct Comparator
{
    const vector<int> &group;
    int t;
    Comparator(const vector<int> &_group, int _t) : group(_group), t(_t)
    {
        // group = _group;
        t = _t;
    }
    bool operator()(int a, int b)
    {
        // 첫 t글자가 다르면 이들을 이용해 비교한다.
        if (group[a] != group[b])
            return group[a] < group[b];
        // 아니라면 S[a+t..]와 S[b+t..]의 첫 t글자를 비교한다.
        return group[a + t] < group[b + t];
    }
};

// 20.10 접미사 배열을 계산하는 맨버와 마이어스의 알고리즘

// s의 접미사 배열을 계산한다.
vector<int> getSuffixArray(const string &s)
{
    int n = s.size();
    // group[i]=접미사들을 첫 t글자를 기준으로 정렬했을 때, S[i..]가 들어가는 그룹 번호.
    // t=1일 때는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를 정해 줘도 같은 효과가 있다.
    int t = 1;
    vector<int> group(n + 1);
    for (int i = 0; i < n; ++i)
        group[i] = s[i];
    group[n] = -1;
    // 결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다.
    vector<int> perm(n);
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    while (t < n)
    {
        // group[]은 첫 t글자를 기준으로 계산해 뒀다.
        // 첫 2t글자를 기준으로 perm을 다시 정렬한다.
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        // 2t글자가 n을 넘는다면 이제 접미사 배열 완성!
        t *= 2;
        if (t >= n)
            break;
        // 2t글자를 기준으로 한 그룹 정보를 만든다.
        vector<int> newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; ++i)
            if (compareUsing2T(perm[i - 1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i - 1]];
        group = newGroup;
    }
    return perm;
}

// 20.11 접미사 배열을 사용해 원형 문자열 문제를 해결하는 알고리즘의 구현

// 사전순으로 가장 앞에 오는 s의 회전 결과를 구한다.
string minShift(const string &s)
{
    string s2 = s + s;
    vector<int> a = getSuffixArray(s2);
    for (int i = 0; i < a.size(); ++i)
        if (a[i] <= s.size())
            return s2.substr(a[i], s.size());
    // 여기로 올 일은 없어야 한다.
    return "___oops___";
}

// 20.12 접미사 배열을 이용해 다른 부분 문자열의 수를 세는 알고리즘

// s[i..]와 s[j..]이 공통 접두사의 최대 길이를 계산한다.
int commonPrefix(const string &s, int i, int j)
{
    int k = 0;
    while (i < s.size() && j < s.size() && s[i] == s[j])
    {
        ++i, ++j, ++k;
    }
    return k;
}
// s의 서로 다른 부분 문자열의 수를 센다.
int countSubstrings(const string &s)
{
    vector<int> a = getSuffixArray(s);
    int ret = 0;
    int n = s.size();
    for (int i = 0; i < a.size(); ++i)
    {
        int cp = 0;
        if (i > 0)
            cp = commonPrefix(s, a[i - 1], a[i]);
        // a[i]의 (n-a[i])개의 접두사들 중에서 cp개는 중복이다.
        ret += n - a[i] - cp;
    }
    return ret;
}

// 20.13 접미사 배열을 이용해 말버릇 문제를 해결하는 알고리즘

// s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다. 코드 20.12 참조.
int commonPrefix(const string &s, int i, int j);

// k번 이상 출현하는 s의 부분 문자열 중 최대 길이를 찾는다.
int longestFrequent(int k, const string &s)
{
    vector<int> a = getSuffixArray(s);
    int ret = 0;
    for (int i = 0; i + k <= s.size(); ++i)
        ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
    return ret;
}