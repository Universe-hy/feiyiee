#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<math.h>
#include<queue>
using namespace std;
typedef long long int ll;

const int  N = 400010;

int a[N], h[N], rt[N], idx;
int main() {
	int T, n;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> h[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		int t;
		for (int i = 0; i < n; i++) {
			cin >> t;
			rt[t] = i;
		}
		int l = 0, r = 1e9;
		for (int i = 0; i < n - 1; i++) {
			double dh = h[rt[i]] - h[rt[i + 1]];
			double da = a[rt[i + 1]] - a[rt[i]];
			if (da < 0)
				l = max(l, (int)floor(dh / da) + 1);
			else if (da > 0)
				r = min(r, (int)ceil(dh / da) - 1);
			else if (dh <= 0) {
				l = -1;
				break;
			}
		}
		cout << (r >= l ? l : -1) << endl;
	}
	return 0;
}