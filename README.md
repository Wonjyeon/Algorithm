# Algorithm

## vector 초기화

```cpp
// 이차원 벡터
vector<vector<int>> v(5, vector<int>(5, 0));

// 3차원 벡터
vector<vector<vector<int>>> v(5, vector<vector<int>>(5, vector<int>(2, 0)));
```

## vector 크기

```cpp
vector<vector<int>> v(3, vector<int>(2, 0));

// 행 개수 (3)
v.size();

// 열 개수 (2)
v[0].size();
```

## 문자열 delimeter로 자르기

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring> 
#include <algorithm>sing namespace std;

vector<int> answer;
bool check[100001];

bool cmp(string a, string b){
    return a.length() < b.length();
}

vector<int> split(string str, char delimeter){
    vector<int> result;
    string tmp = "";
    stringstream ss(str);

    while (getline(ss, tmp, delimeter)){
        result.push_back(stoi(tmp));
    }
    return result;
}

void solution(string s) {
    vector<string> str_sets;
    s = s.substr(1, s.length()-2);
    int idx = 1;
    int cnt = 1;
    for(idx; idx<s.length() - 1;){
        if(s[idx+cnt] == '}'){
            cout<<s.substr(idx, cnt)<<endl;
            str_sets.push_back(s.substr(idx, cnt));
            idx += cnt + 3;
            cnt = 1;
            continue;
        }
        cnt++;
    }

    sort(str_sets.begin(), str_sets.end(), cmp);
    memset(check, false, sizeof(check));

    for(int i=0; i<str_sets.size(); i++){
        vector<int> numVector = split(str_sets[i], ',');
        for(int i=0; i<numVector.size(); i++){
            if(!check[numVector[i]]){
                check[numVector[i]] = true;
                answer.push_back(numVector[i]);
                break;
            }
        }
    }
}

int main(){
    string s = "{{1,2,3},{2,1},{1,2,4,3},{2}}";
    solution(s);
}
```

## 배열 회전 (시계 방향)

```cpp
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
```

## 최대공약수

```cpp
ll gcd(ll a, ll b){
    while(b!=0){
        ll r = a%b;
        a=b;
        b=r;
    }
    return a;
}
```

## 블록 내리기 (부신 뒤 정리)

```cpp
void downBlock(){
    while(1){
        int cnt = 0;
        for(int i=10; i>=0; i--){
            for(int j=0; j<6; j++){
                if(map[i][j] == '.' || map[i+1][j] != '.') continue;
                map[i+1][j] = map[i][j];
                map[i][j] = '.';
                cnt++;
            }
        }
        if(cnt == 0) break;
    }
}
```

## 배열 x, y 바뀌었을 때

- x가 가로, y가 세로인데 바닥이 0인 경우
- x, y 그대로 사용. map[x][y]
- 반시계 방향으로 회전했을 때 같게 됨.


## 대문자를 소문자로 변환

```cpp
#include <cstring>

char alpha = 'B';
cout << tolower(alpha) <<< endl;      // 98 나옴. a가 97.
```

## 이중 탐색 (lower_bound, upper_bound)

```cpp
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(string a, string b)
{
    if (a.length() == b.length())
        return a < b;
    return a.length() < b.length();
}
vector<int> solution(vector<string> words, vector<string> queries)
{
    vector<int> answer;
    vector<string> rwords = words;
    int w_size = words.size();
    for (int i = 0; i < w_size; i++)
        reverse(rwords[i].begin(), rwords[i].end());

    sort(words.begin(), words.end(), cmp);
    sort(rwords.begin(), rwords.end(), cmp);
    int idx, len, low, high;
    for (string query : queries)
    {
        len = query.length();
        if (query[0] == '?')
        {
            reverse(query.begin(), query.end());
            idx = query.find_first_of('?');

            for (int i = idx; i < len; i++)
                query[i] = 'a';
            low = lower_bound(rwords.begin(), rwords.end(), query, cmp) - rwords.begin();

            for (int i = idx; i < len; i++)
                query[i] = 'z';
            high = upper_bound(rwords.begin(), rwords.end(), query, cmp) - rwords.begin();
        }
        else
        {
            idx = query.find_first_of('?');

            for (int i = idx; i < len; i++)
                query[i] = 'a';
            low = lower_bound(words.begin(), words.end(), query, cmp) - words.begin();

            for (int i = idx; i < len; i++)
                query[i] = 'z';
            high = upper_bound(words.begin(), words.end(), query, cmp) - words.begin();
        }
        answer.push_back(high - low);
    }
    return answer;
}
```

## 조합 - N개 중 M개 고르기 (중복x)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool visit[4];
vector<int> v;

void dfs(int idx, int depth){
    if(depth==3){
        for(int i=0; i<3; i++){
            cout<<v[i];
        }
        cout<<endl;
        return;
    }
    for(int i=idx; i<4; i++){
        if(visit[i]) continue;
        visit[i] = true;
        v.push_back(i+1);
        dfs(i+1, depth+1);
        visit[i] = false;
        v.pop_back();
    }
}

int main(){
    dfs(0, 0);
}

```

