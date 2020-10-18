#include <iostream>
#include <queue>
using namespace std;

int N, M, T;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int map[51][51] = { 0, };

void rotateMap(int x, int d, int k) {
   int mid = M / 2;
   if (k > mid) {
      d = (d + 1) % 2;
      k = M - k;
   }
   for (int i = 1; i <= N; i++) {
      if (i % x != 0) continue;
      if (d == 0) {
         for (int t = 1; t <= k; t++) {
            int tmp = map[i][M];
            for (int j = M - 1; j >= 1; j--) {
               map[i][j + 1] = map[i][j];
            }
            map[i][1] = tmp;
         }
      }
      else {
         for (int t = 1; t <= k; t++) {
            int tmp = map[i][1];
            for (int j = 2; j <= M; j++) {
               map[i][j - 1] = map[i][j];
            }
            map[i][M] = tmp;
         }
      }
   }
}

void checkMap() {
   bool visited[51][51] = { false, };
   bool isErased = false;
   int targetNum = 0;
   for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
         if (map[i][j] == 0) continue;
         bool flag = false;
         targetNum = map[i][j];
         map[i][j] = 0;
         queue<pair<int, int>> q;
         q.push({ i, j });
         if (i == 3 && j == 4) {
            int deb = 1;
         }
         while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            for (int d = 0; d < 4; d++) {
               int nx = x + dx[d];
               int ny = y + dy[d];
               if (ny > M) ny = 1;
               else if (ny < 1) ny = M;
               if (nx < 1 || nx > N || map[nx][ny] != targetNum) continue;
               flag = true;
               q.push({ nx, ny });
               map[nx][ny] = 0;
            }
         }
         if (!flag) {
            map[i][j] = targetNum;
         }
         else {
            isErased = true;
         }
      }
   }
   if (!isErased) {
      double sum = 0, cnt = 0, avg = 0;
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= M; j++) {
            if (map[i][j] != 0) {
               sum += map[i][j];
               cnt++;
            }
         }
      }
      avg = (sum / cnt);
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= M; j++) {
            if (map[i][j] != 0) {
               if (map[i][j] > avg)
                  map[i][j]--;
               else if (map[i][j] < avg)
                  map[i][j]++;
            }
         }
      }
   }
}

int main() {
   cin >> N >> M >> T;
   int x, d, k, ans = 0;
   for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
         cin >> map[i][j];
      }
   }
   for (int t = 1; t <= T; t++) {
      cin >> x >> d >> k;
      rotateMap(x, d, k);
      checkMap();
   }
   for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
         ans += map[i][j];
      }
   }
   cout << ans << '\n';
}