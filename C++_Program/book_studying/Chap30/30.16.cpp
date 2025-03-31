#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 30.10 새 간선이 그래프에 추가되었을 때 최단 거리 갱신하기

// adj[][]는 floyd()의 수행 결과
int V, adj[200][200];
// 간선 (a, b)를 추가했을 때 그래프의 최단 거리 배열 adj를
// 적절히 갱신한다. 간선이 아무런 의미가 없을 경우 false를 반환한다.
bool update(int a, int b, int c)
{
    if (adj[a][b] <= c)
        return false;
    for (int x = 0; x < V; ++x)
        for (int y = 0; y < V; ++y)
            // x~y 최단경로가 (a, b)를 이용하면
            // x~a-b~y 혹은 x~b-a~y의 형태를 가져야 한다.
            adj[x][y] = min(adj[x][y], min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[a][y]));
    return true;
}