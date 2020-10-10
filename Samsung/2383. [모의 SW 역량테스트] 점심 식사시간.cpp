#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct people{
    int x, y;
};
struct stair{
    int x, y, l;
};
int T, N, ans;
vector<people> p;
vector<stair> s;
vector<int> stairA, stairB;

void init(){
    p.clear();
    s.clear();
    ans = (1 << 20);
    return;
}

int solution(vector<int> stair, int sid){
    vector<int> dist;
    int pid, d;
    for(int i=0; i<stair.size(); i++){
        pid = stair[i];
        d = abs(p[pid].x - s[sid].x) + abs(p[pid].y - s[sid].y);
        dist.push_back(d);
    }
    sort(dist.begin(), dist.end());
    while(dist.size() > 3){
        if(dist[0] + s[sid].l > dist[3])
            dist[3] = dist[0] + s[sid].l;
        dist.erase(dist.begin());
    }
    return dist[dist.size()-1] + s[sid].l + 1;
}

void dfs(int idx, int depth){
    if(depth==p.size()){
        int timeA = 0, timeB = 0;
        if(stairA.size() > 0)
            timeA = solution(stairA, 0);
        if(stairB.size() > 0)
            timeB = solution(stairB, 1);
        ans = min(ans, max(timeA, timeB));
        return;
    }
    for(int i=idx; i<p.size(); i++){
        stairA.push_back(i);
        dfs(i+1, depth+1);
        stairA.pop_back();
        stairB.push_back(i);
        dfs(i+1, depth+1);
        stairB.pop_back();
    }
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        cin>>N;
        init();
        int n;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin>>n;
                if(n == 1) p.push_back({i, j});               // 사람
                else if(n > 1)s.push_back({i, j, n});         // 계단
            }
        }
        dfs(0, 0);
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}