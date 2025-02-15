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

int idx1 = 0, st[N];
int notring = 1, be;
int maxcut=1e9;

void dfs(int a) {
    int id = h[a];
    d[a] = 0;
    printf("%d ", a);
    while (id) {
        if (d[e[id]])
        {
            if (notring || !(st[e[id]] > st[be] && e[id] > maxcut))
            {
                if (st[a] >= st[be] && st[e[id]] > st[be] && ne[id])
                    maxcut = e[ne[id]];
                dfs(e[id]);
            }
            else notring = 1;
        }
        id = ne[id];
    }
}

void fingring(int a) {
    st[a] = ++idx1;
    int id = h[a];
    if (idx1 - 1 && st[e[id]] == idx1 - 1)
        id = ne[id];
    while (id && notring) {
        if (!st[e[id]])
        {
            fingring(e[id]);
        }
        else {
            notring = 0;
            be= e[id];
        }
        id = ne[id];
        if (idx1 - 1 && st[e[id]] == idx1 - 1)
            id = ne[id];
    }
	if (notring)
    {
        st[a] = 0;
        idx1--;
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
    fingring(1);
    dfs(1);
}
