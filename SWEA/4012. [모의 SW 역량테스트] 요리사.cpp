#include <iostream>
#include <algorithm>
#define INF 1e9
using namespace std;

int T, N, ans, food[17][17];
bool visit[17];

void solution(int idx, int cnt){
    if(cnt == N/2){
        int sum1 = 0, sum2 = 0;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(i==j) continue;
                if(visit[i] && visit[j]) sum1 += food[i][j];
                else if(!visit[i] && !visit[j]) sum2 += food[i][j];
            }
        }
        ans = min(ans, abs(sum1 - sum2));
        return;
    }
    for(int i=idx; i<=N; i++){
        if(visit[i]) continue;
        visit[i] = true;
        solution(i+1, cnt+1);
        visit[i] = false;
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        ans = INF;
        cin>>N;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                cin>>food[i][j];
            }
        }
        solution(1, 0);
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
}