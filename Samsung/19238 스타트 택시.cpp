#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 21
#define INF 987654321
using namespace std;

struct Customer{
    int sx, sy, dx, dy;
};

int N, M, Fuel, tx, ty;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int map[MAX][MAX];
Customer customer[MAX*MAX];

bool cmp(int a, int b){
    Customer A = customer[a];
    Customer B = customer[b];

    if(A.sx == B.sx) return A.sy < B.sy;
    return A.sx < B.sx;
}

int find_customer(){
    bool visited[MAX][MAX] = {false, };
    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push({{tx, ty}, {0, Fuel}});
    visited[tx][ty] = true;
    vector<int> V;
    int minDist = INF;

    while(!Q.empty()){
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int dist = Q.front().second.first;
        int spare_fuel = Q.front().second.second;
        Q.pop();

        if(map[x][y] >= 1 && dist <= minDist){
            minDist = dist;
            V.push_back(map[x][y]);
            continue;
        }
        if(spare_fuel == 0) continue;

        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
            if(map[nx][ny] == -1 || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            Q.push({{nx, ny}, {dist+1, spare_fuel-1}});
        }
    }
    if(V.size() == 0) return -1;
    sort(V.begin(), V.end(), cmp);
    int num = V[0];
    map[customer[num].sx][customer[num].sy] = 0;
    Fuel -= minDist;
    return num;
}

bool bfs(int sx, int sy, int destX, int destY, int custId){
    bool visited[MAX][MAX] = {false, };
    queue<pair<pair<int, int>, pair<int, int>>> Q;
    Q.push({{sx, sy},{0, Fuel}});
    visited[sx][sy] = true;

    while(!Q.empty()){
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int dist = Q.front().second.first;
        int spare_fuel = Q.front().second.second;
        Q.pop();

        if(x == destX && y == destY){
            Fuel += dist;
            tx = x;
            ty = y;
            return true;
        }
        if(spare_fuel == 0) return false;
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
            if(map[nx][ny] == -1 || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            Q.push({{nx, ny}, {dist+1, spare_fuel-1}});
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>N>>M>>Fuel;
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
        int custId = find_customer();
        if(custId == -1){
            cout<<-1<<'\n';
            return 0;
        }
        bool movable = bfs(customer[custId].sx, customer[custId].sy, customer[custId].dx, customer[custId].dy, custId);
        if(!movable){
            cout<<-1<<'\n';
            return 0;
        }
    }
    cout<<Fuel<<'\n';
    return 0;
}