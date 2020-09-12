#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 1e5 + 1
using namespace std;

class Node{
public:
    int val;
    Node* left = NULL;
    Node* right = NULL;
    Node(int val){
        this->val = val;
    }
};

int depth;
vector<int> preOrder, postOrder;
vector<priority_queue<pair<int,int>>> yList;

bool cmp(vector<int>& a, vector<int>& b){
    if(a[1] == b[1]) return a[0] < b[0];
    return a[1]<b[1];
}

Node* makeBinaryTree(int maxX, int level){
    int x = -yList[level].top().first;
    int val = yList[level].top().second;
    yList[level].pop();

    Node* root = new Node(val);
    if(level == depth || yList[level+1].empty()) return root;

    // 왼쪽 노드
    int nextX = -yList[level+1].top().first;
    if(nextX < x)
        root->left = makeBinaryTree(x, level+1);
    if(yList[level+1].empty()) return root;

    // 오른쪽 노드
    nextX = -yList[level+1].top().first;
    if(nextX > x && nextX < maxX)
        root->right = makeBinaryTree(maxX, level+1);
    return root;
}

void setPreOrder(Node* root){
    if(root == NULL) return;
    preOrder.push_back(root->val);
    setPreOrder(root->left);
    setPreOrder(root->right);
}

void setPostOrder(Node* root){
    if(root == NULL) return;
    setPostOrder(root->left);
    setPostOrder(root->right);
    postOrder.push_back(root->val);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo){
    vector<vector<int>> answer;
    depth = -1;
    int beforeY = -1;

    for(int i=0; i<nodeinfo.size(); i++){
        nodeinfo[i].push_back(i+1);
    }
    sort(nodeinfo.begin(), nodeinfo.end(), cmp);

    for(int i=0; i<nodeinfo.size(); i++){
        int nowY = nodeinfo[i][1];
        if(nowY != beforeY){
            yList.push_back(priority_queue<pair<int, int>>());
            depth++;
            beforeY = nowY;
        }
        yList[depth].push_back({-nodeinfo[0], nodeinfo[2]});
    }
    
    return answer;
}