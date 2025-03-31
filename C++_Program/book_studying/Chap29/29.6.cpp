#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

// 29.6 15-퍼즐을 해결하는 너비 우선 탐색 알고리즘

// 게임판의 상태를 표현한다.
class State
{
public:
    vector<vector<int>> board; // 4x4 게임 보드
    int zeroX, zeroY;          // 빈 칸(0)의 위치 저장

    // 생성자
    State(vector<vector<int>> b) : board(b)
    {
        // 빈 칸(0)의 위치 찾기
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (board[i][j] == 0)
                {
                    zeroX = i;
                    zeroY = j;
                    return;
                }
    }

    // 빈 칸을 이동하여 가능한 인접한 상태들을 반환
    vector<State> getAdjacent() const
    {
        vector<State> adjacentStates;
        const int dx[4] = {-1, 1, 0, 0}; // 상하좌우 이동
        const int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i)
        {
            int newX = zeroX + dx[i], newY = zeroY + dy[i];

            if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4)
            {
                State newState = *this;
                swap(newState.board[zeroX][zeroY], newState.board[newX][newY]); // 빈 칸 이동
                newState.zeroX = newX;
                newState.zeroY = newY;
                adjacentStates.push_back(newState);
            }
        }
        return adjacentStates;
    }

    // map에서 사용하기 위한 비교 연산자
    bool operator<(const State &rhs) const
    {
        return board < rhs.board; // 사전순 비교
    }

    // 목표 상태와 비교하는 연산자
    bool operator==(const State &rhs) const
    {
        return board == rhs.board;
    }

    // 보드를 출력하는 함수 (디버깅용)
    void print() const
    {
        for (const auto &row : board)
        {
            for (int num : row)
                cout << num << " ";
            cout << "\n";
        }
        cout << "------------\n";
    }
};
typedef map<State, int> StateMap;
// start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bfs(State start, State finish)
{
    // 예외: start == finish인 경우
    if (start == finish)
        return 0;
    // 각 정점까지의 최단 경로의 길이를 저장한다.
    StateMap c;
    // 앞으로 방문할 정점들을 저장한다.
    queue<State> q;
    q.push(start);
    c[start] = 0;
    // 너비 우선 탐색
    while (!q.empty())
    {
        State here = q.front();
        q.pop();
        int cost = c[here];
        // 인접한 정점들의 번호를 얻어낸다.
        vector<State> adjacent = here.getAdjacent();
        for (int i = 0; i < adjacent.size(); ++i)
        {
            if (c.count(adjacent[i]) == 0)
            {
                // 답을 찾았나?
                if (adjacent[i] == finish)
                    return cost + 1;
                c[adjacent[i]] = cost + 1;
                q.push(adjacent[i]);
            }
        }
    }
    // 답을 찾지 못한 경우
    return -1;
}

// 29.7 15-퍼즐 문제를 해결하는 양방향 탐색 알고리즘

// 15-퍼즐 문제의 상태를 표현하는 클래스
class State;
// x의 부호를 반환한다.
int sgn(int x)
{
    if (!x)
        return 0;
    return x > 0 ? 1 : -1;
}
// x의 절대값을 1 증가시킨다.
int incr(int x)
{
    if (x < 0)
        return x - 1;
    return x + 1;
}
// start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bidirectional(State start, State finish)
{
    // 각 정점까지의 최단 경로의 길이를 저장한다.
    map<State, int> c;
    // 앞으로 방문할 정점들을 저장한다.
    queue<State> q;
    // 시작 상태와 목표 상태가 같은 경우는 예외로 처리해야 한다.
    if (start == finish)
        return 0;
    q.push(start);
    c[start] = 1;
    q.push(finish);
    c[finish] = -1;
    // 너비 우선 탐색
    while (!q.empty())
    {
        State here = q.front();
        q.pop();
        // 인접한 상태들을 검사한다.
        vector<State> adjacent = here.getAdjacent();
        for (int i = 0; i < adjacent.size(); ++i)
        {
            map<State, int>::iterator it = c.find(adjacent[i]);
            if (it == c.end())
            {
                c[adjacent[i]] = incr(c[here]);
                q.push(adjacent[i]);
            }
            // 가운데서 만난 경우
            else if (sgn(it->second) != sgn(c[here]))
                return abs(it->second) + abs(c[here]) - 1;
        }
    }
    // 답을 찾지 못한 경우
    return -1;
}

// 29.8 15-퍼즐 문제를 해결하는 점점 깊어지는 탐색 알고리즘

// 15-퍼즐 문제의 상태를 표현하는 클래스
class State;
int best;
// 깊이 우선 탐색
void dfs(State here, const State &finish, int steps)
{
    // 지금까지 구한 최적해보다 더 좋을 가능성이 없으면 버린다.
    if (steps >= best)
        return;
    // 목표 상태에 도달한 경우
    if (here == finish)
    {
        best = steps;
        return;
    }
    // 인접 상태들을 깊이 우선 탐색으로
    vector<State> adjecent = here.getAdjacent();
    for (int i = 0; i < adjecent.size(); ++i)
        dfs(adjecent[i], finish, steps + 1);
}
// 점점 깊어지는 탐색
int ids(State start, State finish, int growthStep)
{
    for (int limit = 4;; limit += growthStep)
    {
        best = limit + 1;
        dfs(start, finish, 0);
        if (best <= limit)
            return best;
    }
    return -1;
}