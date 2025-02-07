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
int a[N],idx;

void swap(int x,int y) {
    a[x] += a[y];
    a[y] = a[x] - a[y];
    a[x] -= a[y];
}

void up(int x) {
    if (a[x / 2] > a[x]) {
        swap(x / 2, x);
        if(x/2)up(x / 2);
    }
}
void down(int x) {
    if (x * 2 <= idx && (x * 2 + 1 > idx || a[x * 2] < a[x * 2 + 1]) && a[x * 2] < a[x]) {
        swap(x * 2, x);
        down(x * 2);
    }
    else if (x * 2+1 <= idx && a[x * 2] > a[x * 2 + 1] && a[x * 2 + 1] < a[x]) {
        swap(x * 2+1, x);
        down(x * 2+1);
    }
}

void pop() {
    a[1] = a[idx];
    a[idx] = 0;
    idx--;
    down(1);
}
int main()
{
    int k = 260332759;
    int n;
    cin >> n;
    idx = n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i >0; i--)  up(i);
    int b,ans=0;
    while (idx != 1) {
        b = a[1]; pop();
        b += a[1]; pop();
        ans += b;
        a[++idx] = b;
        up(idx);
    }
    cout << ans;
    return 0;
}
