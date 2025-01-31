#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
const int N = 310;
int v[N][N], f[N][N], rs[N][N];
int r, c;

struct ni{
	int w, s;
}niu[50005];

bool cmp(ni a,ni b) {
	return a.s + a.w < b.s + b.w;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++)
		scanf("%d %d", &niu[i].w, &niu[i].s);
	sort(niu, niu+n, cmp);
	int tw = 0,ans= -1000000500;
	for (int i = 0; i < n; i++) {
		ans =max(ans, tw - niu[i].s);
		tw += niu[i].w;
	}
	cout << ans;
	return 0;
}
