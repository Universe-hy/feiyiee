#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
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
int a[N];

int main()
{
    int n;
    long long int dis = 0;
    cin >> n;
    int b;
    for (int i = 0; i < n; i++) {
        cin >> b;
        dis += b;
        a[b]++;
    }
    int r = a[0], l = n - a[0];
    long long int ans = dis;
    for (int i = 1; i < 40050; i++) {
        dis += -l + r;
        l -= a[i];
        r += a[i];
        ans = min(ans, dis);
    }
    cout << ans;
    return 0;
}
