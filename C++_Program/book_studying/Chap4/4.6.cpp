// 가장 간단한 형태의 소인수 분해 알고리즘
// 자연수 n의 소인수 분해 결과를 담은 정수 배열을 반환한다.
#include <vector>
using namespace std;

vector<int> factor(int n){
    if(n==1)
        return vector<int>(1, 1);   // n = 1인 경우는 제외한다.
    vector<int> ret;
    for (int div = 2; n > 1; ++div){
        while(n%div == 0){
            n /= div;
            ret.push_back(div);
        }
    }
    return ret;
}