## 조합 - N개 중 M개 이상 고르기 (중복x)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool visit[4];
vector<int> v;

void dfs(int idx, int depth){
    if(depth>4) return;
    if(depth>=1){
        for(int i=0; i<v.size(); i++){
            cout<<v[i];
        }
        cout<<endl;
    }
    for(int i=idx; i<4; i++){
        if(visit[i]) continue;
        visit[i] = true;
        v.push_back(i+1);
        dfs(i+1, depth+1);
        visit[i] = false;
        v.pop_back();
    }
}

int main(){
    dfs(0, 0);
}
```

## 중복 조합

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v;

void dfs(int depth){
    if(depth==4){
        for(int i=0; i<4; i++){
            cout<<v[i];
        }
        cout<<endl;
        return;
    }
    for(int i=0; i<4; i++){
        v.push_back(i+1);
        dfs(depth+1);
        v.pop_back();
    }
}

int main(){
    dfs(0);
}
```

## lower_bound 구현

```cpp
#include <stdio.h>

int lower_bound(int[], int, int);

int main()
{
	int arr[10] = {1, 3, 4, 5, 7, 9, 12, 13, 15, 18}; // 데이터들이 크기순으로 졍렬되어 있는 상태이다.
	int target = 10; // 이 중 몇 번째 인덱스부터 10 이상이 되는지 찾아보도록 하자.
	int n = 10; // 배열의 크기
	printf("lower bound is arr[%d]\n", lower_bound(arr, target, n));
	return 0;
}

int lower_bound(int arr[], int target, int size)
{
	int mid, start, end;
	start = 0, end = size-1;

	while (end > start) // end가 start보다 같거나 작아지면, 그 값이 Lower Bound이므로 반복을 종료한다.
	{
		mid = (start + end) / 2; 
		if (arr[mid] >= target) // 중간값이 원하는 값보다 크거나 같을 경우, 끝값을 중간값으로 설정하여 다시 탐색한다.
			end = mid;
		else start = mid + 1; // 중간값이 원하는 값보다 작을 경우, 시작값을 중간값+1로 설정하여 다시 탐색한다.
	}
	return end;
}
```

## upper_bound 구현

```cpp
#include <stdio.h>

int upper_bound(int[], int, int);

int main()
{
	int arr[10] = {1, 3, 4, 5, 7, 9, 12, 13, 15, 18}; // 데이터들이 크기순으로 졍렬되어 있는 상태이다.
	int target = 3; // 이 중 몇 번째 인덱스부터 3 초과가 되는지 찾아보도록 하자.
	int n = 10; // 배열의 크기
	printf("Upper bound is arr[%d]\n", upper_bound(arr, target, n));
	return 0;
}

int upper_bound(int arr[], int target, int size)
{
	int mid, start, end;
	start = 0, end = size-1;

	while (end > start) // end가 start보다 같거나 작아지면, 그 값이 Upper Bound이므로 반복을 종료한다.
	{
		mid = (start + end) / 2; 
		if (arr[mid] > target) // 중간값이 원하는 값보다 클 경우, 끝값을 중간값으로 설정하여 다시 탐색한다.
			end = mid;
		else start = mid + 1; // 중간값이 원하는 값보다 작거나 같을 경우, 시작값을 중간값+1로 설정하여 다시 탐색한다.
	}
	return end;
}
```

## next_permutation

```cpp
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = -1;
    sort(dist.begin(), dist.end());
    for(int i=0; i<weak.size(); i++){
        int temp = weak[0] + n;
        for(int j=1; j<weak.size(); j++){
            weak[j-1] = weak[j];
        }
        weak[weak.size()-1] = temp;
        do{
            int w = 0, d = 0;
            for(d = 0; d<dist.size(); d++){
                int target = weak[w] + dist[d];
                while(target >= weak[w]){
                    w++;
                    if(w == weak.size()) break;
                }
                if(w==weak.size()) break;
            }
            if(w == weak.size() && (answer == -1 || answer > d+1)) answer = d+1;

        }while(next_permutation(dist.begin(), dist.end()));
    }
    return answer;
}
```

## 모든 조합의 경우를 vector에 저장

