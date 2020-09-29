#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int T, N, M, C, ans, x, y, subMax;
int honeyMap[10][10] = {0, };
int honeyArr[101] = {0, };
vector<int> subVec;

void init(){
    memset(honeyArr, 0, sizeof(honeyArr));
    ans = -1;
    return;
}
void calcMax(int i, int idx, int cnt, int sum, int powSum){
    if(sum > C) return;
    if(cnt >= 1){
        subMax = max(subMax, powSum);
    }
    for(int j = idx; j<y+M; j++){
        calcMax(i, j+1, cnt+1, sum+honeyMap[i][j], powSum+(honeyMap[i][j] * honeyMap[i][j]));
        calcMax(i, j+1, cnt, sum, powSum);
    }
    return;
}
void fillHoneyArr(){
    int sum = 0, powSum = 0, idx = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<=N-M; j++){
            idx = N*i+j;
            sum = 0, powSum = 0;
            for(int m=0; m<M; m++){
                sum+=honeyMap[i][j+m];
                powSum+=honeyMap[i][j+m] * honeyMap[i][j+m];
            }
            if(sum <= C) honeyArr[idx] = powSum;
            else{
                subMax = 0;
                x = i, y = j;
                subVec.clear();
                calcMax(i, j, 0, 0, 0);
                honeyArr[idx] = subMax;
            }
        }
    }
    return;
}
void solve(){
    int sumA = 0, sumB = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<=N-M; j++){
            sumA = honeyArr[(N*i)+j];
            for(int k = (N*i)+j+M; k<N*N; k++){
                sumB = max(sumB, honeyArr[k]);
            }
            ans = max(ans, sumA + sumB);
            sumB = 0;
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        cin>>N>>M>>C;
        init();
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin>>honeyMap[i][j];
            }
        }
        fillHoneyArr();
        solve();
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}