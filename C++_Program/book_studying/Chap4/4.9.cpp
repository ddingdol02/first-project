// 최대 연속 부분 구간 합 문제를 푸는 무식한 알고리즘들
#include <vector>
#include <limits>
using namespace std;

const int MIN = numeric_limits<int>::min();
// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(N^3)
int inefficientMaxSum(const vector<int>& A){
    int N = A.size(), ret = MIN;
    for (int i = 0; i < N; ++i)
        for (int j = i; j < N; ++j){
            // 구간 A[i..j]의 합을 구한다.
            int sum = 0;
            for (int k = i; k <= j; ++k)
                sum += A[k];
            ret = max(ret, sum);
        }
    return ret;
}
// A[]의 연속된 부분 구간의 최대 합을 구한다. 시간 복잡도: O(N^2)
int betterMaxSum(const vector<int>& A){
    int N = A.size(), ret = MIN;
    for (int i = 0; i < N; ++i){
        int sum = 0;
        for (int j = i; j < N; ++j){
            // 구간 A[i..j]의 합을 구한다.
            sum += A[j];
            ret = max(ret, sum);
        }
    }
    return ret;
}