```cpp
void makeComb(int idx=0, string str = ""){
    for(int i=idx; i<N; i++){
        str+=to_string(i);
        combination.push_back(str);
        makeComb(i+1, str);
        str = str.substr(0, str.length()-1);
    }
}
```

## 문자열에 해당 글자가 있는지 확인

```cpp
combination[j].find(t) == string::npos    // 없는 경우
```

## vector에서 원소 삭제

```cpp
v.erase(v.begin() + j);    // v[j]를 삭제. v의 사이즈도 1 감소한다.
// 이럴 경우, for문에서 v.size()를 범위로 지정해야 함. (계속 바뀌니까)
```

## Binary Tree 만들기, preOrder, postOrder

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include<iostream>
#define MAX 1e5+1
using namespace std;

class Node {
public:
	int val;
	Node* left = NULL;
	Node* right = NULL;
	Node(int val) {
         this->val = val; 
    }
};
int depth = 0;
vector<int> preOrder, postOrder;
vector<priority_queue<pair<int, int>>> yList;

bool compare(vector<int>& a, vector<int>& b) {
    if(a[1] == b[1]) return a[0] < b[0];
    return a[1] > b[1];
}

Node* makeBinaryTree(int maxX, int level) {
	int x = -yList[level].top().first;
	int val = yList[level].top().second;
	yList[level].pop();
	Node* root = new Node(val);

	if (level == depth || yList[level + 1].empty())
		return root;

	// 왼쪽 노드
	int nextX = -yList[level + 1].top().first;
	if (nextX < x)
		root->left = makeBinaryTree(x, level + 1);
	if(yList[level + 1].empty())
		return root;

	// 오른쪽 노드
	nextX = -yList[level + 1].top().first;
	if (x < nextX && nextX < maxX)
		root->right = makeBinaryTree(maxX, level + 1);
	return root;
}

void setPreOrder(Node* root) {
	if (root == NULL) return;
	preOrder.push_back(root->val);
	setPreOrder(root->left);
	setPreOrder(root->right);
}
void setPostOrder(Node* root) {
	if (root == NULL) return;
	setPostOrder(root->left);
	setPostOrder(root->right);
	postOrder.push_back(root->val);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	int beforeY = -1;
	for (int i = 0; i < nodeinfo.size(); i++) {
		nodeinfo[i].push_back(i + 1);
	}

	sort(nodeinfo.begin(), nodeinfo.end(), compare);
	depth = -1;
	for (int i = 0; i < nodeinfo.size(); i++) {
		int nowY = nodeinfo[i][1];
		if (nowY != beforeY) {
			depth++;
			yList.push_back(priority_queue<pair<int,int>>());
			beforeY = nowY;
		}
		yList[depth].push({ -nodeinfo[i][0], nodeinfo[i][2]});
	}

	Node* root = makeBinaryTree(MAX, 0);
	setPreOrder(root);
	setPostOrder(root);
	answer.push_back(preOrder);
	answer.push_back(postOrder);
	return answer;
}
```

## 플로이드 워셜 알고리즘 - 모든 정점에서 모든 정점으로의 최단 거리

```cpp
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1<<20
using namespace std;
int d[210][210];
int N, S, A, B;
void Init(){
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++){
            if(i!=j) {
                d[i][j] = INF;
                d[j][i] = INF;
            }
        }
}
void Floyd(){
    for(int m=1; m<=N; m++)
        for(int s=1; s<=N; s++)
            for(int e=1; e<=N; e++)
                if(d[s][e] > d[s][m] + d[m][e])
                    d[s][e] = d[s][m] + d[m][e];
}
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    N=n, S=s, A=a, B=b;
    int answer = 0;
 ****   Init();
    for(int i=0; i<fares.size(); i++){
        d[fares[i][0]][fares[i][1]] = fares[i][2];
        d[fares[i][1]][fares[i][0]] = fares[i][2];
    }
    Floyd();
    answer = d[s][a] + d[s][b];
    for(int i=1; i<=n; i++){
        if(i==s) continue;
        int tmpDist = d[s][i] + d[i][a] + d[i][b];
        answer = min(answer, tmpDist);
    }
    return answer;
}
```

## string 문자열 끝에 문자 삽입

```cpp
string str = "abcd";
str.push_back('e');    // str = "abcde"
```

## string 문자열에서 문자 삭제

```cpp
string str = "abcde";
str.erase(3, 1);    // 3번째 index부터 1개 삭제. str = "abce"
```

## float 특정 소수점까지 반올림, string으로 변환

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main(){
    string answer = "";
    float ans = 0.2352;
    stringstream ss;
    ss << fixed<< setprecision(2)<<ans;
    answer = ss.str();
    cout<<answer<<'\n';
}
```
