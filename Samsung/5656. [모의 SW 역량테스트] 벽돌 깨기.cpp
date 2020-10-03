#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int T, W, H, N, ans, total;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
vector<vector<int>> map(15, vector<int>(12, 0));

bool isWall(int x, int y) {
	return x < 0 || y < 0 || x >= H || y >= W;
}
void print() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	return;
}
void downMap() {
	while (1) {
		int cnt = 0;
		for (int j = 0; j < W; j++) {
			for (int i = H - 2; i >= 0; i--) {
				if (map[i][j] == 0) continue;
				if (map[i + 1][j] == 0) {
					map[i + 1][j] = map[i][j];
					map[i][j] = 0;
					cnt++;
				}
			}
		}
		if (cnt == 0) return;
	}
	return;
}
void solution(int n, int total) {
	if (total == 0) {
		ans = 0;
		return;
	}
	if (n == N) {
		ans = min(ans, total);
		return;
	}
	int i, j;
	vector<vector<int>> tmp = map;
	for (j = 0; j < W; j++) {
		if (map[H - 1][j] == 0) continue;
		for (i = 0; i < H; i++) {
			if (map[i][j] != 0)
				break;
		}
		if (map[i][j] == 1) {
			map[i][j] = 0;
			solution(n + 1, total - 1);
		}
		else {
			queue<pair<pair<int, int>, int>> q;
			q.push({ {i, j}, map[i][j] - 1 });
			map[i][j] = 0;
			int cnt = 1;
			while (!q.empty()) {
				int x = q.front().first.first;
				int y = q.front().first.second;
				int num = q.front().second;
				q.pop();
				for (int i = 0; i < 4; i++) {
					int nx = x, ny = y;
					for (int k = 0; k < num; k++) {
						nx += dx[i], ny += dy[i];
						if (isWall(nx, ny)) break;
						if (map[nx][ny] == 0) continue;
						if (map[nx][ny] > 1) {
							q.push({ {nx, ny}, map[nx][ny] - 1 });
						}
						map[nx][ny] = 0;
						cnt++;
					}
				}
			}
			downMap();
			solution(n + 1, total - cnt);
		}
		map = tmp;
	}
	return;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		total = 0;
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
				if (map[i][j] > 0)
					total++;
			}
		}
		ans = total;
		solution(0, total);
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}
