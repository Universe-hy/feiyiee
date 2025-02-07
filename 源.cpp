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
long long int a[N], idx;

void swap(int x, int y) {
    long long int z = a[x];
    a[x] = a[y];
    a[y] = z;
}


void down(int x) {
    int t = x;
    if (x * 2 <= idx && a[x * 2] < a[t])t = x * 2;
    if (x * 2 + 1 <= idx && a[x * 2 + 1] < a[t])t = x * 2 + 1;
    if (t != x)
    {
        swap(t, x);
        down(t);
    }

    // if (x * 2 <= idx && (x * 2 + 1 > idx || a[x * 2] < a[x * 2 + 1]) && a[x * 2] < a[x]) {
    //     swap(x * 2, x);
    //     down(x * 2);
    // }
    // else if (x * 2+1 <= idx && a[x * 2] > a[x * 2 + 1] && a[x * 2 + 1] < a[x]) {
    //     swap(x * 2+1, x);
    //     down(x * 2+1);
    // }
}

void pop() {
    a[1] = a[idx];
    a[idx] = 0;
    idx--;
    down(1);
}
int main()
{
    int n;
    cin >> n;
    idx = n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = idx / 2; i; i--)
        down(i);
    long long int ans = 0;
    while (idx > 1) {
        long long int b = a[1]; pop();
        b += a[1];

        ans += b;

        a[1] = b;
        down(1);
    }
    cout << ans;
    return 0;
}