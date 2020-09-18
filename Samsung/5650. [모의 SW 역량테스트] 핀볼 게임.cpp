#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, ans, sx, sy;
int map[101][101];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int block[6][4] = {
	0,0,0,0,
	2,3,1,0,
	1,3,0,2,
	3,2,0,1,
	2,0,3,1,
	2,3,0,1
};
vector<pair<int, int>> worm_hole[11];
vector<pair<int, int>> zero;

bool isWall(int x, int y) {
	return x >= N || x < 0 || y >= N || y < 0;
}

int solution(int sx, int sy, int d) {
	int x = sx, y = sy;
	int sum = 0;
	while (1) {
		x += dx[d], y += dy[d];
		if (isWall(x, y)) {
			d = block[5][d];
			sum++;
			continue;
		}
		if (map[x][y] == -1 || (x == sx && y == sy))
			return sum;
		if (map[x][y] == 0)
			continue;
		if (map[x][y] >= 1 && map[x][y] <= 5) {
			d = block[map[x][y]][d];
			sum++;
			continue;
		}
		if(map[x][y] >= 6) {
			int nx1 = worm_hole[map[x][y]][0].first;
			int ny1 = worm_hole[map[x][y]][0].second;
			int nx2 = worm_hole[map[x][y]][1].first;
			int ny2 = worm_hole[map[x][y]][1].second;
			if (x == nx1 && y == ny1)
				x = nx2, y = ny2;
			else
				x = nx1, y = ny1;
		}
	}
}

void init() {
	for (int i = 6; i <= 10; i++) {
		worm_hole[i].clear();
	}
	zero.clear();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		ans = 0;
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 0) {
					zero.push_back({ i, j });
				}
				else if (map[i][j] >= 6) {
					worm_hole[map[i][j]].push_back({ i, j });
				}
			}
		}
		for (int i = 0; i < zero.size(); i++) {
			int x = zero[i].first, y = zero[i].second;
			for (int d = 0; d < 4; d++) {
				ans = max(ans, solution(x, y, d));
			}
		}
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}