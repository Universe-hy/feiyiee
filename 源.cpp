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

queue<int> a[3];
int b[N];

int maxa() {
    int t=0;
    for (int i = 0; i < 3; i++) 
        if (a[i].size()) {
            t = i;
            break;
        }
    for (int i = t+1; i < 3; i++) 
        if (a[i].size() && a[i].front() > a[t].front())
            t = i;
    int res = a[t].front();
    a[t].pop();
    return res;

}
int main()
{
    int n,m,q,u,v,t;
    scanf("%d %d %d %d %d %d", &n, &m, &q, &u, &v, &t);
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    sort(b, b + n + m, greater <int>() );
    for (int i = 0; i < n; i++) {
        a[0].push(b[i]);
    }
    int rise = 0;
    for (int i = 1; i <= m; i++) {
        int x = maxa()+rise;
        long long int xa = (long long)x * u / v;
        int xb = x - xa;
        if (i % t == 0) {
            printf("%d ", x);
        }
        rise += q;
        a[1].push(xa - rise);
        a[2].push(xb - rise);
    }
    printf("\n");
    for (int i = 0; i < n + m; i ++) {
        int k = maxa()+rise;
        if ((i + 1) % t == 0)
            printf("%d ", k);
    }
    return 0;
}

