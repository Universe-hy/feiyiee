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
priority_queue<int,vector<int>,greater<int> > a;


int main()
{
    int n;
    cin >> n;
    
    int k;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        a.push(k);
    }

    long long int ans = 0;
    while (a.size() > 1) {
        int b = a.top();
        a.pop();
        b += a.top(); 
        a.pop();
        a.push(b);
        ans += b;
    }
    cout << ans;
    return 0;
}