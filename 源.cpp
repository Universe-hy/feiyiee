#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<math.h>
#include<stack>
using namespace std;
typedef long long int ll;

const int  N = 100010;
typedef pair<int, int> PII;
int n, k;
int map[13][13];
int f[13][13], f1 = 1, f3 = 1 << 1, f5 = 1 << 2, f7 = 1 << 3;
stack<int> ans;
int dfs(int x, int y, int w) {
	if (map[x][y] != w) {
		return 0;
	}
	int back = map[x][y];
	map[x][y] = -1;

	if (x == n && y == n) {
		for (int i = 1; i <= n; i++) {
			for (int q = 1; q <= n; q++) {
				if (map[i][q] != -1) {
					map[x][y] = back;
					return 0;
				}
			}
		}
		return 1;
	}


	if (dfs(x - 1, y, (w + 1) % k))
	{
		ans.push(0);
		return 1;
	}

	if ((f[x][y] & f1) == 0) {

		int fb1 = f[x - 1][y];
		int fb2 = f[x][y + 1];
		f[x - 1][y] |= f3;
		f[x][y + 1] |= f7;

		if (dfs(x - 1, y + 1, (w + 1) % k))
		{
			ans.push(1);
			return 1;
		}

		f[x - 1][y] = fb1;
		f[x][y + 1] = fb2;
	}


	if (dfs(x, y + 1, (w + 1) % k))
	{
		ans.push(2);
		return 1;
	}


	if ((f[x][y] & f3) == 0) {
		int fb1 = f[x][y + 1];
		int fb2 = f[x + 1][y];

		f[x][y + 1] |= f5;
		f[x + 1][y] |= f1;

		if (dfs(x + 1, y + 1, (w + 1) % k))
		{
			ans.push(3);
			return 1;
		}

		f[x][y + 1] = fb1;
		f[x + 1][y] = fb2;
	}

	if (dfs(x + 1, y, (w + 1) % k))
	{
		ans.push(4);
		return 1;
	}

	if ((f[x][y] & f5) == 0) {
		int fb1 = f[x][y - 1];
		int fb2 = f[x + 1][y];
		f[x][y - 1] |= f3;
		f[x + 1][y] |= f7;

		if (dfs(x + 1, y - 1, (w + 1) % k))
		{
			ans.push(5);
			return 1;
		}

		f[x][y - 1] = fb1;
		f[x + 1][y] = fb2;
	}

	if (dfs(x, y - 1, (w + 1) % k))
	{
		ans.push(6);
		return 1;
	}


	if ((f[x][y] & f7) == 0) {
		int fb1 = f[x][y - 1];
		int fb2 = f[x - 1][y];

		f[x][y - 1] |= f1;
		f[x - 1][y] |= f5;

		if (dfs(x - 1, y - 1, (w + 1) % k))
		{
			ans.push(7);
			return 1;
		}

		f[x][y - 1] = fb1;
		f[x - 1][y] = fb2;
	}

	map[x][y] = back;
	return 0;
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int q = 1; q <= n; q++) {
			cin >> map[i][q];
		}
	}
	for (int i = 0; i <= n + 1; i++) {
		map[0][i] = map[n + 1][i] = map[i][0] = map[i][n + 1] = -1;
	}

	dfs(1, 1, 0);
	while (ans.size()) {
		cout << ans.top();
		ans.pop();
	}
	return 0;
}