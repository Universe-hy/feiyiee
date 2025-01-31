#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
const int N = 6010;
int v[N],f[N],g[N],rs1[N],rs2[N];
queue<int> hod;

int main() {
	int n, a, b;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		f[a] = b; g[b]++;
	}

	for (int i = 1; i <=n; i++)
		if (!g[i]) hod.push(i);

	while (1) {
		a = hod.front();
		rs1[a] += v[a];
		if (f[a] == 0)break;
		hod.pop();
		rs1[f[a]] += rs2[a];
		rs2[f[a]] += max(rs1[a],rs2[a]);
		g[f[a]]--;
		if(g[f[a]]==0)
			hod.push(f[a]);
	}
	cout << max(rs1[hod.front()],rs2[hod.front()]);
	return 0;
}

