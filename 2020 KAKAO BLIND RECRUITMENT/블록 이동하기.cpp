#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, x1, y1, x2, y2, d;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int visit[100][100][4]; //x좌표, y좌표, 방향

struct robot
{
    int x, y, d;
};

bool isWall(int x, int y)
{
    return x < 0 || x >= N || y < 0 || y >= N;
}

int solution(vector<vector<int>> board)
{
    int answer = 0;
    N = board.size();
    memset(visit, false, sizeof(visit));
    visit[0][0][1] = true;
    visit[0][1][3] = true;

    queue<pair<robot, int>> q; //{{x,y,d},dist}
    q.push({{0, 0, 1}, 0});
    while (!q.empty())
    {
        robot r = q.front().first;
        d = r.d;
        x1 = r.x;
        y1 = r.y;
        x2 = x1 + dx[d];
        y2 = y1 + dy[d];
        int dist = q.front().second;
        q.pop();
        if ((x1 == N - 1 && y1 == N - 1) || (x2 == N - 1 && y2 == N - 1))
        {
            answer = dist;
            break;
        }

        // 4방향 이동 가능 체크
        for (int i = 0; i < 4; i++)
        {
            int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
            int nx2 = x2 + dx[i], ny2 = y2 + dy[i];
            // 범위를 벗어나거나 벽이 하나라도 있으면 이동 불가
            if (isWall(nx1, ny1) || isWall(nx2, ny2) || board[nx1][ny1] == 1 || board[nx2][ny2] == 1)
                continue;
            // 이미 방문했던 곳이면 이동 불가
            if (visit[nx1][ny1][d])
                continue;
            q.push({{nx1, ny1, d}, dist + 1});
            visit[nx1][ny1][d] = true;
            visit[nx2][ny2][(d + 2) % 4] = true;
        }
        // 회전 방향 체크
        // 1. 가로 모양일 때
        if (d == 1 || d == 3)
        {
            for (int i = 0; i <= 2; i += 2) // 상, 하 방면으로 확인.
            {
                int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
                int nx2 = x2 + dx[i], ny2 = y2 + dy[i];
                // 범위를 벗어났거나, 벽이 있는 경우 -> 회전할 수 없음.
                if (isWall(nx1, ny1) || isWall(nx2, ny2) || board[nx1][ny1] == 1 || board[nx2][ny2] == 1)
                    continue;
                // 회전 (각 축을 중심으로)
                if (!visit[x1][y1][i])
                { // (x1, y1)를 축으로.
                    visit[x1][y1][i] = true;
                    visit[nx1][ny1][(i + 2) % 4] = true;
                    q.push({{x1, y1, i}, dist + 1});
                }
                if (!visit[x2][y2][i])
                { // (x2, y2)를 축으로.
                    visit[x2][y2][i] = true;
                    visit[nx2][ny2][(i + 2) % 4] = true;
                    q.push({{x2, y2, i}, dist + 1});
                }
            }
        }
        // 2. 세로 모양일 때
        else
        {
            for (int i = 1; i <= 3; i += 2)
            {
                int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
                int nx2 = x2 + dx[i], ny2 = y2 + dy[i];
                // 범위를 벗어났거나, 벽이 있는 경우 -> 회전할 수 없음.
                if (isWall(nx1, ny1) || isWall(nx2, ny2) || board[nx1][ny1] == 1 || board[nx2][ny2] == 1)
                    continue;
                // 회전 (각 축을 중심으로)
                if (!visit[x1][y1][i])
                { // (x1, x2)를 축으로.
                    visit[x1][y1][i] = true;
                    visit[nx1][ny1][(i + 2) % 4] = true;
                    q.push({{x1, y1, i}, dist + 1});
                }
                if (!visit[x2][y2][i])
                {
                    visit[x2][y2][i] = true;
                    visit[nx2][ny2][(i + 2) % 4] = true;
                    q.push({{x2, y2, i}, dist + 1});
                }
            }
        }
    }
    return answer;
}