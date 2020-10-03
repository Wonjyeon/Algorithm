#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int T, N, M, K, A, B, atime[10], btime[10], min_time = 0, max_time = 0;
vector<int> Reception[10];
vector<int> Repair[10];
vector<int> tk[1001];

void solution() {
	int cnt = 0;
	int time = min_time;
	int last_num = 0;
	int a[10] = { 0, };
	int b[10] = {0, };
	int check[1001] = { 0, };
	queue<int> wait1, wait2;
	while (1) {
		if (time <= max_time && tk[time].size() > 0) {
			for (int i = 0; i < tk[time].size(); i++) {
				wait1.push(tk[time][i]);
			}
		}
		// 접수 창구
		for (int i = 1; i <= N; i++) {
			a[i]--;
			if (a[i] == 0) {
				wait2.push(Reception[i].back());
			}
			if (a[i] <= 0 && wait1.size() > 0) {
				a[i] = atime[i];
				Reception[i].push_back(wait1.front());
				wait1.pop();
				cnt++;
			}
		}
		if (cnt == K) {
			last_num = Reception[A].back();
		}
		// 정비 창구
		for (int i = 1; i <= M; i++) {
				b[i]--;
			if (b[i] <= 0 && wait2.size() > 0) {
				b[i] = btime[i];
				Repair[i].push_back(wait2.front());
				check[wait2.front()] = 1;
				if (check[last_num] == 1) return;
				wait2.pop();
			}
		}
		time++;
	}
    return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> K >> A >> B;
		int t;
		for (int i = 0; i < 10; i++) {
			Reception[i].clear();
			Repair[i].clear();
		}
		for (int i = 0; i < 1001; i++) {
			tk[i].clear();
		}
		for (int i = 1; i <= N; i++)
			cin >> atime[i];
		for (int i = 1; i <= M; i++)
			cin >> btime[i];
		for (int i = 1; i <= K; i++) {
			cin >> t;
			if (i == 1) min_time = t;
			else if (i == K) max_time = t;
			tk[t].push_back(i);
		}
		solution();
		int ans = 0;
		for (int i = 0; i < Reception[A].size(); i++) {
			for (int j = 0; j < Repair[B].size(); j++) {
				if (Reception[A][i] == Repair[B][j]) {
					ans += Reception[A][i];
					break;
				}
			}
		}
		if (ans == 0) ans = -1;
		cout << '#' << tc << ' ' << ans << '\n';
	}
    return 0;
}