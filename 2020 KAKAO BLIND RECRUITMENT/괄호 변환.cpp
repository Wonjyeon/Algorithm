#include <string>
#include <vector>
#include <stack>

using namespace std;

bool check(string s) {
	stack<char> st;
	for (int i = 0; i<s.length(); i++) {
		if (s[i] == '(') st.push(s[i]);
		else {
			if (st.empty() || st.top() != '(') return false;
			st.pop();
		}
	}
	return true;
}

string solution(string p) {
	if (p.length() == 0) return p;
	string answer = "";
	string u = "";
	string v = "";
	int left = 0, right = 0;
	for (int i = 0; i<p.length(); i++) {
		if (p[i] == '(') left++;
		else right++;
		if (left == right) {
			u = p.substr(0, i + 1);
			v = p.substr(i + 1);
			break;
		}
	}
	if (check(u)) answer = u + solution(v);
	else {
		answer = "(" + solution(v) + ")";
		string tmp = "";
		for (int i = 1; i<u.length() - 1; i++) {
			if (u[i] == '(') tmp += ")";
			else tmp += "(";
		}
		answer += tmp;
	}
	return answer;
}