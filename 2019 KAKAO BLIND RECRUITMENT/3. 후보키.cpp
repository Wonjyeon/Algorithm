#include <iostream>
#include <vector>
#include <map>  
#include <string>
#include <algorithm>
using namespace std;

int N;
vector<string> combination;

bool cmp(string& a, string& b){
    if(a.length() == b.length()) return a < b;
    return a.length() < b.length();
}

void makeComb(int idx=0, string str = ""){
    for(int i=idx; i<N; i++){
        str+=to_string(i);
        combination.push_back(str);
        makeComb(i+1, str);
        str = str.substr(0, str.length()-1);
    }
}

bool checkSuper(vector<vector<string>>& relation, string key){
    map<string, int> m;
    for(int i=0; i<relation.size(); i++){
        string str = "";
        for(int k=0; k<key.length(); k++){
            int idx = key[k] - '0';
            str+=relation[i][idx];
        }
        if(m[str]) return false;
        m[str]++;
    }
    return true;
}

int solution(vector<vector<string>> relation){
    int answer = 0;
    N = relation[0].size();
    makeComb();
    sort(combination.begin(), combination.end(), cmp);

    for(int i=0; i<combination.size(); i++){
        if(checkSuper(relation, combination[i])){
            string str = combination[i];
            for(int j=combination.size()-1; j>=i; j--){
                bool check=true;
                for(auto t:str){
                    if(combination[j].find(t) == string::npos){
                        check = false;
                        break;
                    }
                }
                if(check) combination.erase(combination.begin() + j);
            }
            i--;
            answer++;
        }
    }
    return answer;
}
