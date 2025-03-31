#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// 28.8 간선을 구분하는 깊이 우선 탐색의 구현

// 그래프의 인접 리스트 표현
vector<vector<int>> adj;
// discovered[i] = i번 정점의 발견 순서
// finished[i] = dfs(i)가 종료했으면 1, 아니면 0
vector<int> discovered, finished;
// 지금까지 발견한 정점의 수
int counter;

void dfs2(int here)
{
    discovered[here] = counter++;
    // 모든 인접 정점을 순회하면서
    for (int i = 0; i < adj[here].size(); ++i)
    {
        int there = adj[here][i];
        cout << "(" << here << "," << there << ") is a ";
        // 아직 방문한 적 없다면 방문한다.
        if (discovered[there] == -1)
        {
            cout << "tree edge" << endl;
            dfs2(there);
        }
        // 만약 there가 here보다 늦게 발견됐으면 there은 here의 후손이다.
        else if (discovered[here] < discovered[there])
            cout << "forward edge" << endl;
        // 만약 disf(there)가 아직 종료하지 않았으면 there은 here의 선조다.
        else if (finished[there] == 0)
            cout << "back edge" << endl;
        // 이 외의 경우는 모두 교차 간선
        else
            cout << "cross edge" << endl;
    }
    finished[here] = 1;
}

// 28.9 무향 그래프에서 절단점을 찾는 알고리즘

// 그래프의 인접 리스트 표현
vector<vector<int>> adj;
// 각 정점의 발견 순서. -1로 초기화한다.
vector<int> discovered;
// 각 정점이 절단점인지 여부를 저장한다. false로 초기화한다.
vector<bool> isCutVertex;
int counter = 0;
// here를 루트로 하는 서브트리에 있는 절단점들을 찾는다.
// 반환 값은 해당 서브트리에서 역방향 간선으로 갈 수 있는 정점 중
// 가장 일찍 발견된 정점의 발견 시점. 처음 호출할 때는 isRoot=true로 둔다.
int findCutVertex(int here, bool isRoot)
{
    // 발견 순서를 기록한다.
    discovered[here] = counter++;
    int ret = discovered[here];
    // 루트인 경우의 절단점 판정을 위해 자손 서브트리의 개수를 센다.
    int children = 0;
    for (int i = 0; i < adj[here].size(); ++i)
    {
        int there = adj[here][i];
        if (discovered[there] == -1)
        {
            ++children;
            // 이 서브트리에서 갈 수 있는 가장 높은 정점의 번호
            int subtree = findCutVertex(there, false);
            // 그 노드가 자기 자신 이하에 있다면 현재 위치는 절단점!
            if (!isRoot && subtree >= discovered[here])
                isCutVertex[here] = true;
            ret = min(ret, subtree);
        }
        else
            ret = min(ret, discovered[there]);
    }
    // 루트인 경우 절단점 판정은 서브트리의 개수로 한다.
    if (isRoot)
        isCutVertex[here] = (children >= 2);
    return ret;
}

// 28.10 타잔의 강결합 컴포넌트 분리 알고리즘의 구현

// 그래프의 인접 리스트 표현
vector<vector<int>> adj;
// 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0부터 시작하며,
// 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId;
// 각 정점의 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> st;
int sccCounter, vertexCounter;
// here를 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을
// 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다.
// (이미 SCC로 묶인 정점으로 연결된 교차 간선은 무시한다)
int scc(int here)
{
    int ret = discovered[here] = vertexCounter++;
    // 스택에 here를 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다.
    st.push(here);
    for (int i = 0; i < adj[here].size(); ++i)
    {
        int there = adj[here][i];
        // (here, there)가 트리 간선
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        // there가 무시해야 하는 교차 간선이 아니라면
        else if (sccId[there] == -1)
            ret = min(ret, discovered[there]);
    }
    // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
    if (ret == discovered[here])
    {
        // here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
        while (true)
        {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here)
                break;
        }
        ++sccCounter;
    }
    return ret;
}
// tarjan의 SCC 알고리즘
vector<int> tarjanSCC()
{
    // 배열들을 전부 초기화
    sccId = discovered = vector<int>(adj.size(), -1);
    // 카운터 초기화
    sccCounter = vertexCounter = 0;
    // 모든 정점에 대해 scc() 호출
    for (int i = 0; i < adj.size(); i++)
        if (discovered[i] == -1)
            scc(i);
    return sccId;
}