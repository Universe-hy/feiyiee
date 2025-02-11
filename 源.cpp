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
const int N = 10000010;

int a[N],idx;

void down(int x) {
    int t=x;
    if (2 * x <= idx && a[t] < a[2 * x])t = x * 2;
    if (x * 2 + 1 <= idx && a[t] < a[x * 2 + 1])t = x * 2 + 1;
    if (t ^ x)
    {
        swap(a[t], a[x]);
        down(t);
    }

}

void up(int x) {
    if (x / 2 && a[x / 2] < a[x]) {
        swap(a[x/2], a[x]);
        up(x / 2);
    }
}
void pop() {
    a[1] = a[idx];
    a[idx--] = 0;
    down(1);
}

void push(int x) {
    a[++idx] = x;
    up(idx);
}
int cmp1(int x, int y) {
    return x > y;
}
int main()
{
    int n,m,q,u,v,t;
    scanf("%d %d %d %d %d %d", &n, &m, &q, &u, &v, &t);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    idx = n;
    for (int i = n / 2; i; i--)
        down(i);

    int rise = 0;
    for (int i = 1; i <= m; i++) {
        int x = a[1]+rise;
        pop();
        long long int xa = (long long)x * u / v;
        int xb = x - xa;
        if (i % t == 0) {
            printf("%d ", x);
        }
        rise += q;
        push(xa - rise);
        push(xb - rise);
    }
    printf("\n");

    sort(a+1, a + n + m+1,cmp1);
    for (int i = t; i <= n + m; i += t) {
        printf("%d ", a[i]+rise);
    }
    
    return 0;
}

