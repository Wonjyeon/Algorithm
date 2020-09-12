#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<double, int> a, pair<double, int> b){
    if(a.first == b.first) return a < b;
    return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<double, int>> failure;
    vector<double> challengers(N+2);
    vector<double> success(N+2);
    for(int i=0; i<stages.size(); i++){
        challengers[stages[i]]++;
    }
    success[N+1] = challengers[N+1];
    for(int i=N; i>=1; i--){
        success[i] = challengers[i] + success[i+1];
    }
    for(int i=1; i<=N; i++){
        if(success[i] == 0 || challengers[i] == 0) failure.push_back({0, i});
        else failure.push_back({challengers[i]/success[i], i});
    }
    sort(failure.begin(), failure.end(), cmp);
    for(int i=0; i<N; i++){
        answer.push_back(failure[i].second);
    }
    return answer;
}
