#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int map[110][110][2];

int insert(int x, int y, int t)
{
    if(t == 0){
        if(y == 0 || (y-1 >= 0 && map[x][y-1][0] == 1) || (x-1 >= 0 && map[x-1][y][1] == 1) || map[x][y][1] == 1) return true;
    }
    else{
        if((y-1 >= 0 && map[x][y-1][0] == 1) || (y-1 >= 0 && x+1 <= N && map[x+1][y-1][0]==1)) return true;
        if((x-1 >= 0 && map[x-1][y][1] == 1) && (x+1 <= N && map[x+1][y][1] == 1)) return true;
    }
    return false;
}

bool erase(){
    for(int i=0; i<=N; i++){
        for(int j=0; j<=N; j++){
            for(int k=0; k<2; k++){
                if(map[i][j][k]==1){
                    map[i][j][k] = 0;
                    if(!insert(i, j, k)){
                        map[i][j][k] = 1;
                        return false;
                    }
                    map[i][j][k] = 1;
                }
            }
        }
    }
    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame){
    vector<vector<int>> answer;
    N = n;

    for(int i=0; i<build_frame.size(); i++){
        int x = build_frame[i][0];
        int y = build_frame[i][1];
        int t = build_frame[i][2];
        int c = build_frame[i][3];

        if(c == 0){             // 삭제
            map[x][y][t] = 0;
            if(!erase()) map[x][y][t] = 1;
        }
        else{                   // 설치
            if(insert(x, y, t)) map[x][y][t] = 1;
        }
    }
    for(int i=0; i<=N; i++){
        for(int j=0; j<=N; j++){
            for(int k=0; k<2; k++){
                if(map[i][j][k]){
                    vector<int> col;
                    col.push_back(i);
                    col.push_back(j);
                    col.push_back(k);
                    answer.push_back(col);
                }
            }
        }
    }
    return answer;
}

int main(){
    int n = 5;
    vector<vector<int>> build_frame = {{0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1}};
    vector<vector<int>> ans = solution(n, build_frame);
    for(int i=0; i<ans.size(); i++){
        for(int j=0; j<ans[0].size(); j++){
            cout<<ans[i][j]<<',';
        }
        cout<<'\n';
    }
    return 0;
}