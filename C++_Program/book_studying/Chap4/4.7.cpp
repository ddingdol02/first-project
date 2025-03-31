// 선형 탐색
// array[i] = element인 첫 i를 반환한다. 없으면 -1을 반환한다.
#include <vector>
using namespace std;

int firstIndex(const vector<int>& array, int element){
    for (int i = 0; i < array.size(); ++i){
        if(array[i] == element)
            return i;
    }
    return -1;
}