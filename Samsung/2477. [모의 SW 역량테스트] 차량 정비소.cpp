#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int T, A, B, N = 0, M = 0, K = 0, minTime = 0, maxTime = 0;
int aTime[10], bTime[10];
vector<int> cTime[1001];
vector<int> recept[10];
vector<int> repair[10];

void init(){
	for(int i=1; i<=N; i++){
		recept[i].clear();
	}
	for(int i=1; i<=M; i++){
		repair[i].clear();
	}
	for(int i=0; i<=maxTime; i++){
		cTime[i].clear();
	}
	return;
}

void solution(){
	int receptCnt = 0, time = minTime, lastA = 0;
	int receptArr[10] = {0, };
	int repairArr[10] = {0, };
	bool checkRepair[1001] = {false, };
	queue<int> receptReady, repairReady;
	while(1){
		if(time <= maxTime && cTime[time].size() > 0){
			for(int i=0; i<cTime[time].size(); i++){
				receptReady.push(cTime[time][i]);
			}
		}
		// 접수 창구
		if(receptCnt < K){
			for(int i=1; i<=N; i++){
				receptArr[i]--;
				if(receptArr[i] == 0){
					repairReady.push(recept[i].back());
					receptCnt++;
				}
				if(receptArr[i] <= 0 && !receptReady.empty()){
					receptArr[i] = aTime[i];
					recept[i].push_back(receptReady.front());
					receptReady.pop();
				}
			}
			if(receptCnt == K)
				lastA = recept[A].back();
		}

		// 정비 창구
		for(int i=1; i<=M; i++){
			repairArr[i]--;
			if(repairArr[i] <= 0 && !repairReady.empty()){
				repairArr[i] = bTime[i];
				repair[i].push_back(repairReady.front());
				checkRepair[repairReady.front()] = true;
				if(checkRepair[lastA]) return;
				repairReady.pop();
			}
		}
		time++;
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>T;
	for(int tc=1; tc<=T; tc++){
		cin>>N>>M>>K>>A>>B;
		int t, ans = 0;
		init();
		for(int i=1; i<=N; i++){
			cin>>aTime[i];
		}
		for(int i=1; i<=M; i++){
			cin>>bTime[i];
		}
		for(int i=1; i<=K; i++){
			cin>>t;
			if(i == 1) minTime = t;
			else if(i == K) maxTime = t;
			cTime[t].push_back(i);
		}
		solution();
		for(int i=0; i<recept[A].size(); i++){
			for(int j=0; j<repair[B].size(); j++){
				if(recept[A][i] == repair[B][j]){
					ans+=recept[A][i];
					break;
				}
			}
		}
		if(ans == 0) ans = -1;
		cout<<'#'<<tc<<' '<<ans<<'\n';
	}
	return 0;
}
