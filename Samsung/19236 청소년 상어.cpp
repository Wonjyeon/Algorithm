#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fish{
    int x, y, dir, dead;
};
vector<Fish> fishes(18);
vector<vector<int>> map(4, vector<int>(4, 0));
int ans = 0;
int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,-1,-1,-1,0,1,1,1};

void moving(int sum){
    if(ans < sum) ans = sum;
    // 물고기 이동
    for(int i=1; i<=16; i++){
        if(fishes[i].dead == 1) continue;
        int x = fishes[i].x;
        int y = fishes[i].y;
        int dir = fishes[i].dir;

        for(int d=0; d<8; d++){
            int ndir = (dir+d) % 8;
            int nx = x + dx[ndir];
            int ny = y + dy[ndir];
            // 이동 불가 (범위 벗어나거나 상어가 위치함)
            if(nx<0 || ny<0 || nx>=4 || ny>=4 || map[nx][ny] == 17)
                continue;
            // 이동 가능
            fishes[i].dir = ndir;
            // 빈 공간
            if(map[nx][ny] == 0){
                map[nx][ny] = i;
                map[x][y] = 0;
                fishes[i].x = nx;
                fishes[i].y = ny;
            }
            // 다른 물고기 -> 자리 바꾸기 (방향은 바뀌지 않음)
            else{
                swap(map[x][y], map[nx][ny]);
                swap(fishes[i].x, fishes[map[x][y]].x);
                swap(fishes[i].y, fishes[map[x][y]].y);
            }
            break;
        }
    }
    // 상어 이동
    int sx = fishes[17].x, sy = fishes[17].y, sdir = fishes[17].dir;
    int nsx = sx, nsy = sy;
    while(1){
        nsx += dx[sdir];
        nsy += dy[sdir];
        if(nsx<0 || nsy<0 || nsx>=4 || nsy>=4) break;
        if(map[nsx][nsy] == 0) continue;
        vector<Fish> tempFish = fishes;
        vector<vector<int>> tempMap = map;
        int dieFishId = map[nsx][nsy];
        fishes[17] = fishes[dieFishId];
        fishes[dieFishId].dead = 1;
        map[nsx][nsy] = 17;
        map[sx][sy] = 0;
        moving(sum + dieFishId);
        fishes = tempFish;
        map = tempMap;
    }
    return;
}

int main(){
    int fid, dir;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cin>>fid>>dir;
            fishes[fid] = Fish{i, j, dir-1, 0};
            map[i][j] = fid;
        }
    }
    ans += map[0][0];
    fishes[17] = fishes[map[0][0]];
    fishes[map[0][0]].dead = 1;
    map[0][0] = 17;
    moving(ans);
    cout<<ans<<'\n';
    return 0;
}