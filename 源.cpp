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
struct link
{
    int a, b;
	bool operator<(const link& t) const
	{
        return ((a == t.a) ? (b > t.b) : (a < t.a));
	}
}lin[N*2];


void add(int a, int b) {
    ne[idx] = h[a], h[a] = idx, e[idx++] = b;
    d[a]++;
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
        lin[i * 2].a = a;
		lin[i * 2].b = b;
        lin[i * 2+1].a = b;
        lin[i * 2+1].b = a;
    }
	sort(lin, lin + m*2);
	for (int i = 0; i < m*2; i++)
		add(lin[i].a, lin[i].b);
    dfs(1);
}

