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
const int N = 310;
int v[N][N], f[N][N], rs[N][N];
int r, c;
int dfs(int a, int b) {
	if (rs[a][b])
		return rs[a][b];

	if (a - 1 >= 0 && v[a - 1][b] < v[a][b])
		rs[a][b] = max(rs[a][b], dfs(a - 1, b));
	if (b - 1 >= 0 && v[a][b - 1] < v[a][b])
		rs[a][b] = max(rs[a][b], dfs(a, b - 1));
	if (a + 1 < r && v[a + 1][b] < v[a][b])
		rs[a][b] = max(rs[a][b], dfs(a + 1, b));
	if (b + 1 < c && v[a][b + 1] < v[a][b])
		rs[a][b] = max(rs[a][b], dfs(a, b + 1));
	rs[a][b]++;
	return rs[a][b];
}

int main() {
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++)
		for (int q = 0; q < c; q++)
		{
			scanf("%d", &v[i][q]);
		}
	int ans = 0;
	for (int i = 0; i < r; i++)
		for (int q = 0; q < c; q++)
			ans = max(ans, dfs(i, q));
	cout << ans;

	return 0;
}
