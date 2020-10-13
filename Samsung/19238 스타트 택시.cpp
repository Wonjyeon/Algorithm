#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX 21
#define INF 987654321
using namespace std;

struct Customer{
    int sx, sy, dx, dy;
};
Customer customer[MAX*MAX];
int N, M, Fuel, tx, ty;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int map[MAX][MAX];

bool cmp(int a, int b){
    Customer A = customer[a];
    Customer B = customer[b];

    if(A.sx == B.sx) return A.sy < B.sy;
    return A.sx < B.sx;
}

int find_closest_customer(){
    queue<pair<pair<int, int>, int>> q;
    bool visited[MAX][MAX] = {false, };
    q.push({{tx, ty}, 0});
    visited[tx][ty] = true;
    int minDist = INF;
    vector<int> minCust;

    while(!q.empty()){
        int x = q.front().first.first;
        int y = q.front().first.second;
        int d = q.front().second;
        q.pop();
        if(Fuel - d < 0) break;
        if(map[x][y] >= 1 && d <= minDist){
            minDist = d;
            minCust.push_back(map[x][y]);
            continue;
        }
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if(map[nx][ny] == -1 || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({{nx, ny}, d+1});
        }
    }
    if(minCust.size() == 0) return -1;
    sort(minCust.begin(), minCust.end(), cmp);
    Fuel -= minDist;
    int minCustId = minCust[0];
    map[customer[minCustId].sx][customer[minCustId].sy] = 0;
    return minCustId;
}
bool bfs(int sx, int sy, int destX, int destY, int custId){
    queue<pair<pair<int, int>, int>> q;
    bool visited[MAX][MAX] = {false, };
    q.push({{sx, sy}, 0});
    visited[sx][sy] = true;

    while(!q.empty()){
        int x = q.front().first.first;
        int y = q.front().first.second;
        int d = q.front().second;
        q.pop();

        if(Fuel - d < 0) return false;
        if(x == destX && y == destY){
            Fuel += d;
            tx = destX, ty = destY;
            return true;
        }
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if(map[nx][ny] == -1 || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({{nx, ny}, d+1});
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>N>>M>>Fuel;
    int ans = -1;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>map[i][j];
            if(map[i][j] == 1) map[i][j] = -1;
        }
    }
    cin>>tx>>ty;
    for(int i=1; i<=M; i++){
        cin>>customer[i].sx>>customer[i].sy>>customer[i].dx>>customer[i].dy;
        map[customer[i].sx][customer[i].sy] = i;
    }
    for(int i=1; i<=M; i++){
        int custId = find_closest_customer();
        if(custId == -1) break;
        bool movable = bfs(customer[custId].sx, customer[custId].sy, customer[custId].dx, customer[custId].dy, custId);
        if(!movable) break;
        if(i == M) ans = Fuel;
    }
    cout<<ans<<'\n';
    return 0;
}
