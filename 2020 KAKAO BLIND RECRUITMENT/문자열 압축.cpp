#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(string s) {
	int answer = s.length();
	for (int len = 1; len <= s.length() / 2; len++) {
		int idx = 0;
		int tmp_length = 0;            // 숫자 길이 + 문자 길이
		while (idx < s.length()) {
			if (idx > s.length() - len) {
				tmp_length += s.length() - idx;
				break;
			}
			int cnt = 1;
			string cmp_str1 = s.substr(idx, len);
			while (1) {
				string cmp_str2 = s.substr(idx + cnt*len, len);
				if (cmp_str1 != cmp_str2) break;
				cnt++;
			}
			idx += cnt*len;
			tmp_length += len;
			if (cnt > 1) {
				if (cnt <10) tmp_length += 1;
				else if (cnt<100) tmp_length += 2;
				else tmp_length += 3;
			}
		}
		answer = min(answer, tmp_length);
	}
	return answer;
}