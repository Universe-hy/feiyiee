#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<vector>
using namespace std;
typedef long long int ll;

const int  N = 100010;
ll n, S;
typedef pair<int, int> PII;
vector<PII> a;
int main() {
	cin >> n >> S;
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		a.push_back(make_pair(y, x));
	}
	sort(a.begin(), a.end(), greater<PII>());

	int id = 0;
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i].second;
		if (sum >= S) {
			id = i;
			break;
		}
	}
	ll cost = a[id].first * S;
	for (int i = 0; i < id; i++) {
		cost += (ll)(a[i].first - a[id].first) * a[i].second;
	}
	cout << cost;
	return 0;
}