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


int main()
{
    int s,t;
    cin >> s>>t;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({ x, y });
    }
    sort(a.begin(), a.end());

    int l = s;
    int r = -1000000000;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (a[i].first <= l) {
            if (r < a[i].second)
            {
                r = a[i].second;
                if(t<=r)
                {
                    cout << ans;
                    return 0;
                }
            }
        }
        else if ( a[i].first<=r ) {
            l = r;
            ans++;
            i--;
        }
        else {
            cout << -1;
            return 0;
        }
    }
    cout <<  -1;   
    return 0;
}