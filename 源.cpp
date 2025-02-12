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
int h[N], ne[N], e[N], idx=1,d[N];

void add(int a, int b) {
    ne[idx] = h[a], h[a] = idx, e[idx++] = b;
    ne[idx] = h[b], h[b] = idx, e[idx++] = a;
    d[a]++; d[b]++;
}


void dfs(int a) {
    int id = h[a];
    d[a] = 0;
    printf("%d ", a);
    while (id) {
        if (d[e[id]])
            dfs(e[id]);
        id = ne[id];
    }
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
    }

    dfs(1);
}

