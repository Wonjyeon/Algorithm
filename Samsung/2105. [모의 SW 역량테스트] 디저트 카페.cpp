#include <iostream>
using namespace std;

int T, N, sx, sy, ans;
int dx[4] = {1,1,-1,-1};
int dy[4] = {1,-1,-1,1};
int map[21][21];
bool dessert[101];

void solution(int x, int y, int dir, int cnt){
    int nx = x + dx[dir], ny = y + dy[dir];
    if(dir == 3 && nx == sx && ny == sy){
        if(ans < cnt) ans = cnt;
        return;
    }
    if(nx >= 0 && ny >= 0 && nx < N && ny < N && !dessert[map[nx][ny]]){
        dessert[map[nx][ny]] = true;
        solution(nx, ny, dir, cnt+1);
        if(dir < 3)
            solution(nx, ny, dir+1, cnt+1);
        dessert[map[nx][ny]] = false;
    }
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        cin>>N;
        ans = -1;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin>>map[i][j];
            }
        }
        for(int i=0; i<=N-3; i++){
            for(int j=1; j<=N-2; j++){
                sx = i, sy = j;
                dessert[map[i][j]] = true;
                solution(i, j, 0, 1);
                dessert[map[i][j]] = false;
            }
        }
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}