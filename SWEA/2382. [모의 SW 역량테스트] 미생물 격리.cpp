#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct grp{
    int id, n, d;
};
int T, N, M, K;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
bool visit[1001];
vector<grp> map[101][101];

bool isWall(int x, int y){
    return x == 0 || y == 0 || x == N-1 || y == N-1;
}

void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            map[i][j].clear();
        }
    }
    return;
}

void solution(){
    while(M--){
        memset(visit, false, sizeof(visit));
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(map[i][j].size() == 0) continue;
                grp g = map[i][j][0];
                if(visit[g.id]) continue;
                visit[g.id] = true;
                map[i][j].erase(map[i][j].begin());
                int nx = i + dx[g.d];
                int ny = j + dy[g.d];
                if(isWall(nx, ny)){
                    g.n /= 2;
                    g.d = (g.d+2)%4;
                    if(g.n == 0) continue;
                }
                map[nx][ny].push_back(g);
            }
        }
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(map[i][j].size() <= 1) continue;
                int maxN = 0, maxD = 0, maxID = 0;
                int sum = 0;
                for(int k=0; k<map[i][j].size(); k++){
                    grp g = map[i][j][k];
                    sum+=g.n;
                    if(maxN < g.n){
                        maxN = g.n;
                        maxD = g.d;
                        maxID = g.id;
                    }
                }
                map[i][j].clear();
                map[i][j].push_back({maxID, sum, maxD});
            }
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        init();
        int ans = 0;
        cin>>N>>M>>K;
        for(int i=0; i<K; i++){
            int x, y;
            grp g;
            g.id = i;
            cin>>x>>y>>g.n>>g.d;
            if(g.d == 1) g.d = 0;
            else if(g.d == 4) g.d = 1;
            map[x][y].push_back(g);
        }
        solution();
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(map[i][j].size() > 0){
                    ans+=map[i][j][0].n;
                }
            }
        }
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}
