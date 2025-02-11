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

int a[N];
void sort_swap(int x, int y) {
    if (x == y)return;
    a[x] += a[y];
    a[y] = a[x] - a[y];
    a[x] -= a[y];
}

void sort_quick(int x,int y) {
    if (x >= y)return;
    int k = a[x];

    int l = x;
    for (int i = x + 1; i <= y; i++) {
        if (a[i] < k) {
            sort_swap(++l, i);
        }
    }
    sort_swap(x, l);
    sort_quick(x, l-1);
    sort_quick(l+1, y);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort_quick(0, n - 1);
    int k = a[0], ans = 1;
    a[n] = -1;
    for (int i = 1; i <= n; i++) {
        if (a[i] ^ k) {
            printf("%d %d\n", k, ans);
            k = a[i];
            ans = 1;
        }
        else {
            ans++;
        }
    }
    return 0;
}

