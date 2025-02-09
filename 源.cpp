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
const int N = 100010;

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

    int r=-1000000010,ans=0;
    for (int i = 0; i < n; i++) 
        if (r <a[i].first ) {
            ans++;
            r = a[i].second;
        }else if (a[i].second < r) 
            r = a[i].second;
    cout << ans;
    return 0;
}

