#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

vector<string> split(string str, char delimeter){
    vector<string> result;
    string tmp = "";
    stringstream ss(str);
    
    while(getline(ss, tmp, delimeter)){
        result.push_back(tmp);
    }
    return result;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> userInfo;
    vector<vector<string>> split_record;
    for(int i=0; i<record.size(); i++){
        vector<string> splited = split(record[i], ' ');
        if(splited[0] != "Leave"){
            userInfo[splited[1]] = splited[2];
        }
        split_record.push_back(splited);
    }
    for(int i=0; i<split_record.size(); i++){
        vector<string> splited = split_record[i];
        if(splited[0] == "Enter")
            answer.push_back(userInfo[splited[1]]+"님이 들어왔습니다.");
        else if(splited[0] == "Leave")
            answer.push_back(userInfo[splited[1]]+"님이 나갔습니다.");
    }
    return answer;
}