#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 987654321;
const int MAX_V = 50;

// 30.3 다익스트라 알고리즘을 이용해 철인 N종 경기 문제를 해결하기

// 정점의 개수
int V;
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[410];
const int START = 401;
// (A국 선수의 예상 시간 - B국 선수의 예상 시간)의 정점 번호를 반환한다.
int vertex(int delta)
{
    return delta + 200;
}
// a[]=A국 선수의 종목별 예상 시간
// b[]=B국 선수의 종목별 예상 시간
int solve(const vector<int> &a, const vector<int> &b)
{
    // 그래프를 만든다.
    V = 402;
    for (int i = 0; i < V; ++i)
        adj[i].clear();
    for (int i = 0; i < a.size(); i++)
    {
        int delta = a[i] - b[i];
        adj[START].push_back(make_pair(vertex(delta), a[i]));
    }
    // 현재 차이
    for (int delta = -200; delta <= 200; ++delta)
    {
        // i번 종목을 뒤에 붙인다면?
        for (int i = 0; i < a.size(); ++i)
        {
            int next = delta + a[i] - b[i];
            // 시간 차이의 절대 값이 200을 넘는 정점은 만들 필요가 없다.
            if (abs(next) > 200)
                continue;
            adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
        }
    }
    vector<int> shortest = dijkstra(START);
    int ret = shortest[vertex(0)];
    if (ret == INF)
        return -1;
    return ret;
}

vector<int> dijkstra(int src)
{
    vector<int> dist(V, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty())
    {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것은 무시한다.
        if (dist[here] < cost)
            continue;
        // 인접한 정점들을 모두 검사한다.
        for (int i = 0; i < adj[here].size(); ++i)
        {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;
            // 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            if (dist[there] > nextDist)
            {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
    return dist;
}

// 30.4 벨만-포드 알고리즘의 구현

// 정점의 개수
int V;
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
// 음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<int> bellanFord(int src)
{
    // 시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
    vector<int> upper(V, INF);
    upper[src] = 0;
    bool updated;
    // V번 순회한다.
    for (int iter = 0; iter < V; ++iter)
    {
        updated = false;
        for (int here = 0; here < V; ++here)
            for (int i = 0; i < adj[here].size(); ++i)
            {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                // (here, there) 간선을 따라 완화를 시도한다.
                if (upper[there] > upper[here] + cost)
                {
                    // 성공
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        // 모든 간선에 대해 완화가 실패했을 경우 V-1번도 돌 필요 없이 곧장 종료한다.
        if (!updated)
            break;
    }
    // V번째 순회에서도 완화가 성공했다면 음수 사이클이 있다.
    if (updated)
        upper.clear();
    return upper;
}