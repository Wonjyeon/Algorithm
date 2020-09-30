#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int T, N, minVal, maxVal;
int numArr[13] = {0,};
int opCnt[4] = {0,};
vector<int> opVec;

void init(){
    memset(opCnt, 0, sizeof(opCnt));
    minVal = 100000001;
    maxVal = -100000001;
}
void solve(int depth, int sum){
    if(depth == N-1){
        minVal = min(minVal, sum);
        maxVal = max(maxVal, sum);
        return;
    }
    for(int i=0; i<4; i++){
        if(opCnt[i] == 0) continue;
        opCnt[i]--;
        if(i == 0) solve(depth+1, sum+numArr[depth+1]);
        else if(i == 1) solve(depth+1, sum-numArr[depth+1]);
        else if(i == 2) solve(depth+1, sum*numArr[depth+1]);
        else if(i == 3) solve(depth+1, sum/numArr[depth+1]);
        opCnt[i]++;
    }
    return;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        init();
        cin>>N;
        for(int i=0; i<4; i++){
            cin>>opCnt[i];
        }
        for(int i=0; i<N; i++){
            cin>>numArr[i];
        }
        solve(0, numArr[0]);
        cout<<'#'<<tc<<' '<<maxVal - minVal<<'\n';
    }
    return 0;
}