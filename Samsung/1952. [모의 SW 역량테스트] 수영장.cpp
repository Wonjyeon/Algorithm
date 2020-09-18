#include <iostream>
#include <algorithm>
using namespace std;

int T, day, month, t_months, year, ans;
int week[13];

void solution(int idx, int sum){
    if(idx == 13){
        ans = min(ans, sum);
        return;
    }
    if(idx <= 10){
        int t_sum = week[idx] + week[idx+1] + week[idx+2];
        if(t_sum >= t_months)
            solution(idx+3, sum+t_months);
    }
    solution(idx+1, sum+week[idx]);
    return;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    for(int tc=1; tc<=T; tc++){
        cin>>day>>month>>t_months>>year;
        ans = year;
        int num = 0;
        for(int i=1; i<=12; i++){
            cin>>num;
            week[i] = min(num*day, month);
        }
        solution(1, 0);
        cout<<'#'<<tc<<' '<<ans<<'\n';
    }
    return 0;
}