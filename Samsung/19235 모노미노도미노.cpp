#include <iostream>
using namespace std;

int N, score = 0;
pair<int, int> block_map[6][4][2];      // 0 : 초록색, 1 : 파란색

void init() {
   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
         block_map[i][j][0].first = 0;
         block_map[i][j][1].first = 0;
      }
   }
   return;
}

void down_block(int color) {
   while (1) {
      int cnt = 0;
      for (int i = 4; i >= 0; i--) {
         for (int j = 0; j < 4; j++) {
            int type = block_map[i][j][color].first;
            int id = block_map[i][j][color].second;
            if (type == 0) continue;
            // 나랑 내 오른쪽 블록의 아래 모두 비어있어야 가능.
            if (type == 2) {
               if (block_map[i + 1][j][color].first == 0 && block_map[i + 1][j + 1][color].first == 0) {
                  block_map[i + 1][j][color] = block_map[i][j][color];
                  block_map[i + 1][j + 1][color] = block_map[i][j + 1][color];
                  block_map[i][j][color].first = 0;
                  block_map[i][j + 1][color].first = 0;
                  cnt++;
               }
               j++;
            }
            // 내 아래만 비어있으면 가능.
            else {
               if (block_map[i + 1][j][color].first == 0) {
                  block_map[i + 1][j][color] = block_map[i][j][color];
                  block_map[i][j][color].first = 0;
                  cnt++;
               }
            }
         }
      }
      if (cnt == 0) return;
   }
}

void check_block(int color) {
   // 삭제 가능한 행 찾기
   while (1) {
      bool flag = false;
      for (int i = 0; i < 6; i++) {
         int cnt = 0;
         for (int j = 0; j < 4; j++) {
            if (block_map[i][j][color].first == 0) break;
            cnt++;
         }
         if (cnt == 4) {
            score++;
            flag = true;
            for (int j = 0; j < 4; j++) {
               block_map[i][j][color].first = 0;
            }
         }
      }
      if (flag) {
         down_block(color);
      }
      else
         break;
   }
   // 0, 1번째 행 확인
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {
         if (block_map[i][j][color].first != 0) {
            if (i == 0) {
               for (int c = 0; c < 4; c++) {
                  block_map[4][c][color].first = 0;
                  block_map[5][c][color].first = 0;
               }
            }
            else {
               for (int c = 0; c < 4; c++) {
                  block_map[5][c][color].first = 0;
               }
            }
            down_block(color);
            return;
         }
      }
   }
   return;
}

int main() {
   ios::sync_with_stdio(0); cin.tie(0);
   cin >> N;
   init();
   int t, x, y;
   for (int i = 1; i <= N; i++) {
      cin >> t >> x >> y;
      for (int j = 0; j < 2; j++) {
         int r;
         if (j == 1) {
            y = x;
            if (t == 2) t = 3;
            else if (t == 3) t = 2;
         }
         if (t == 1) {
            for (r = 0; r < 6; r++) {
               if (block_map[r][y][j].first != 0) break;
            }
            r--;
            block_map[r][y][j].first = t;
            block_map[r][y][j].second = i;
         }
         else if (t == 2) {
            for (r = 0; r < 6; r++) {
               if (block_map[r][y][j].first != 0 || block_map[r][y + 1][j].first != 0) break;
            }
            r--;
            block_map[r][y][j].first = t;
            block_map[r][y][j].second = i;
            block_map[r][y+1][j].first = t;
            block_map[r][y+1][j].second = i;
         }
         else if (t == 3) {
            for (r = 0; r < 6; r++) {
               if (block_map[r][y][j].first != 0) break;
            }
            r--;
            block_map[r][y][j].first = t;
            block_map[r][y][j].second = i;
            block_map[r-1][y][j].first = t;
            block_map[r-1][y][j].second = i;
         }
         //printBlocks();
         check_block(j);
      }
   }
   int g_cnt = 0, b_cnt = 0;
   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
         if (block_map[i][j][0].first != 0) g_cnt++;
         if (block_map[i][j][1].first != 0) b_cnt++;
      }
   }
   cout << score << '\n' << g_cnt + b_cnt << '\n';
   return 0;
}