// 최대 연속 부분 구간 합 문제를 푸는 동적 계획법 알고리즘

// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(N)
#include <vector>
#include <limits>
using namespace std;
const int MIN = numeric_limits<int>::min();
int fastestMaxSum(const vector<int>& A){
    int N = A.size(), ret = MIN, psum = 0;
    for (int i = 0; i < N; ++i){
        psum = max(psum, 0) + A[i];
        ret = max(psum, ret);
    }
    return ret;
}