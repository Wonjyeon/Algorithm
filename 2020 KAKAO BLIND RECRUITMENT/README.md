# 2020 KAKAO BLIND RECRUITMENT

#### 1. [문자열 압축](https://programmers.co.kr/learn/courses/30/lessons/60057)
:pushpin: Tip
- 숫자의 길이도 포함시켜야 한다.
- 최대 압축할 수 있는 문자열의 길이는 전체 문자열의 1/2 이하이다.
<br>

#### 2. [괄호 변환](https://programmers.co.kr/learn/courses/30/lessons/60058)
:pushpin: Tip
- stack을 활용하여 올바른 괄호 문자열 check
- '('를 Left로, ')'를 Right로 계산해서 둘이 같아지면 균형잡힌 문자열. 반복문 break
<br>

#### 3. [자물쇠와 열쇠](https://programmers.co.kr/learn/courses/30/lessons/60059)
:pushpin: Tip
- 회전하는 함수를 따로 정의하여 4개의 key 벡터 구해놓기
- 자물쇠에서 0을 갖는 lx, ly를 하나 선정해서 key의 돌기 부분을 맞춰봄
- 자물쇠의 홈의 개수가 열쇠의 돌기 개수보다 크다면 무조건 false
<br>

#### 4. [가사 검색](https://programmers.co.kr/learn/courses/30/lessons/60060)
:pushpin: Tip
- 효율성 문제임을 고려하여 이분탐색을 이용함
- '?'가 접두사에 오는 경우를 대비하여 words의 문자열을 역순으로 저장하는 rwords를 생성
- words와 rwords를 길이 순서, 알파벳 순서로 정렬
- '?'인 부분을 전부 a로, 그리고 z로 바꾸면서 lower_bound, upper_bound 적용
<br>

#### 5. [기둥과 보 설치](https://programmers.co.kr/learn/courses/30/lessons/60061)
:pushpin: Tip
- x, y가 헷갈리는데 배열을 시계 방향으로 90도 회전시켰다고 생각하면 x, y를 그대로 두고 계산해도 됨.
- (x, y, type)으로 해당 좌표에 보, 기둥이 설치되었는지 유무를 파악
- 기둥 및 보 설치시 "양쪽"의 보, 기둥을 확인해야함
- 삭제의 경우, 해당 부분을 삭제하고 전체 기둥 및 보를 다시 삽입해보는 과정을 거쳐서 check함 (인풋이 크지 않았기에 가능)
<br>

#### 6. [외벽 점검](https://programmers.co.kr/learn/courses/30/lessons/60062)
:pushpin: Tip
- 원형으로 되어있는 리스트 -> weak.size()만큼 weak[0]번째 원소에 n을 더해서 push_back해준다.
- dist가 8이하이므로, next_permutation을 이용해서 모든 조합의 경우를 구했다.
<br>

#### 7. [블록 이동하기](https://programmers.co.kr/learn/courses/30/lessons/60063)
:pushpin: Tip
- 로봇이 2개의 좌표를 가지고 있으므로, (x, y, dir)로 visited를 체크함. (x, y)좌표에서 dir 방향으로 한 칸 더 차지한다는 뜻
- 이 때, (x, y, dir)도 visited고, 그 반대로 (x2, y2, (dir+2)%4)도 visited 체크!
- 회전은 가로, 세로를 구분지어서 가로인 경우 위, 아래 2칸에 모두 0인 경우만 두 좌표에서 회전이 가능함. 세로는 왼쪽, 오른쪽 2칸 체크
- 이동할 수 있으면 visited 체크하고, q에 삽입. 이 때, 거리 값도 같이 넣기.
