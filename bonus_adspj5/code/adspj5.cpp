//
//  main.cpp
//  adspj5
//
//  Created by 张倬豪 on 2017/5/13.
//  Copyright © 2017年 Icarus. All rights reserved.
//

#include<iostream>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

struct Node{
    char c;
    int f;
} huffmanTreeNode[100];

struct Code{
    char ch;
    string hCode;
} huffmanTreeCode[100];

int cmp(Code a, Code b) {
    return a.hCode.size() < b.hCode.size();
}

int getWPL(int n) {
    int i, x = 0, y = 0, ans = 0;
    priority_queue< int, vector<int>, greater<int> > queue;
    for(i = 1; i <= n; i++){
        queue.push(huffmanTreeNode[i].f);
    }
    while(!queue.empty()) {
        x = queue.top();
        queue.pop();
        if(!queue.empty()) {
            y = queue.top();
            queue.pop();
            queue.push(x + y);
        }
        ans += x + y;
    }
    return ans - x - y;
}

int findPos(char a, int n) {
    int i;
    for(i = 1; i <= n; i++) if(huffmanTreeNode[i].c == a) return i;
    return 0;
}

int wplJudge(int n, int ans) {
    int i, resWPL = 0;
    for(i = 1; i <= n; i++){
        resWPL += huffmanTreeNode[findPos(huffmanTreeCode[i].ch, n)].f * huffmanTreeCode[i].hCode.size();
    }
    return resWPL == ans;
}

int prefixJudge(int n) {
    int i, j;
    sort(huffmanTreeCode + 1, huffmanTreeCode + 1 + n, cmp);
    for(i = 1; i <= n; i++){
        string t = huffmanTreeCode[i].hCode;
        for(j = i + 1; j <= n; j++) if(huffmanTreeCode[j].hCode.substr(0 ,t.size()) == t) return 0;
    }
    return 1;
}

int main() {
    int n, m, rightWPL, i;
    cin >> n;
    for(i = 1; i <= n; i++){
        cin >> huffmanTreeNode[i].c >> huffmanTreeNode[i].f;
    }
    cin >> m;
    
    rightWPL = getWPL(n);
    
    while(m--) {
        for(i = 1; i <= n; i++){
            cin >> huffmanTreeCode[i].ch >> huffmanTreeCode[i].hCode;
        }
        if(!wplJudge(n, rightWPL) || !prefixJudge(n)) cout << "No" << endl;
        else cout << "Yes" << endl;
    }
    return 0;
}
