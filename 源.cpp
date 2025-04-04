//#include<stdio.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
const int N = 200010;
int n, m;
ll a[N], b[N];
int ai[N], idx = 1;
void cut() {
	int nidx = 1;
	for (int i = 1; i < idx; i++) {
		if (a[ai[i]] > a[ai[nidx - 1]]) {
			ai[nidx++] = ai[i];
		}
	}
	idx = nidx;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	idx = 1;
	for (int i = 1; i < n; i++) {
		if (a[i] > a[ai[idx - 1]]) {
			ai[idx++] = i;
		}
	}
	for (int i = 0; i < m; i++)
		cin >> b[i];

	for (int i = 0; i < m; i++) {
		ll down = 0;
		for (int q = 0; q < idx; q++) {
			int top = min(a[ai[q]], b[i]);
			if (top > down)
			{
				a[ai[q]] += top - down;
				down = top;
				if (down >= b[i])
					break;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
	return 0;
}