#include <iostream>
#include <vector>
using namespace std;

struct Shark {
	int x = 0, y = 0, nDir = 0, dead = 0;
	int pDir[5][5] = { 0, };
};
int N, M, K;
Shark sharks[401];
pair<int, int> map[20][20];
int dx[] = { 0,-1,1,0,0 };
int dy[] = { 0,0,0,-1,1 };

int moving() {
	int time = 0, rest_shark = M;
	while (rest_shark > 1 && time <= 1000) {

		if (time == 3)
			int debug = 1;
		// 상어 이동
		for (int m = 1; m <= M; m++) {
			if (sharks[m].dead == 1)
				continue;
			int x = sharks[m].x;
			int y = sharks[m].y;
			int nDir = sharks[m].nDir;
			for (int i = 1; i <= 4; i++) {
				int next_dir = sharks[m].pDir[nDir][i];
				int nx = x + dx[next_dir];
				int ny = y + dy[next_dir];
				if (nx < 0 || nx >= N || ny < 0 || ny >= N || !map[nx][ny].second == 0)
					continue;
				// 빈 공간을 찾았으면
				sharks[m].x = nx;
				sharks[m].y = ny;
				sharks[m].nDir = next_dir;
				break;
			}
			// 빈 공간이 없었으면 나랑 같은 애 찾기.
			if (sharks[m].x == x && sharks[m].y == y) {
				for (int i = 1; i <= 4; i++) {
					int next_dir = sharks[m].pDir[nDir][i];
					int nx = x + dx[next_dir];
					int ny = y + dy[next_dir];
					if (nx < 0 || nx >= N || ny < 0 || ny >= N || map[nx][ny].first != m)
						continue;
					// 나랑 같은 애 찾았으면
					sharks[m].x = nx;
					sharks[m].y = ny;
					sharks[m].nDir = next_dir;
					break;
				}
			}
		}
		int fx = sharks[1].x;
		int fy = sharks[1].y;
		map[fx][fy] = { 1, K + 1 };			// 전체 한꺼번에 1 빼주기 위함.
		for (int i = 2; i <= M; i++) {
			if (sharks[i].dead == 1)
				continue;
			int nextX = sharks[i].x;
			int nextY = sharks[i].y;
			if (map[nextX][nextY].first != 0 && map[nextX][nextY].first != i) {
				sharks[i].dead = 1;
				rest_shark--;
			}
			else {
				map[nextX][nextY] = { i, K + 1 };
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j].second > 0) {
					map[i][j].second--;
					if (map[i][j].second == 0)
						map[i][j].first = 0;
				}
			}
		}
		time++;
	}
	if (time > 1000)
		time = -1;
	return time;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	int s;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> s;
			if (s == 0)
				map[i][j] = { 0, 0 };
			else {
				map[i][j] = { s, K };
				sharks[s].x = i;
				sharks[s].y = j;
			}
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> sharks[i].nDir;
	}
	for (int m = 1; m <= M; m++) {
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				cin >> sharks[m].pDir[i][j];
			}
		}
	}
	cout << moving() << endl;
	return 0;
}