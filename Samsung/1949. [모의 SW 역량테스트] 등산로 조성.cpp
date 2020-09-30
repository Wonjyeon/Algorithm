#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int T, N, K, ans;
int map[8][8] = {0, };
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
bool visit[8][8] = {false, };

void dfs(int x, int y, int depth, bool flag){
    ans = max(ans, depth);
    visit[x][y] = true;
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx < 0 || nx >= N || ny < 0 || ny >= N || visit[nx][ny]) continue;
        if(map[x][y] > map[nx][ny]) dfs(nx, ny, depth+1, flag);
        else if(!flag && map[nx][ny] - K < map[x][y]){
        	int tmp = map[nx][ny];
            map[nx][ny] = map[x][y] - 1;
            dfs(nx, ny, depth+1, true);
            map[nx][ny] = tmp;
        }
    }
    visit[x][y] = false;
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        cin>>N>>K;
        int highVal = 0;
        ans = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin>>map[i][j];
                highVal = max(highVal, map[i][j]);
            }
        }
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(map[i][j] == highVal){
                    memset(visit, false, sizeof(visit));
                    dfs(i, j, 1, false);
                }
            }
        }
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}