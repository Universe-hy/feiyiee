#include <iostream>
#include <iomanip>
#include <cmath>
#include<vector>
using namespace std;
const int M = 10;
vector<int> w, r, ans;
int k = 0;
void w2() {
	for (int i = 0; i < w.size(); i++) {
		w[i] *= 2;
	}
	int id = w.size() - 1;

	for (int i = 0; i < id; i++)
	{
		if (w[i] / M) {
			w[i + 1] += w[i] / M;
			w[i] %= M;
		}
	}

	if (w[id] / M) {
		w.push_back(w[id] / M);
		w[id] %= M;
	}

}

int main()
{
	int n;
	string R;
	cin >> n;
	cin >> R;
	w.push_back(2);
	for (int i = 1; i < n; i++)
	{
		w2();
	}

	for (int i = R.size() - 1; i >= 0; i--) {
		if (R[i] == '.')
		{
			k = R.size() - i - 1;
			continue;
		}
		r.push_back(R[i] - '0');
	}

	for (int i = 0; i < w.size(); i++) {
		for (int q = 0; q < r.size(); q++) {
			if (i + q >= ans.size()) {
				ans.push_back(w[i] * r[q]);
			}
			else {
				ans[i + q] += w[i] * r[q];
			}

			for (int w = i + q; ans[w] / M; w++) {

				if (w + 1 < ans.size()) {
					ans[w + 1] += ans[w] / M;
				}
				else {
					ans.push_back(ans[w] / M);
				}
				ans[w] %= M;
			}
		}
	}

	if (ans[k - 1] >= 5) {
		ans[k]++;

		for (int w = k; ans[w] / M; w++) {

			if (w + 1 < ans.size()) {
				ans[w + 1] += ans[w] / M;
			}
			else {
				ans.push_back(ans[w] / M);
			}
			ans[w] %= M;
		}
	}

	for (int i = ans.size() - 1; i >= k; i--) {
		cout << ans[i];
	}

	return 0;
}