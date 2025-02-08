#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>

using namespace std;
const int N = 10010;

typedef pair<int, int> PII;
vector<PII> a;
priority_queue<int,vector<int>,greater<int> > group;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({ x, y });
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++) {
        if (group.size() && group.top() < a[i].first)
            group.pop();
        group.push(a[i].second);
    }
    cout << group.size();
    return 0;
}