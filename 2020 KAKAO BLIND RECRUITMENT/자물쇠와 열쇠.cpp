#include <iostream>
#include <vector>
using namespace std;

int N, M, lx, ly, lock_cnt, key_cnt;

vector<vector<int>> rotate(vector<vector<int>> key) {
	vector<vector<int>> rotKey;
	for (int i = 0; i < M; i++) {
		vector<int> col;
		for (int j = M - 1; j >= 0; j--) {
			col.push_back(key[j][i]);
		}
		rotKey.push_back(col);
	}
	return rotKey;
}

bool check(vector<vector<int>> key, vector<vector<int>> lock, int kx, int ky) {
	int x_diff = kx - lx;
	int y_diff = ky - ly;
	int tmpCnt = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			int nx = i - x_diff, ny = j - y_diff;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || key[i][j] == 0) continue;
			if (lock[nx][ny] == 1) return false;
			tmpCnt++;
		}
	}
	if (tmpCnt == lock_cnt) return true;
	return false;
}

bool findKey(vector<vector<int>> key, vector<vector<int>> lock) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (key[i][j] == 1) {
				if (check(key, lock, i, j)) return true;
			}
		}
	}
	return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	N = lock[0].size();
	M = key[0].size();
	lx = -1, ly = -1, lock_cnt = 0, key_cnt = 0;
	vector<vector<int>> key2 = rotate(key);
	vector<vector<int>> key3 = rotate(key2);
	vector<vector<int>> key4 = rotate(key3);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (lock[i][j] == 0) {
				lock_cnt++;
				if (lx == -1 && ly == -1) lx = i, ly = j;
			}
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (key[i][j] == 1) key_cnt++;
		}
	}
	if (lock_cnt > key_cnt) return false;
	if (findKey(key, lock)) return true;
	if (findKey(key2, lock)) return true;
	if (findKey(key3, lock)) return true;
	if (findKey(key4, lock)) return true;

	return false;
}

int main() {
	vector<vector<int>> key = { { 0,0,0 },{ 1,0,0 },{ 0,1,1 } };
	vector<vector<int>> lock = { { 1,1,1 },{ 1,1,0 },{ 1,0,1 } };
	cout << solution(key, lock) << '\n';
	return 0;
}